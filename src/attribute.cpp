#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

#include "attribute.h"

Attvalue::Attvalue()
{
	dat.int8 = 0;
	datlen = 1;
}

Attvalue::~Attvalue()
{

}

bool Attvalue::setValue(int8_t i)
{
	dat.int8 = i;
	datlen = 1;
	return true;
}

bool Attvalue::setValue(uint8_t i)
{
	dat.uint8 = i;
	datlen = 1;
	return true;
}

bool Attvalue::setValue(uint32_t i)
{
	dat.uint32 = i;
	datlen = 4;
	return true;
}

bool Attvalue::setValue(int32_t i)
{
	dat.int32 = i;
	datlen = 4;
	return true;
}

bool Attvalue::setValue(char *str)
{
	if (strlen(str) < VALUE_LEN) {
		datlen = strlen(str);
#ifdef _MSC_VER
		strcpy_s(dat.str, str);
#else
		strcpy(dat.str, str);
#endif
		return true;
	}
	else {
		return false;
	}
}

bool Attvalue::setValue(float f)
{
	dat.f = f;
	datlen = 4;
	return true;
}

bool Attvalue::setValue(double d)
{
	dat.d = d;
	datlen = 8;
	return true;
}

bool Attvalue::setValue(byte *p, uint8_t len)
{
	if (len <= VALUE_LEN) {
		memcpy(dat.str, p, len);
		datlen = len;
		return true;
	}
	return false;
}

uint8_t Attvalue::getValueUint8()
{
	return dat.uint8;
}

int8_t Attvalue::getValueInt8()
{
	return dat.int8;
}

uint32_t Attvalue::getValueUint32()
{
	return dat.uint32;
}

int32_t Attvalue::getValueInt32()
{
	return dat.int32;
}

char* Attvalue::getValueStr()
{
	dat.str[VALUE_LEN] = '\0';  // Add NULL at the end of data just in case
	return dat.str;
}

float Attvalue::getValueFloat()
{
	return dat.f;
}

double Attvalue::getValueDouble()
{
	return dat.d;
}

uint8_t Attvalue::getValueLength()
{
	return datlen;
}


Attribute::Attribute(ATTID id, byte prop, byte conf)
{
	attid = id;
	property = prop;
	config = conf;
}

Attribute::~Attribute()
{

}

ATTID Attribute::getAttid()
{
	return attid;
}

