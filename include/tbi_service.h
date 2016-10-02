#ifndef TOOLBITSDK_TBI_SERVICE_H_
#define TOOLBITSDK_TBI_SERVICE_H_

#include <stdint.h>
#include <string>
#include "tbi_device.h"
#include "attribute.h"

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
	OP_ATTR_VALUE_SET,
	OP_ATTR_VALUE_GET,
	// Event Code
	EVT_NOTIFY = 0xA0
} OperationCode;

typedef enum
{
	// Return Code
	RC_FAIL = 0x0,
	RC_OK   = 0x1,
} ReturnCode;

class TbiService {
public:
	TbiService(TbiDevice *p);
	~TbiService();

	bool readAttribute(Attribute *att);
	bool writeAttribute(Attribute att);

private:
	TbiDevice *tdev;
};

#endif /* TOOLBITSDK_TBI_SERVICE_H_ */
