#include "tbi_device_manager.h"
#include "tbit.h"


Tbit::Tbit() :
	gpiohw(mTbiService, ATT_GPIO0_BASE),
	adchw(mTbiService, ATT_ADC_BASE),
	i2chw(mTbiService, ATT_IC20_BASE)
{
	TbiDeviceManager devm;

	if (open(devm.getPath("Tbit"))) {

	}

}

Tbit::~Tbit()
{
	close();
}

