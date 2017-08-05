#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "tbit.h"


I2c::I2c(TbiService *tbisrv) :
	mAttI2C0Addr(ATT_I2C0_ADDR, 0x00, 0x00),
	mAttI2C0RW1Byte(ATT_I2C0_RW_1BYTE, 0x00, 0x00),
	mAttI2C0RW2Byte(ATT_I2C0_RW_2BYTE, 0x00, 0x00)
{

	mTbiSrv = tbisrv;
}

I2c::~I2c()
{

}

bool I2c::write(uint8_t addr, uint16_t val)
{
	bool status;

	mAttI2C0Addr.setValue(addr);
	status = mTbiSrv->writeAttribute(mAttI2C0Addr);
	if (!status) {
		// error
		return false;
	}

	mAttI2C0RW2Byte.setValue(val);
	status = mTbiSrv->writeAttribute(mAttI2C0RW2Byte);
	if (!status) {
		// error
		return false;
	}

	return true;
}

uint16_t I2c::read(uint8_t addr)
{
	bool status;

	mAttI2C0Addr.setValue(addr);
	status = mTbiSrv->writeAttribute(mAttI2C0Addr);
	if (!status) {
		// error
		return 0;
	}

	status = mTbiSrv->readAttribute(&mAttI2C0RW2Byte);
	if (!status) {
		// error
		return 0;
	}
	return mAttI2C0RW2Byte.getValueInt16();
}


Tbit::Tbit() :
	i2ca(mTbiService),
	mAttGpioInoutMode(ATT_GPIO_INOUT_MODE, 0x00, 0x00),
	mAttGpioPullUp(ATT_GPIO_PULL_UP, 0x00, 0x00),
	mAttGpioPullDown(ATT_GPIO_PULL_DOWN, 0x00, 0x00),
	mAttGpioRw(ATT_GPIO_RW, 0x00, 0x00),
	mAttAdc0(ATT_ADC0, 0x00, 0x00)
{
}

Tbit::~Tbit()
{
}

bool Tbit::setGpioPinMode(uint8_t pin, PinMode mode)
{
	bool status;

	if (pin > 3)
		return false;

	if (mode == OUTPUT_PIN) {
		mAttGpioInoutMode.setValue(mAttGpioInoutMode.getValueUint32() & ~(1 << pin));
	}
	else {
		if (mode == INPUT_PIN)
		mAttGpioPullUp.setValue(mAttGpioPullUp.getValueUint32() & ~(1 << pin));
		else if (mode == INPUT_PULLUP_PIN)
		mAttGpioPullUp.setValue(mAttGpioPullUp.getValueUint32() | 1 << pin);
		else
		return false;  // error because INPUT_PULLDOWN_PIN is not supported yet

		status = mTbiService->writeAttribute(mAttGpioPullUp);
		if (!status)
		return false;  // error

		mAttGpioInoutMode.setValue(mAttGpioInoutMode.getValueUint32() | 1 << pin);
	}

	status = mTbiService->writeAttribute(mAttGpioInoutMode);
	if (!status)
		return false;  // error

	return true;
}

bool Tbit::writeGpio(uint32_t dat)
{
	mAttGpioRw.setValue(dat);
	bool status = mTbiService->writeAttribute(mAttGpioRw);
	if (!status)
		return false;   // error
	return true;
}

uint32_t Tbit::readGpio()
{
	bool status = mTbiService->readAttribute(&mAttGpioRw);
	if (!status)
		return false;   // error
	return mAttGpioRw.getValueUint32();
}

bool Tbit::digitalWrite(uint8_t pin, bool val)
{
	if (val)
		mAttGpioRw.setValue(mAttGpioRw.getValueUint32() | 1 << pin);
	else
		mAttGpioRw.setValue(mAttGpioRw.getValueUint32() & ~(1 << pin));

	bool status = mTbiService->writeAttribute(mAttGpioRw);
	if (!status)
		return false;   // error
	return true;
}

bool Tbit::digitalRead(uint8_t pin)
{
	return readGpio() & 1 << pin;
}

uint32_t Tbit::analogRead(uint8_t pin)
{
	
	bool status = mTbiService->readAttribute(&mAttAdc0);
	if (!status)
		return false;   // error
	return mAttAdc0.getValueUint32();
}
