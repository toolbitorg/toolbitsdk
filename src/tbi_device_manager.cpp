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

void TbiDeviceManager::showDeviceList()
{
	struct hid_device_info* cur_dev;
	TbiCore cur_obj;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev) {
			printf("Device found\n");
			printf("  VID: %04hx\n", cur_dev->vendor_id);
			printf("  PID: %04hx\n", cur_dev->product_id);
			printf("  Path: %s\n", cur_dev->path);
			printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
			printf("  Product     : %ls\n", cur_dev->product_string);
			printf("  Serial      : %ls\n", cur_dev->serial_number);
			printf("\n");

			/*
			if (cur_obj.openPath(cur_dev->path)) {
				cout << "  Attribute " << endl;
				cout << "    Product Name: " << cur_obj.getProductName() << endl;
				cout << "    Product Revision: " << cur_obj.getProductRevision() << endl;
				cout << "    Product Serial: " << cur_obj.getProductSerial() << endl;
				cout << "    Firm Version: " << cur_obj.getFirmVersion() << endl;
				cur_obj.close();
			}
			*/

			cur_dev = cur_dev->next;
		}
	}
}

const char* TbiDeviceManager::getPathByName(string name)
{
	struct hid_device_info* cur_dev;
	TbiCore cur_obj;
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
	TbiCore cur_obj;
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


//
// Protected functions
//
