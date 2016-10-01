#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "luke.h"


Luke::Luke() :
	mAttProductName(ATT_PRODUCT_NAME, 0x00, 0x00),
	mAttProductRevision(ATT_PRODUCT_REVISION, 0x00, 0x00),
	mAttProductSerial(ATT_PRODUCT_SERIAL, 0x00, 0x00),
	mAttFirmVersion(ATT_FIRM_VERSION, 0x00, 0x00)
{
	mTbiDevice = new TbiDevice();
	mTbiDevice->open(0x00, 0x00);
	mTbiService = new TbiService(mTbiDevice);

	// Read product data from device
	mTbiService->readAttribute(mAttProductName);
	mTbiService->readAttribute(mAttProductRevision);
	mTbiService->readAttribute(mAttProductSerial);
	mTbiService->readAttribute(mAttFirmVersion);
}

Luke::~Luke()
{
	delete mTbiService;
	delete mTbiDevice;
}


