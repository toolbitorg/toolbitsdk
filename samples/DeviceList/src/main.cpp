#include <stdio.h>
#include <iostream>
#include <string>
#include "tbi_device_manager.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
	
    TbiDeviceManager *devm = new TbiDeviceManager();
	list<string> devs = devm->getDeviceList();

	devs.unique();

	cout << "Product : Serial" << endl;
	
	for (list<string>::iterator itr = devs.begin(); itr != devs.end(); itr++) {
		list<string> serials = devm->getSerialList(*itr);

		for (list<string>::iterator itr2 = serials.begin(); itr2 != serials.end(); itr2++) {
			cout << *itr << " : " << *itr2 << endl;
		}
	}

	return 0;
}
