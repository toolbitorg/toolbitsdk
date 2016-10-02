#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "tbi_core.h"

#define USB_VID 0x4d8
#define USB_PID 0x3f

TbiCore::TbiCore() :
	mAttProductName(ATT_PRODUCT_NAME, 0x00, 0x00),
    mAttProductRevision(ATT_PRODUCT_REVISION, 0x00, 0x00),
    mAttProductSerial(ATT_PRODUCT_SERIAL, 0x00, 0x00),
    mAttFirmVersion(ATT_FIRM_VERSION, 0x00, 0x00)
{
	mTbiDevice = new TbiDevice();
	mTbiDevice->open(USB_VID, USB_PID);
	mTbiService = new TbiService(mTbiDevice);

	// Read product data from device
	mTbiService->readAttribute(&mAttProductName);
	mTbiService->readAttribute(&mAttProductRevision);
	mTbiService->readAttribute(&mAttProductSerial);
	mTbiService->readAttribute(&mAttFirmVersion);
}

TbiCore::~TbiCore()
{
	delete mTbiService;
	delete mTbiDevice;
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

