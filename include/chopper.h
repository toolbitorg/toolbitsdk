#ifndef TOOLBITSDK_CHOPPER_H_
#define TOOLBITSDK_CHOPPER_H_

#include <stdint.h>
#include "tbi_core.h"
#include "attribute.h"

class Chopper : public TbiCore
{
public:
    Chopper();
    ~Chopper();
    
	bool enableAllUsbPort();
	bool enableUsbPort(uint32_t p);
	bool disableAllUsbPort();
	bool disableUsbPort(uint32_t p);
	uint32_t getUsbPortStatus();
protected:

private:
	Attribute mAttUsbPortCtrl;    // Enable/Disable USB ports
};

#endif /* TOOLBITSDK_CHOPPER_H_ */
