#ifndef TOOLBITSDK_HIDPIC16F_H_
#define TOOLBITSDK_HIDPIC16F_H_

#include <stdint.h>
#include "libhidcomm.h"


typedef enum
{
    // Platform commom commands
	CMD_GET_GPIO_CONFIG = 0x20,
	CMD_SET_GPIO_CONFIG = 0x21,
	CMD_GET_GPIO_IN = 0x22,
	CMD_SET_GPIO_OUT = 0x23,
	CMD_CONFIG_ADC = 0x24,
	CMD_GET_ADC_IN = 0x25,
} HidCommPlatformCommands;

class HidPic16f : public HidComm
{
public:
	HidPic16f();
	~HidPic16f();
    
	// Platform common commands
//	uint8_t GetGpioConfig(uint8_t port, uint8_t dat);
//	uint8_t SetGpioConfig(uint8_t port, uint8_t dat);
	uint32_t GetGpioIn();
	uint32_t GetAdcIn(uint8_t ch);
    
    
protected:

private:
};

#endif /* TOOLBITSDK_HIDPIC16F_H_ */
