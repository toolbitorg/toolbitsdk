#ifndef TOOLBITSDK_HIDLUKE_H_
#define TOOLBITSDK_HIDLUKE_H_

#include <stdint.h>
#include "hidpic16f.h"

typedef enum
{
    // Prodcut specific commands
//    CMD_GET_GPIO_CONFIG = 0x20,
//	CMD_SET_GPIO_CONFIG = 0x21,
//	CMD_GET_GPIO_IN = 0x22,
//	CMD_SET_GPIO_OUT = 0x23,
//	CMD_CONFIG_ADC = 0x24,
//	CMD_GET_ADC_IN = 0x25,
} HidCommProductCommands;


class HidLuke : public HidPic16f
{
public:
	HidLuke();
	~HidLuke();

protected:

private:
};

#endif /* TOOLBITSDK_HIDLUKE_H_ */
