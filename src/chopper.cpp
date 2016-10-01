#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "chopper.h"

Chopper::Chopper() :
	mAttProductName(ATT_PRODUCT_NAME, 0x00, 0x00),
    mAttProductRevision(ATT_PRODUCT_REVISION, 0x00, 0x00),
    mAttProductSerial(ATT_PRODUCT_SERIAL, 0x00, 0x00),
    mAttFirmVersion(ATT_FIRM_VERSION, 0x00, 0x00),
    mAttCount(0x1000, 0x00, 0x00)
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

Chopper::~Chopper()
{
	delete mTbiService;
	delete mTbiDevice;
}

void Chopper::CountUp()
{
	uint8_t cnt = mAttCount.getValueInt8() + 1;
	mAttCount.setValue(cnt);
	bool status = mTbiService->writeAttribute(mAttCount);
	if (!status) {
		// error
	}
}

uint8_t Chopper::GetCount()
{
	bool status = mTbiService->readAttribute(mAttCount);
	if (!status) {
		// error
	}
	return mAttCount.getValueInt8();
}

