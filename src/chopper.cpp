#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "chopper.h"

Chopper::Chopper() :
    mAttCount(0x1000, 0x00, 0x00)
{
}

Chopper::~Chopper()
{
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

