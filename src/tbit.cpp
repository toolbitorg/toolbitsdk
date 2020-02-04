#include "tbi_device_manager.h"
#include "tbit.h"


Tbit::Tbit() :
	gpiohw(mTbiService, ATT_GPIO0_BASE),
	adchw(mTbiService, ATT_ADC_BASE),
	i2chw(mTbiService, ATT_IC20_BASE)
{
}

Tbit::~Tbit()
{
	close();
}

bool Tbit::open()
{
	TbiDeviceManager devm;
	return openPath(devm.getPathByName("Tbit"));
}

bool Tbit::open(string serial)
{
	TbiDeviceManager devm;
	return openPath(devm.getPathByNameAndSerial("Tbit", serial));
}
