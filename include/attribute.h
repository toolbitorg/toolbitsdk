#ifndef TOOLBITSDK_ATTRIBUTE_H_
#define TOOLBITSDK_ATTRIBUTE_H_

#include <stdint.h>
#include <string>

using namespace std;

#define VALUE_LEN 32

#define PROTOCOL_VERSION 0x00  // 7-6bits is effective

#define byte uint8_t
#define ATTID uint16_t

typedef enum
{
	// Common attribute ID
	ATT_PRODUCT_NAME     = 0x0000,
	ATT_PRODUCT_REVISION = 0x0001,
	ATT_PRODUCT_SERIAL   = 0x0002,
	ATT_FIRM_VERSION     = 0x0003
} AttributionID;

typedef enum
{
	// Attribution permission
	PERMISSION_NONE = 0x00,
	PERMISSION_READABLE = 0x01,
	PERMISSION_WRITABLE = 0x02,
	PERMISSION_READABLE_WRITABLE = 0x03,
} AttributionPermission;

typedef enum
{
	// Attribution property
	PROPERTY_READ = 0x01,
	PROPERTY_WRITE = 0x02,
	PROPERTY_NOTIFY = 0x04,
} AttributionProperty;

class Attvalue
{
public:
	Attvalue();
	~Attvalue();

	bool setValue(uint8_t i);
	bool setValue(int8_t i);
	bool setValue(uint32_t i);
	bool setValue(int32_t i);
	bool setValue(char *str);
	bool setValue(float f);
	bool setValue(double d);
	bool setValue(byte *p, uint8_t len);

	uint8_t  getValueUint8();
	int8_t   getValueInt8();
	uint32_t getValueUint32();
	int32_t  getValueInt32();
	char     *getValueStr();
	float    getValueFloat();
	double   getValueDouble();
	uint8_t  getValueLength();

private:
	union {
		// Byte order must be little endian
		uint8_t  uint8;
		int8_t   int8;
		uint32_t uint32;
		int32_t  int32;
		char     str[VALUE_LEN + 1];
		float    f;
		double   d;
	} dat;
	uint8_t datlen;
};

class Attribute : public Attvalue
{
public:
	Attribute(ATTID id, byte prop, byte perm);
	~Attribute();

	ATTID getAttid();

private:
	ATTID attid;
	uint8_t property;
	uint8_t config;
};

#endif /* TOOLBITSDK_ATTRIBUTE_H_ */
