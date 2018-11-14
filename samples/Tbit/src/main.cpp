#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "tbit.h"
#include "pin.h"
#include "adc.h"


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


	cout << "GPIO: " << "0x" << std::hex << tbit->gpiohw.read() << endl;
	cout << "ADC: " << tbit->adchw.analogRead(4) << endl;

                                            // Atmega32U4
	Pin led(tbit, 15);                      // PC7
	Pin outpin(tbit, 6, OUTPUT_PIN);        // PB6
	Pin inpin(tbit, 5, INPUT_PULLUP_PIN);   // PB5
	Adc adcpin(tbit, 4);                    // PB4


	led.off();
	cout << "LED: " << led.value() << endl;
	outpin.off();
	cout << "IN: " << inpin.value() << endl;
	cout << "GPIO: " << "0x" << std::hex << tbit->gpiohw.read() << endl;
	cout << "ADC: " << adcpin.value() << endl;


	led.on();
	cout << "LED: " << led.value() << endl;
	outpin.on();
	cout << "IN: " << inpin.value() << endl;
	cout << "GPIO: " << "0x" << std::hex << tbit->gpiohw.read() << endl;
	cout << "ADC: " << adcpin.value() << endl;


#ifdef WIN32
	system("pause");
#endif
	return 0;
}
