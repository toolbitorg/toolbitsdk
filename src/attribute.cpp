/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
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
	return false;
}

bool Attvalue::setValue(uint8_t i)
{
	dat.uint8 = i;
	datlen = 1;
	return false;
}

bool Attvalue::setValue(uint16_t i)
{
	dat.uint16 = i;
	datlen = 2;
	return false;
}

bool Attvalue::setValue(int16_t i)
{
	dat.int16 = i;
	datlen = 2;
	return false;
}

bool Attvalue::setValue(uint32_t i)
{
	dat.uint32 = i;
	datlen = 4;
	return false;
}

bool Attvalue::setValue(int32_t i)
{
	dat.int32 = i;
	datlen = 4;
	return false;
}

bool Attvalue::setValue(uint64_t i)
{
	dat.uint64 = i;
	datlen = 8;
	return false;
}

bool Attvalue::setValue(int64_t i)
{
	dat.int64 = i;
	datlen = 8;
	return false;
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
		return false;
	}
	else {
		return true;
	}
}

bool Attvalue::setValue(float f)
{
	dat.f = f;
	datlen = 4;
	return false;
}

bool Attvalue::setValue(double d)
{
	dat.d = d;
	datlen = 8;
	return false;
}

bool Attvalue::setValue(byte *p, uint8_t len)
{
	if (len <= VALUE_LEN) {
		memcpy(dat.str, p, len);
		datlen = len;
		return false;
	}
	return true;
}

uint8_t Attvalue::getValueUint8()
{
	return dat.uint8;
}

int8_t Attvalue::getValueInt8()
{
	return dat.int8;
}

uint16_t Attvalue::getValueUint16()
{
	return dat.uint16;
}

int16_t Attvalue::getValueInt16()
{
	return dat.int16;
}

uint32_t Attvalue::getValueUint32()
{
	return dat.uint32;
}

int32_t Attvalue::getValueInt32()
{
	return dat.int32;
}

uint64_t Attvalue::getValueUint64()
{
	return dat.uint64;
}

int64_t Attvalue::getValueInt64()
{
	return dat.int64;
}

char* Attvalue::getValueStr()
{
	dat.str[VALUE_LEN] = '\0';  // Add NULL at the end of data just in case
	return dat.str;
}

wchar_t* Attvalue::getValueU8str()
{
	dat.u8str[VALUE_LEN] = '\0';  // Add NULL at the end of data just in case
	return dat.u8str;
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
