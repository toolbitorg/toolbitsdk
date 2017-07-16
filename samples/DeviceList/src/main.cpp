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
	devm->showDeviceList();

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
