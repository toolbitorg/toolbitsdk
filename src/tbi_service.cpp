#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "tbi_service.h"



TbiService::TbiService(TbiDevice *p)
{
	tdev = p;
}

TbiService::~TbiService()
{

}

bool TbiService::readAttribute(Attribute *att)
{
	uint8_t buf[BUF_LEN];
	buf[0] = PROTOCOL_VERSION + 4;  // The first byte is Version(7-6bit) + Length(5-0bit).
	buf[1] = OP_ATTR_VALUE_GET;     // Operation Code
	buf[2] = (att->getAttid() & 0xFF00) >> 8;
	buf[3] = att->getAttid() & 0xFF;

	if (tdev->isOpen()) {
		tdev->write(buf, 4);
	}
	else {
		return false;
	}

	msleep(10);

	if (tdev->read(buf) >= 4) {

		if ((buf[0] & 0xC0) == PROTOCOL_VERSION
			&& buf[1] == OP_ATTR_VALUE_GET
			&& buf[2] == RC_OK)
		{
			int len = (buf[0] & 0x3F) - 3;
			return att->setValue(&buf[3], len);
		}
	}
	return false;
}

bool TbiService::writeAttribute(Attribute att)
{
	uint8_t len = att.getValueLength();
	uint16_t id = att.getAttid();

	uint8_t buf[BUF_LEN];
	buf[0] = PROTOCOL_VERSION + 4 + len;  // The first byte is Version(7-6bit) + Length(5-0bit).
	buf[1] = OP_ATTR_VALUE_SET;           // Operation Code
	buf[2] = (id & 0xFF00) >> 8;
	buf[3] = id & 0xFF;
	char *p = att.getValueStr();
	for (int i = 0; i < len; i++) {
		buf[4 + i] = *p++;                // Set value
	}
	if (tdev->isOpen()) {
		tdev->write(buf, 4+len);
	}
	else {
		return false;
	}

	msleep(10);

	if (tdev->read(buf) >= 3) {
		if (buf[0] == PROTOCOL_VERSION + 3  // Check received packet
			&& buf[1] == OP_ATTR_VALUE_SET
			&& buf[2] == RC_OK)
			return true;
	}
	return false;
}
