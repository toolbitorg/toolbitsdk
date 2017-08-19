#include "tbi_device_manager.h"
#include "tbit.h"


Tbit::Tbit() :
	gpio(mTbiService, ATT_GPIO0_BASE),
	adc(mTbiService, ATT_ADC_BASE),
	i2c(mTbiService, ATT_IC20_BASE)
{
	TbiDeviceManager devm;

	if (open(devm.getPath("Tbit"))) {

	}

}

Tbit::~Tbit()
{
	close();
}

