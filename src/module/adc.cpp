#include "adc.h"


Adc::Adc(Tbit *p, uint8_t pinnum)
{
	mTbit = p;
	mPinNum = pinnum;
	val = 0;
}

Adc::~Adc()
{
}

int Adc::value()
{
	return mTbit->adchw.analogRead(mPinNum);
}
