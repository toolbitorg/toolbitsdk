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
	ttpDevice *mAttpDevice;

	HidComm dev;

	AttpService *mAttpService;

	attpService = dev.connected(this, false, attCallback);	
}

Chopper::~Chopper()
{
}

void Chopper::CountUp()
{
	uint8_t cnt = mAttCount.getValue + 1;
	mAttCount.setValue(cnt);
	bool status = mAttpService.writeAttribute(mAttCount);
	if (!status) {
		// error
	}
}


uint8_t Chopper::GetCount()
{
	

	uint8_t sndbuf[BUF_LEN];
	uint8_t rcvbuf[BUF_LEN];
	uint8_t num;
    
    sndbuf[0] = 0x81;
	SendPacket(sndbuf, 1);

    msleep(10);
    
	if (!ReceivePacket(rcvbuf, &num))
		return 0;
	else
		return rcvbuf[0];
}

