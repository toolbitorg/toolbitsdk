#include "gpio.h"


Gpio::Gpio(TbiService *tbisrv, ToolbitAttributionID base)
{
	mTbiSrv = tbisrv;
	mAttGpioInoutMode = new Attribute(base + ATT_GPIO_INOUT_MODE, 0x00, 0x00);
	mAttGpioPullUp = new Attribute(base + ATT_GPIO_PULL_UP, 0x00, 0x00);
	mAttGpioPullDown = new Attribute(base + ATT_GPIO_PULL_DOWN, 0x00, 0x00);
	mAttGpioRw = new Attribute(base + ATT_GPIO_RW, 0x00, 0x00);
}

Gpio::~Gpio()
{
	delete mAttGpioInoutMode;
	delete mAttGpioPullUp;
	delete mAttGpioPullDown;
	delete mAttGpioRw;	
}

bool Gpio::pinMode(uint8_t pin, PinMode mode)
{
	bool status;

	if (pin > 32)
		return false;

	if (mode == OUTPUT_PIN) {
		mAttGpioInoutMode->setValue(mAttGpioInoutMode->getValueUint32() | (1 << pin));
	}
	else {
		if (mode == INPUT_PIN)
			mAttGpioPullUp->setValue(mAttGpioPullUp->getValueUint32() & ~(1 << pin));
		else if (mode == INPUT_PULLUP_PIN)
			mAttGpioPullUp->setValue(mAttGpioPullUp->getValueUint32() | (1 << pin));
		else
			return false;  // error because INPUT_PULLDOWN_PIN is not supported yet

		status = mTbiSrv->writeAttribute(*mAttGpioPullUp);
		if (!status)
			return false;  // error

		mAttGpioPullUp->setValue(mAttGpioInoutMode->getValueUint32() & ~(1 << pin));
	}

	status = mTbiSrv->writeAttribute(*mAttGpioInoutMode);
	if (!status)
		return false;  // error

	return true;
}

bool Gpio::write(uint32_t dat)
{
	mAttGpioRw->setValue(dat);
	bool status = mTbiSrv->writeAttribute(*mAttGpioRw);
	if (!status)
		return false;   // error
	return true;
}

uint32_t Gpio::read()
{
	bool status = mTbiSrv->readAttribute(mAttGpioRw);
	if (!status)
		return false;   // error
	return mAttGpioRw->getValueUint32();
}

bool Gpio::digitalWrite(uint8_t pin, bool val)
{
	read();
	if (val)
		mAttGpioRw->setValue(mAttGpioRw->getValueUint32() | 1 << pin);
	else
		mAttGpioRw->setValue(mAttGpioRw->getValueUint32() & ~(1 << pin));

	bool status = mTbiSrv->writeAttribute(*mAttGpioRw);
	if (!status)
		return false;   // error
	return true;
}

bool Gpio::digitalRead(uint8_t pin)
{
	return read() & 1 << pin;
}
