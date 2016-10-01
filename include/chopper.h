#ifndef TOOLBITSDK_CHOPPER_H_
#define TOOLBITSDK_CHOPPER_H_

#include <stdint.h>
#include "tbi_device.h"
#include "tbi_service.h"
#include "attribute.h"

class Chopper
{
public:
    Chopper();
    ~Chopper();
    
    void CountUp();
    uint8_t GetCount();
protected:

private:
	TbiDevice *mTbiDevice;
	TbiService *mTbiService;
	Attribute mAttProductName;
	Attribute mAttProductRevision;
	Attribute mAttProductSerial;
	Attribute mAttFirmVersion;
	Attribute mAttCount;
};

#endif /* TOOLBITSDK_CHOPPER_H_ */
