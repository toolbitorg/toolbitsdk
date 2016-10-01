#include <stdio.h>
#include <iostream>
#include <string>
#include "getopt.h"
#include "chopper.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

#define USB_VID 0x4d8
#define USB_PID 0x3f

int main(int argc, char* argv[])
{
    HidChopper *hidchopper = new HidChopper();
    hidchopper->GetDeviceList(USB_VID, USB_PID);

    getoption go(argc, argv);

    while (1) {
        int c = go.get("l");
        if ( c == -1 ) {
            break;
        }

        switch (c) {
            case 'l':
                hidchopper->ShowDeviceList();
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

    if (hidchopper->Open(USB_VID, USB_PID)) {
        cout << "Open HID Device " << endl;
	}

	hidchopper->GetInfo();
	/*
	int i = hidchopper->GetCount();
	cout << "Count: " << dec << i << endl;
	cout << "CountUp" << endl;
	hidchopper->CountUp();
    i = hidchopper->GetCount();
	cout << "Count: " << dec << i << endl;
	*/

	cout << "Product Name: " << hidchopper->GetProductName() << endl;
	cout << "Product Revision: " << hidchopper->GetProductRevision() << endl;
	cout << "Product Serial: " << hidchopper->GetProductSerial() << endl;
	cout << "Firm Version: " << hidchopper->GetFirmVersion() << endl;
	/*
	cout << "ADC ch0: " << hidchopper->GetAdcIn(0) << endl;
	cout << "GPIO dump: " << hidchopper->GetGpioIn() << endl;
	hidchopper->Close();
	*/

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
