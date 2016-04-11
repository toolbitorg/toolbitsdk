#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "hidluke.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

#define USB_VID 0x4d8
//#define USB_PID 0x3f
#define USB_PID 0x54

int main(int argc, char* argv[])
{
    HidLuke *hidluke = new HidLuke();
    hidluke->GetDeviceList(USB_VID, USB_PID);

    getoption go(argc, argv);

    while (1) {
        int c = go.get("fl");
        if ( c == -1 ) {
            break;
        }

        switch (c) {
            case 'f':
                cout << "Bootloader mode" << endl;
                hidluke->Open(0);
                hidluke->BootloaderMode();
                return 0;

            case 'l':
                hidluke->ShowDeviceList();
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

    wchar_t serial_num[] = {'S', 'N', '0', '0', '0', '0', '0', '1', '\0'};

//    if (hidluke->Open(0)) {
    if (hidluke->Open(USB_VID, USB_PID)) {
        cout << "Open HID Device " << endl;
	}

//	hidluke->GetInfo();
	cout << "Product Name: " << hidluke->GetProductName() << endl;
	cout << "Product Revision: " << hidluke->GetProductRevision() << endl;
	cout << "Product Serial: " << hidluke->GetProductSerial() << endl;
	cout << "Firm Version: " << hidluke->GetFirmVersion() << endl;
	cout << "ADC ch0: " << hidluke->GetAdcIn(0) << endl;
	cout << "GPIO dump: " << hidluke->GetGpioIn() << endl;
	hidluke->Close();

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
