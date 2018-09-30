#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "luke.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
    Luke *luke = new Luke();
/*
	if (!luke->isConnected()) {
		cout << "Fail to connect to Luke " << endl;
		return 1;
	}
	*/

	cout << "ProductName: " << luke->getProductName() << endl;
	cout << "ProductRevision: " << luke->getProductRevision() << endl;
	cout << "ProductSerial: " << luke->getProductSerial() << endl;
	cout << "ProductVersion: " << luke->getFirmVersion() << endl;

	/*
    getoption go(argc, argv);

    while (1) {
        int c = go.get("l");
        if ( c == -1 ) {
            break;
        }

        switch (c) {			
			case 'l':
                //hidchopper->ShowDeviceList();
                break;

            case 'c':
                cout << "option c with value " << go.argument() << endl;
                break;

            case '?':
              break;

            default:
                cout << "?? getopt returned character code "<< c << "??" << endl;
        }
    }

    // optind
    cout << "non-option ARGV-elements: ";
    for (int i=go.optind(); i<argc; i++ ) {
        cout << argv[i] << " ";
    }
    cout << endl;
	*/

	//luke->setCurrentRange(CURRENT_RANGE_HIGH);
	//cout << "Set Current Range High" << endl;
	cout << "Current: " << luke->getCurrent() * 1000.0  << "mA" << endl;

	//luke->setVoltageRange(VOLTAGE_RANGE_HIGH);
	//cout << "Set Voltage Range High" << endl;
	cout << "Voltage: " << luke->getVoltage() << "V" << endl;

	cout << endl;
	cout << luke->showReg() << endl;
	cout << hex << "DieID: 0x" << luke->getDieID() << endl;

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
