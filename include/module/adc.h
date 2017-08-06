#ifndef TOOLBITSDK_ADC_H_
#define TOOLBITSDK_ADC_H_

#include "tbi_core.h"

class Adc
{
public:
	Adc(TbiService *tbisrv, ToolbitAttributionID base);
	~Adc();
	uint32_t analogRead(uint8_t pin);

protected:
	TbiService *mTbiSrv;
	Attribute *mAttAdcR[8];
};

#endif /* TOOLBITSDK_ADC_H_ */
