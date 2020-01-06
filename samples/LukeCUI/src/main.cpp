#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "dmm.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
    Dmm *dmm = new Dmm();
/*
	if (!dmm->isConnected()) {
		cout << "Fail to connect to dmm " << endl;
		return 1;
	}
	*/

	cout << "ProductName: " << dmm->getProductName() << endl;
	cout << "ProductRevision: " << dmm->getProductRevision() << endl;
	cout << "ProductSerial: " << dmm->getProductSerial() << endl;
	cout << "ProductVersion: " << dmm->getFirmVersion() << endl;

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

	//dmm->setCurrentRange(CURRENT_RANGE_HIGH);
	//cout << "Set Current Range High" << endl;
	cout << "Current: " << dmm->getCurrent() * 1000.0  << "mA" << endl;

	//dmm->setVoltageRange(VOLTAGE_RANGE_HIGH);
	//cout << "Set Voltage Range High" << endl;
	cout << "Voltage: " << dmm->getVoltage() << "V" << endl;

	cout << endl;
	cout << dmm->showReg() << endl;
	cout << hex << "DieID: 0x" << dmm->getDieID() << endl;

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
