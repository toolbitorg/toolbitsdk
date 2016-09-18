#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

#include "attp_service.h"



AttpService::AttpService(AttpDevice *dev)
{

}

AttpService::~AttpService()
{

}

bool AttpService::readAttribute(Attribute att)
{

}

bool AttpService::writeAttribute(Attribute att)
{
	uint8_t sndbuf[BUF_LEN];
	sndbuf[0] = OP_VALUE_SET;


	SendPacket(sndbuf, 1);
	int get
		uint8_t cnt =
}


bool AttpService::sendPacket()
{
	uint8_t buf[BUF_LEN];

	sndbuf[0] = PROTOCOL_VERSION + 4;       // The second byte is Version(7-6bit) + Length(5-0bit).
	buf[1] = OP_VALUE_GET;
	buf[2] = (attrid & 0xFF00) >> 8;
	buf[3] = attrid & 0xFF;
}


bool AttpService::sendPacket()
{
	// Read response from HID device
	int res = hid_read(handle, buf, BUF_LEN);
	if (res < 0)
		return false;

	if ((buf[0] & 0x3) != 0x00)  // Check Version
		return false;
	*num = (buf[0] >> 2) - 1;
	memcpy(rcvbuf, &buf[1], *num);

}



