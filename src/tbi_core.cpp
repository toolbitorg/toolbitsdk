#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <codecvt> 
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
	if (mTbiDevice->isOpen())
		return false;
  	if (!path)
		return false;
  	
	if (!mTbiDevice->open(path))
		return false;

	// Read product data from device
	mTbiService->readAttribute(&mAttVendorName);
	mTbiService->readAttribute(&mAttProductName);
	mTbiService->readAttribute(&mAttProductRevision);
	mTbiService->readAttribute(&mAttProductSerial);
	mTbiService->readAttribute(&mAttFirmVersion);

	return true;
}

bool TbiCore::close()
{
	if (!mTbiDevice->isOpen())
		return false;
	
	mTbiDevice->close();
	return true;
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
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(mAttProductSerial.getValueU8str());		
}

string TbiCore::getFirmVersion()
{
	return mAttFirmVersion.getValueStr();
}
