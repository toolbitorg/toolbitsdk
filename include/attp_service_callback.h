#ifndef TOOLBITSDK_ATTP_SERVICE_CALLBACK_H_
#define TOOLBITSDK_ATTP_SERVICE_CALLBACK_H_

#include <stdint.h>
#include <string>
#include "attp_service.h"
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


class AttpServiceCallback {
public:
	AttpServiceCallback();
	~AttpServiceCallback();

	void onAttributeRead(AttpService attps, AttpService att, int status);
	void onAttributeWrite(AttpService attps, AttpService att, int status);
	void onAttributeChanged(AttpService attps, AttpService att);
};



#endif /* TOOLBITSDK_ATTP_SERVICE_CALLBACK_H_ */
