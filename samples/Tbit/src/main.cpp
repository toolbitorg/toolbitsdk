#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "tbit.h"

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


	cout << "GPIO: " << tbit->gpio.read() << endl;

	cout << "GPIO: " << tbit->gpio.write(0x12345678) << endl;


#ifdef WIN32
	system("pause");
#endif
	return 0;
}
