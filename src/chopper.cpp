/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <stdlib.h>
#include "tbi_device_manager.h"
#include "chopper.h"

Chopper::Chopper() :
	gpiohw(mTbiService, ATT_GPIO0_BASE),
	mAttUsbPortCtrl(ATT_USB_PORT_CTRL, 0x00, 0x00)
{
}

Chopper::~Chopper()
{
	close();
}

bool Chopper::open()
{
	TbiDeviceManager devm;

	if (openPath(devm.getPathByName("Chopper HUB"))) {
		// error
		return true;
	}
	mTbiService->readAttribute(&mAttUsbPortCtrl);
	return false;
}

bool Chopper::open(string serial)
{
	TbiDeviceManager devm;

	if (openPath(devm.getPathByNameAndSerial("Chopper HUB", serial))) {
		//error
		return true;
	}
	mTbiService->readAttribute(&mAttUsbPortCtrl);
	return false;
}

bool Chopper::enableAllUsbPort()
{
	uint32_t val = 0xFFFFFFFF;
	mAttUsbPortCtrl.setValue(val);
	return mTbiService->writeAttribute(mAttUsbPortCtrl);
}

bool Chopper::enableUsbPort(uint32_t p)
{
	if (p == 0 || p > 32)
		return true;

	uint32_t val = mAttUsbPortCtrl.getValueUint32() | (1 << p - 1);
	mAttUsbPortCtrl.setValue(val);
	return mTbiService->writeAttribute(mAttUsbPortCtrl);
}

bool Chopper::disableAllUsbPort()
{
	uint32_t val = 0x00000000;
	mAttUsbPortCtrl.setValue(val);
	return mTbiService->writeAttribute(mAttUsbPortCtrl);
}

bool Chopper::disableUsbPort(uint32_t p)
{
	if (p == 0 || p > 32)
		return true;

	uint32_t val = mAttUsbPortCtrl.getValueUint32() & ~(1 << p - 1);
	mAttUsbPortCtrl.setValue(val);
	return mTbiService->writeAttribute(mAttUsbPortCtrl);
}

uint32_t Chopper::getUsbPortStatus()
{
	return mTbiService->readAttribute(&mAttUsbPortCtrl);
}
