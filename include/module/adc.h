#ifndef TOOLBITSDK_ADC_H_
#define TOOLBITSDK_ADC_H_

#include "tbit.h"

class Adc
{
public:
	Adc(Tbit *p, uint8_t pinnum);
	~Adc();

	int value();

protected:
	Tbit *mTbit;
	uint8_t mPinNum;
	int val;
};

#endif /* TOOLBITSDK_ADC_H_ */
