#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "basicdemo.h"

BasicDemo::BasicDemo() :
    mAttCount(0x1000, 0x00, 0x00)
{
	// Read value from device
	mTbiService->readAttribute(&mAttCount);
}

BasicDemo::~BasicDemo()
{
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

