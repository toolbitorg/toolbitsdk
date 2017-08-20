#ifndef TOOLBITSDK_PIN_H_
#define TOOLBITSDK_PIN_H_

#include "gpio.h"

class Pin
{
public:
	Pin(Gpio *gpio, uint8_t pinnum);
	Pin(Gpio *gpio, uint8_t pinnum, PinMode mode);
	~Pin();

	bool mode(PinMode m);
	bool value();
	bool value(bool v);
	bool on();
	bool off();

protected:
	Gpio *mGpio;
	uint8_t mPinNum;
	bool val;
	PinMode mPinMode;
};

#endif /* TOOLBITSDK_PIN_H_ */
