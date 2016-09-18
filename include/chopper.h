#ifndef TOOLBITSDK_CHOPPER_H_
#define TOOLBITSDK_CHOPPER_H_

#include <stdint.h>
#include "libhid_dev.h"
#include "attp_service.h"
#include "attp_service_callback.h"
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
	HidDev *mAttpDevice;
	AttpService *mAttpService;
	AttpServiceCallback *mAttpCallback;
	Attribute mAttProductName;
	Attribute mAttProductRevision;
	Attribute mAttProductSerial;
	Attribute mAttFirmVersion;
	Attribute mAttCount;
};

#endif /* TOOLBITSDK_CHOPPER_H_ */
