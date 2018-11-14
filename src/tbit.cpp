#include "tbi_device_manager.h"
#include "tbit.h"

#include <iostream>

using namespace std;

void eventHandler(tbiPacket pckt)
{
	cout << "Get event notify packet: ";

	for (int i = 0; i < (pckt.dat[0] & 0x3F); i++)
		cout << unsigned(pckt.dat[i]);
	cout << endl;
}

Tbit::Tbit() :
	gpiohw(mTbiService, ATT_GPIO0_BASE),
	adchw(mTbiService, ATT_ADC_BASE),
	i2chw(mTbiService, ATT_IC20_BASE)
{
	TbiDeviceManager devm;

//	if (open(devm.getPath("Tbit"))) {
	if (open(devm.getPath("CHOPPER HUB"))) {

		this->mTbiService->bindEventHandler(eventHandler);

	}

}

Tbit::~Tbit()
{
	close();
}

