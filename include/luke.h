#ifndef TOOLBITSDK_LUKE_H_
#define TOOLBITSDK_LUKE_H_

#include <stdint.h>
#include "tbi_device.h"
#include "tbi_service.h"
#include "attribute.h"

class Luke
{
public:
	Luke();
	~Luke();

protected:

private:
	TbiDevice *mTbiDevice;
	TbiService *mTbiService;
	Attribute mAttProductName;
	Attribute mAttProductRevision;
	Attribute mAttProductSerial;
	Attribute mAttFirmVersion;
};

#endif /* TOOLBITSDK_LUKE_H_ */
