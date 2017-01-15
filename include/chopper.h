#ifndef TOOLBITSDK_CHOPPER_H_
#define TOOLBITSDK_CHOPPER_H_

#include <stdint.h>
#include "tbi_core.h"
#include "attribute.h"
#include "pic16f145x.h"

// Product specific attribute ID
#define ATT_USB_PORT_CTRL    0x8000
#define GPIO_INOUT_MODE      0x8010
//#define GPIO_PULL_UP         0x8011
//#define GPIO_PULL_DOWN       0x8012
#define GPIO_RW_VAL          0x8013

typedef enum
{
	// Operation Code
	OUTPUT_PIN,
	INPUT_PIN,
	INPUT_PULLUP_PIN,
	INPUT_PULLDOWN_PIN
} PinMode;

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
	bool setGpioPinMode(uint32_t pin, PinMode mode);
	bool writeGpio(uint32_t dat);
	uint32_t readGpio();
protected:

private:
	// Product specific attribute ID
	Attribute mAttUsbPortCtrl;    // Enable/Disable USB ports
	Attribute mAttGpioInoutMode;
	//Attribute mAttGpioPullUp;
	//Attribute mAttGpioPullDown;
	Attribute mAttGpioRwVal;
};

#endif /* TOOLBITSDK_CHOPPER_H_ */
