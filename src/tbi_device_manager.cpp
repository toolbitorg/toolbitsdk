/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include <iostream>
#include "tbi_device_manager.h"
#include "tbi_core.h"

TbiDeviceManager::TbiDeviceManager()
{
	for (int i = 0; i < USB_VID_NUM_MAX; i++)
		devs[i] = NULL;

	updateDeviceList();
}

TbiDeviceManager::~TbiDeviceManager()
{
	for (int i = 0; i < USB_VID_NUM_MAX; i++)
		hid_free_enumeration(devs[i]);
}

void TbiDeviceManager::updateDeviceList()
{
	for (int i = 0; i < USB_VID_NUM_MAX; i++)
		hid_free_enumeration(devs[i]);

	devs[0] = hid_enumerate(USB_VID_PIC, USB_PID_PIC);
}

int TbiDeviceManager::getDeviceNum()
{
	struct hid_device_info *cur_dev;
	int num = 0;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev) {
			cur_dev = cur_dev->next;
			num++;
		}
	}
	return num;
}

int TbiDeviceManager::getDeviceNum(string name)
{
	struct hid_device_info *cur_dev;
	int num = 0;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev) {
			if (name==convertWcharToString(cur_dev->product_string)) {
				num++;
			}
			cur_dev = cur_dev->next;
		}
	}
	return num;
}

vector<string> TbiDeviceManager::getDeviceList()
{
	struct hid_device_info* cur_dev;
	vector<string> list;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev) {
			list.push_back(convertWcharToString(cur_dev->product_string));
			cur_dev = cur_dev->next;
		}
	}

	return list;
}

vector<string> TbiDeviceManager::getSerialList(string name)
{
	struct hid_device_info* cur_dev;
	vector<string> list;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev) {
			if (name == convertWcharToString(cur_dev->product_string))
			{
				list.push_back(convertWcharToString(cur_dev->serial_number));
			}
			cur_dev = cur_dev->next;
		}
	}

	return list;
}

const char* TbiDeviceManager::getPathByName(string name)
{
	struct hid_device_info* cur_dev;
	const char* path = NULL;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev && !path) {
			if (name==convertWcharToString(cur_dev->product_string)) {
				path = cur_dev->path;
			}
			cur_dev = cur_dev->next;
		}
	}

	return path;
}

const char* TbiDeviceManager::getPathByNameAndSerial(string name, string serial)
{
	struct hid_device_info* cur_dev;
	const char* path = NULL;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev && !path) {
			if (name==convertWcharToString(cur_dev->product_string)
				&& serial==convertWcharToString(cur_dev->serial_number))
			{
				path = cur_dev->path;
			}
			cur_dev = cur_dev->next;
		}
	}

	return path;
}



//
// Protected functions
//
