#ifndef TOOLBITSDK_CHOPPER_H_
#define TOOLBITSDK_CHOPPER_H_

#include <stdint.h>
#include "pic16f145x.h"
#include "attribute.h"

// Product specific attribute ID
#define ATT_USB_PORT_CTRL    0x8000


class Chopper : public Picbit
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
	// Product specific attribute ID
	Attribute mAttUsbPortCtrl;    // Enable/Disable USB ports
};

#endif /* TOOLBITSDK_CHOPPER_H_ */
