#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "tbit.h"
#include "pin.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
    Tbit *tbit = new Tbit();

	if (!tbit->isConnected()) {
		cout << "Fail to connect to Tbit device" << endl;
#ifdef WIN32
		system("pause");
#endif
		return 1;
	}

	cout << "ProductName: " << tbit->getProductName() << endl;
	cout << "ProductRevision: " << tbit->getProductRevision() << endl;
	cout << "ProductSerial: " << tbit->getProductSerial() << endl;
	cout << "ProductVersion: " << tbit->getFirmVersion() << endl;


	cout << "GPIO: " << "0x" << std::hex << tbit->gpio.read() << endl;

	Pin led(&tbit->gpio, 15);                   // PC7 
	Pin out(&tbit->gpio, 6, OUTPUT_PIN);        // PB6
	Pin in(&tbit->gpio, 5, INPUT_PULLUP_PIN);   // PB5


	led.off();
	cout << "LED: " << led.value() << endl;
	out.off();
	cout << "IN: " << in.value() << endl;
	cout << "GPIO: " << "0x" << std::hex << tbit->gpio.read() << endl;

	led.on();
	cout << "LED: " << led.value() << endl;
	out.on();
	cout << "IN: " << in.value() << endl;
	cout << "GPIO: " << "0x" << std::hex << tbit->gpio.read() << endl;

	//	cout << "ADC: " << tbit->adc.analogRead() << endl;


#ifdef WIN32
	system("pause");
#endif
	return 0;
}
