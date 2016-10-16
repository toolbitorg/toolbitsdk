#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "chopper.h"

Chopper::Chopper() :
	mAttUsbPortCtrl(0x1000, 0x00, 0x00)
{
	// Get current status
	mTbiService->readAttribute(&mAttUsbPortCtrl);
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

