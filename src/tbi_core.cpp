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
#include <string.h>
#include <stdlib.h>
#include "tbi_core.h"

TbiCore::TbiCore() :
	mAttVendorName(ATT_VENDOR_NAME, 0x00, 0x00),
	mAttProductName(ATT_PRODUCT_NAME, 0x00, 0x00),
	mAttProductRevision(ATT_PRODUCT_REVISION, 0x00, 0x00),
    mAttProductSerial(ATT_PRODUCT_SERIAL, 0x00, 0x00),
    mAttFirmVersion(ATT_FIRM_VERSION, 0x00, 0x00)
{
	mTbiDevice = new TbiDevice();
	mTbiService = new TbiService(mTbiDevice);
}


TbiCore::~TbiCore()
{
	delete mTbiService;
	delete mTbiDevice;
}

bool TbiCore::openPath(const char *path)
{
	if (mTbiDevice->isOpen() || !path)
		return true;

	if (mTbiDevice->open(path))
		return true;

	// Read product data from device
	mTbiService->readAttribute(&mAttVendorName);
	mTbiService->readAttribute(&mAttProductName);
	mTbiService->readAttribute(&mAttProductRevision);
	mTbiService->readAttribute(&mAttProductSerial);
	mTbiService->readAttribute(&mAttFirmVersion);

	return false;
}

bool TbiCore::close()
{
	if (!mTbiDevice->isOpen())
		return true;

	mTbiDevice->close();
	return false;
}

bool TbiCore::isConnected()
{
	if (!mTbiDevice)
		return false;

	return mTbiDevice->isOpen();
}

string TbiCore::getVendorName()
{
	return mAttVendorName.getValueStr();
}

string TbiCore::getProductName()
{
	return mAttProductName.getValueStr();
}

string TbiCore::getProductRevision()
{
	return mAttProductRevision.getValueStr();
}

string TbiCore::getProductSerial()
{
	return mAttProductSerial.getValueStr();
}

string TbiCore::getFirmVersion()
{
	return mAttFirmVersion.getValueStr();
}

string convertWcharToString(wchar_t* p)
{
	char str[VALUE_LEN];
	char* dst = str;

	if (!p)
		return "";

	while (*p != NULL) {
		*dst++ = (char)* p++;
	}
	*dst = NULL;

	return str;
}
