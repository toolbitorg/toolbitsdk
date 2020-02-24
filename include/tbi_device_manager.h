/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include <stdio.h>
#include <string>
#include <vector>
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

#define USB_VID_NUM_MAX 1

class TbiDeviceManager
{
public:
	TbiDeviceManager();
	~TbiDeviceManager();

	void updateDeviceList();
	int getDeviceNum();
	int getDeviceNum(string name);
	vector<string> getDeviceList();
	vector<string> getSerialList(string name);
	const char* getPathByName(string name);
	const char* getPathByNameAndSerial(string name, string serial);

protected:

private:
    struct hid_device_info *devs[USB_VID_NUM_MAX];
};

#endif /* TOOLBITSDK_TBI_DEVICE_MANAGER_H_ */
