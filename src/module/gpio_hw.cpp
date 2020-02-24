/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include "gpio_hw.h"

GpioHw::GpioHw(TbiService *tbisrv, ToolbitAttributionID base)
{
	mTbiSrv = tbisrv;
	mAttGpioInoutMode = new Attribute(base + ATT_GPIO_INOUT_MODE, 0x00, 0x00);
	mAttGpioPullUp = new Attribute(base + ATT_GPIO_PULL_UP, 0x00, 0x00);
	mAttGpioPullDown = new Attribute(base + ATT_GPIO_PULL_DOWN, 0x00, 0x00);
	mAttGpioRw = new Attribute(base + ATT_GPIO_RW, 0x00, 0x00);
}

GpioHw::~GpioHw()
{
	delete mAttGpioInoutMode;
	delete mAttGpioPullUp;
	delete mAttGpioPullDown;
	delete mAttGpioRw;
}

bool GpioHw::pinMode(uint8_t pin, PinMode mode)
{
	bool status;

	if (pin > 32)
		return false;

	status = mTbiSrv->readAttribute(mAttGpioInoutMode);
	if (status)
		return true;   // error

	if (mode == OUTPUT_PIN) {
		// clear bit to change output pin
		mAttGpioInoutMode->setValue(mAttGpioInoutMode->getValueUint32() & ~(1 << pin));
	}
	else {
		status = mTbiSrv->readAttribute(mAttGpioPullUp);
		if (status)
			return true;   // error

		if (mode == INPUT_PIN)
			mAttGpioPullUp->setValue(mAttGpioPullUp->getValueUint32() & ~(1 << pin));
		else if (mode == INPUT_PULLUP_PIN)
			mAttGpioPullUp->setValue(mAttGpioPullUp->getValueUint32() | (1 << pin));
		else
			return true;  // error because INPUT_PULLDOWN_PIN is not supported yet

		status = mTbiSrv->writeAttribute(*mAttGpioPullUp);
		if (status)
			return true;  // error

		// set bit to change input pin
		mAttGpioInoutMode->setValue(mAttGpioInoutMode->getValueUint32() | (1 << pin));
	}

	status = mTbiSrv->writeAttribute(*mAttGpioInoutMode);
	if (status)
		return true;  // error

	return false;
}

bool GpioHw::write(uint32_t dat)
{
	mAttGpioRw->setValue(dat);
	bool status = mTbiSrv->writeAttribute(*mAttGpioRw);
	if (status)
		return true;   // error
	return false;
}

uint32_t GpioHw::read()
{
	bool status = mTbiSrv->readAttribute(mAttGpioRw);
	if (status)
		return 0xFFFFFFFF;   // error
	return mAttGpioRw->getValueUint32();
}

bool GpioHw::digitalWrite(uint8_t pin, bool val)
{
	read();
	if (val)
		mAttGpioRw->setValue(mAttGpioRw->getValueUint32() | 1 << pin);
	else
		mAttGpioRw->setValue(mAttGpioRw->getValueUint32() & ~(1 << pin));

	bool status = mTbiSrv->writeAttribute(*mAttGpioRw);
	if (status)
		return true;   // error
	return false;
}

bool GpioHw::digitalRead(uint8_t pin)
{
	return read() & 1 << pin;
}
