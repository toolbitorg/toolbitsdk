#ifndef TOOLBITSDK_PIN_H_
#define TOOLBITSDK_PIN_H_

#include "gpio.h"

class Pin
{
public:
	Pin(Gpio *gpio, uint8_t pinnum);
	~Pin();

	bool value();
	bool value(bool v);
	bool on();
	bool off();

protected:
	Gpio *mGpio;
	uint8_t mPinNum;
	bool val;
};

#endif /* TOOLBITSDK_PIN_H_ */
