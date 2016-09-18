#ifndef TOOLBITSDK_ATTP_SERVICE_H_
#define TOOLBITSDK_ATTP_SERVICE_H_

#include <stdint.h>
#include <string>
#include "attp_device.h"
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
	OP_VALUE_SET,
	OP_VALUE_GET,
	// Event Code
	EVT_NOTIFY = 0xA0
} OperationCode;


class AttpService {
public:
	AttpService(AttpDevice *dev);
	~AttpService();

	bool readAttribute(Attribute att);
	bool writeAttribute(Attribute att);
};


#endif /* TOOLBITSDK_ATTP_SERVICE_H_ */
