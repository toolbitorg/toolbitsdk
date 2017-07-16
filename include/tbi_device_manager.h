#include <stdio.h>
#include "hidapi.h"

using namespace std;

#ifndef TOOLBITSDK_TBI_DEVICE_MANAGER_H_
#define TOOLBITSDK_TBI_DEVICE_MANAGER_H_


#define USB_VID_PICBIT 0x4d8
#define USB_PID_PICBIT 0x3f

#define USB_VID_ARDUBIT 0x2341
#define USB_PID_ARDUBIT 0x8036


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
