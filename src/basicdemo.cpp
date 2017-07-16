#include <stdio.h>
#include <wchar.h>
#include <string>
#include <stdlib.h>
#include "tbi_device_manager.h"
#include "basicdemo.h"

BasicDemo::BasicDemo() :
    mAttCount(0x1000, 0x00, 0x00)
{
	TbiDeviceManager devm;

	if (open(devm.getPath("Luke"))) {

		// Read value from device
		mTbiService->readAttribute(&mAttCount);
	}
}

BasicDemo::~BasicDemo()
{
	close();
}

void BasicDemo::CountUp()
{
	uint8_t cnt = mAttCount.getValueInt8() + 1;
	mAttCount.setValue(cnt);
	bool status = mTbiService->writeAttribute(mAttCount);
	if (!status) {
		fprintf(stderr, "[ERR] Unable to write attribute\n");
	}
}

uint8_t BasicDemo::GetCount()
{
	bool status = mTbiService->readAttribute(&mAttCount);
	if (!status) {
		fprintf(stderr, "[ERR] Unable to read attribute\n");
	}
	return mAttCount.getValueInt8();
}

