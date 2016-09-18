#ifndef TOOLBITSDK_ATTRIBUTE_H_
#define TOOLBITSDK_ATTRIBUTE_H_

#include <stdint.h>
#include <string>

using namespace std;

#define BUF_LEN 65
#define MAX_STR 255

#define PROTOCOL_VERSION 0x00  // 7-6bits is effective

#define byte uint8_t
#define ATTID uint16_t

typedef enum
{
	// Operation Code
	OP_METADATA_GET = 0x10,
	OP_CONFIG_SET,
	OP_VALUE_SET,
	OP_VALUE_GET,
	// Event Code
	EVT_NOTIFY = 0xA0
} OperationCode;

typedef enum
{
	// Common attribute ID
	ATT_PRODUCT_NAME = 0x0000,
	ATT_PRODUCT_REVISION = 0x0001,
	ATT_PRODUCT_SERIAL = 0x0002,
	ATT_FIRM_VERSION = 0x0003
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


class Attribute {
public:
	Attribute(ATTID attid, byte prop, byte perm);
	~Attribute();

	ATTID getAttid();
	bool setValue();
	byte getValue();
};

#endif /* TOOLBITSDK_ATTRIBUTE_H_ */
