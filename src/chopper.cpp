#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "chopper.h"


Chopper::Chopper() :
	mAttUsbPortCtrl(ATT_USB_PORT_CTRL, 0x00, 0x00),
	mAttGpioInoutMode(GPIO_INOUT_MODE, 0x00, 0x00),
	mAttGpioRwVal(GPIO_RW_VAL, 0x00, 0x00)
{
	// Get current status
	mTbiService->readAttribute(&mAttUsbPortCtrl);
	mTbiService->readAttribute(&mAttGpioInoutMode);
	mTbiService->readAttribute(&mAttGpioRwVal);
}

Chopper::~Chopper()
{
}

bool Chopper::enableAllUsbPort()
{
	uint32_t val = 0xFFFFFFFF;
	mAttUsbPortCtrl.setValue(val);
	bool status = mTbiService->writeAttribute(mAttUsbPortCtrl);
	if (!status)
		return false;   // error
	return true;
}

bool Chopper::enableUsbPort(uint32_t p)
{
	if (p == 0 || p > 32)
		return false;

	uint32_t val = mAttUsbPortCtrl.getValueUint32() | (1 << p - 1);
	mAttUsbPortCtrl.setValue(val);
	bool status = mTbiService->writeAttribute(mAttUsbPortCtrl);
	if (!status)
		return false;   // error
	return true;
}

bool Chopper::disableAllUsbPort()
{
	uint32_t val = 0x00000000;
	mAttUsbPortCtrl.setValue(val);
	bool status = mTbiService->writeAttribute(mAttUsbPortCtrl);
	if (!status)
		return false;   // error
	return true;
}

bool Chopper::disableUsbPort(uint32_t p)
{
	if (p == 0 || p > 32)
		return false;

	uint32_t val = mAttUsbPortCtrl.getValueUint32() & ~(1 << p - 1);
	mAttUsbPortCtrl.setValue(val);
	bool status = mTbiService->writeAttribute(mAttUsbPortCtrl);
	if (!status)
		return false;   // error
	return true;
}

uint32_t Chopper::getUsbPortStatus()
{
	bool status = mTbiService->readAttribute(&mAttUsbPortCtrl);
	if (!status)
		return false;   // error
	return mAttUsbPortCtrl.getValueUint32();
}

bool Chopper::setGpioPinMode(uint32_t pin, PinMode mode)
{
	bool status;

	if (pin > 3)
		return false;

	if (mode == OUTPUT_PIN) {
		mAttGpioInoutMode.setValue(mAttGpioInoutMode.getValueUint32() & ~(1 << pin));
	}
	else {
		// comment out because INPUT_PULLUP_PIN is not supported
		/*
		if (mode == INPUT_PIN)
			mAttGpioPullUp.setValue(mAttGpioPullUp.getValueUint32() & ~(1 << pin));
		else if (mode == INPUT_PULLUP_PIN)
			mAttGpioPullUp.setValue(mAttGpioPullUp.getValueUint32() | 1 << pin);
		else
			return false;  // error because INPUT_PULLDOWN_PIN is not supported

		status = mTbiService->writeAttribute(mAttGpioPullUp);
		if (!status)
			return false;  // error
		*/
		mAttGpioInoutMode.setValue(mAttGpioInoutMode.getValueUint32() | 1 << pin);
	}

	status = mTbiService->writeAttribute(mAttGpioInoutMode);
	if (!status)
		return false;  // error

	return true;
}

bool Chopper::writeGpio(uint32_t dat)
{
	mAttGpioRwVal.setValue(dat);
	bool status = mTbiService->writeAttribute(mAttGpioRwVal);
	if (!status)
		return false;   // error
	return true;
}

uint32_t Chopper::readGpio()
{
	bool status = mTbiService->readAttribute(&mAttGpioRwVal);
	if (!status)
		return false;   // error
	return mAttGpioRwVal.getValueUint32();
}
