#include <stdio.h>
#include <string>
#include "hidapi.h"

using namespace std;

#ifndef TOOLBITSDK_TBI_DEVICE_MANAGER_H_
#define TOOLBITSDK_TBI_DEVICE_MANAGER_H_


#define USB_VID_TBIT_PIC 0x4d8
#define USB_PID_TBIT_PIC 0x3f

#define USB_VID_TBIT_ARDUINO 0x2341
#define USB_PID_TBIT_ARDUINO 0x8036


class TbiDeviceManager
{
public:
	TbiDeviceManager();
	~TbiDeviceManager();

	void updateDeviceList();
	void showDeviceList();
	const char* getPath(string name);
	int getDeviceNum();

protected:

private:
    struct hid_device_info *devs;
};

#endif /* TOOLBITSDK_TBI_DEVICE_MANAGER_H_ */
