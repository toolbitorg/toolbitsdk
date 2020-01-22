#include <stdio.h>
#include <string>
#include "hidapi.h"

using namespace std;

#ifndef TOOLBITSDK_TBI_DEVICE_MANAGER_H_
#define TOOLBITSDK_TBI_DEVICE_MANAGER_H_


// This code is provided by Microchip based on sublicense of USB VID/PID
#define USB_VID_PIC 0x4D8
//#define USB_PID_PIC 0x3f
#define USB_PID_PIC 0xECD0



#define USB_VID_ARDUINO 0x2341
#define USB_PID_ARDUINO 0x8036

#define USB_VID_NUM_MAX 2

class TbiDeviceManager
{
public:
	TbiDeviceManager();
	~TbiDeviceManager();

	void updateDeviceList();
	void showDeviceList();
	const char* getPathByName(string name);
	const char* getPathByNameAndSerial(string name, string serial);
	int getDeviceNum();

protected:

private:
    struct hid_device_info *devs[USB_VID_NUM_MAX];
};

#endif /* TOOLBITSDK_TBI_DEVICE_MANAGER_H_ */
