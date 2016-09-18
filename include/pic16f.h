#ifndef TOOLBITSDK_PIC16F_H_
#define TOOLBITSDK_PIC16F_H_

#include <stdint.h>
#include "libhidcomm.h"


typedef enum
{
    // Platform commom commands
	ATTR_GPIO_CONFIG = 0x20,
	ATTR_GPIO = 0x21,
	ATTR_ADC_CONFIG = 0x22,
	ATTR_ADC = 0x23,
} HidCommPlatformCommands;

class Pic16f : public HidComm
{
public:
	Pic16f();
	~Pic16f();
    
	// Platform common commands
	uint32_t GetGpioIn();
	uint32_t GetAdcIn(uint8_t ch);
    
    
protected:

private:
};

#endif /* TOOLBITSDK_PIC16F_H_ */
