#include <stdio.h>
#include <wchar.h>
#include <string>
#include <stdlib.h>
#include "tbi_device_manager.h"
#include "chopper.h"


Chopper::Chopper() :
	mAttUsbPortCtrl(ATT_USB_PORT_CTRL, 0x00, 0x00)
{
	TbiDeviceManager devm;

	if (open(devm.getPath("CHOPPER HUB"))) {

		// Get current status
		mTbiService->readAttribute(&mAttGpioInoutMode);
		mTbiService->readAttribute(&mAttGpioPullUp);
		mTbiService->readAttribute(&mAttGpioPullDown);
		mTbiService->readAttribute(&mAttGpioRw);

		mTbiService->readAttribute(&mAttUsbPortCtrl);
	}
}

Chopper::~Chopper()
{
	close();
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

