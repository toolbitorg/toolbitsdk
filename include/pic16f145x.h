#ifndef TOOLBITSDK_PIC16F145X_H_
#define TOOLBITSDK_PIC16F145X_H_

#include "tbi_core.h"


typedef enum
{
	// Platform common attribute ID
	ATT_GPIO_INOUT_MODE = 0x1000,
	ATT_GPIO_PULL_UP = 0x1001,
	ATT_GPIO_PULL_DOWN = 0x1002,
	ATT_GPIO_RW = 0x1003,
	ATT_I2C0_ADDR = 0x1030,
	ATT_I2C0_RW_1BYTE = 0x1031,
	ATT_I2C0_RW_2BYTE = 0x1032,
} PlatformAttributionID;

typedef enum
{
	// Operation Code
	OUTPUT_PIN,
	INPUT_PIN,
	INPUT_PULLUP_PIN,
	INPUT_PULLDOWN_PIN
} PinMode;

#define HIGH 1
#define LOW  0


class Picbit : public TbiCore
{
public:
	Picbit();
	~Picbit();

	// GPIO
	bool setGpioPinMode(uint8_t pin, PinMode mode);
	bool writeGpio(uint32_t dat);
	uint32_t readGpio();
	bool digitalWrite(uint8_t pin, bool val);
	bool digitalRead(uint8_t pin);
	// I2C
	uint16_t readReg(uint8_t addr);
	bool writeReg(uint8_t addr, uint16_t val);

protected:
	// Platform commom attribute
	Attribute mAttGpioInoutMode;
	Attribute mAttGpioPullUp;
	Attribute mAttGpioPullDown;
	Attribute mAttGpioRw;
	Attribute mAttI2C0Addr;
	Attribute mAttI2C0RW1Byte;
	Attribute mAttI2C0RW2Byte;


private:
};

#endif /* TOOLBITSDK_PIC16F145X_H_ */
