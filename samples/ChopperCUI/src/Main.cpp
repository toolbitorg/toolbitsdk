#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>  // Add this for linux
#include "getopt.h"
#include "chopper.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

#define ALL_PORTS 0

int main(int argc, char* argv[])
{
	Chopper *chopper = new Chopper();
	if (!chopper->isConnected())
		return 0;

	uint32_t port = ALL_PORTS;
	
    getoption go(argc, argv);

    while (1) {
        int c = go.get("ls:p:");
        if ( c == -1 ) {
            break;
        }

        switch (c) {			
			case 'l':
                chopper->showDeviceList();
                break;

			case 's':
//				cout << "option s with value " << go.argument() << endl;
				break;

			case 'p':
				if (atoi(go.argument()) <= 0) {
					cout << "Wrong value: " << go.argument() << endl;
					return 0;
				}
				else {
					port = atoi(go.argument());
				}
				break;

            case '?':
              break;

            default:
                cout << "?? getopt returned character code "<< c << "??" << endl;
        }
    }

	int argi = go.optind();  // index of the first non-option ARGV-element

	if (argi==argc || !strcmp(argv[argi], "status")) {

		cout << "Product Name: " << chopper->getProductName() << endl;
		cout << "Product Revision: " << chopper->getProductRevision() << endl;
		cout << "Product Serial: " << chopper->getProductSerial() << endl;
		cout << "Firm Version: " << chopper->getFirmVersion() << endl;

		uint32_t s = chopper->getUsbPortStatus();
		for (int i = 0; i < 2; i++) {
			cout << i + 1 << ": ";
			if (s & 1 << i) {
				cout << "on" << endl;
			}
			else {
				cout << "off" << endl;
			}
		}
	}
	else if (!strcmp(argv[argi], "on")) {
		if (port == ALL_PORTS) {
			chopper->enableAllUsbPort();
			cout << "Enable all USB ports " << endl;
		}
		else {
			chopper->enableUsbPort(port);
			cout << "Enable USB port " << port << endl;
		}
	}
	else if (!strcmp(argv[argi], "off")) {
		if (port == ALL_PORTS) {
			chopper->disableAllUsbPort();
			cout << "Disable all USB ports " << endl;
		}
		else {
			chopper->disableUsbPort(port);
			cout << "Disable USB port " << port << endl;
		}
	}
	else {
		cout << "Unknown option: " << argv[argi] << endl;
	}



#ifdef WIN32
	system("pause");
#endif
	return 0;
}
