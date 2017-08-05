#ifndef TOOLBITSDK_TBIT_H_
#define TOOLBITSDK_TBIT_H_

#include "tbi_core.h"

// Target MCU
// PIC16F145X
// ATmega32U4

typedef enum
{
	// Platform common attribute ID
	ATT_GPIO_INOUT_MODE = 0x1000,
	ATT_GPIO_PULL_UP = 0x1001,
	ATT_GPIO_PULL_DOWN = 0x1002,
	ATT_GPIO_RW = 0x1003,
	ATT_ADC0 = 0x1010,
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


class I2c
{
public:
	I2c(TbiService *tbisrv);
	~I2c();
	bool write(uint8_t addr, uint16_t val);
	uint16_t I2c::read(uint8_t addr);

protected:
	TbiService *mTbiSrv;
	Attribute mAttI2C0Addr;
	Attribute mAttI2C0RW1Byte;
	Attribute mAttI2C0RW2Byte;
};


class Tbit : public TbiCore
{
public:
	Tbit();
	~Tbit();

	// GPIO
	bool setGpioPinMode(uint8_t pin, PinMode mode);
	bool writeGpio(uint32_t dat);
	uint32_t readGpio();
	bool digitalWrite(uint8_t pin, bool val);
	bool digitalRead(uint8_t pin);
	uint32_t analogRead(uint8_t pin);
	// I2C
	I2c  i2ca;


protected:
	// Platform commom attribute
	Attribute mAttGpioInoutMode;
	Attribute mAttGpioPullUp;
	Attribute mAttGpioPullDown;
	Attribute mAttGpioRw;
	Attribute mAttAdc0;


private:
};

#endif /* TOOLBITSDK_TBIT_H_ */
