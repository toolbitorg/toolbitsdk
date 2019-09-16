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

	// Enumerate and print the HID devices on the system
	devs[0] = hid_enumerate(USB_VID_PIC, USB_PID_PIC);
	devs[1] = hid_enumerate(USB_VID_ARDUINO, USB_PID_ARDUINO);
}

void TbiDeviceManager::showDeviceList()
{
	struct hid_device_info *cur_dev;
	TbiCore cur_obj;
	
	for (int i = 0; i < USB_VID_NUM_MAX; i++) {
		cur_dev = devs[i];
		while (cur_dev) {

			printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
				cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
			printf("\n");
			printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
			printf("  Product:      %ls\n", cur_dev->product_string);

			if (cur_obj.openPath(cur_dev->path)) {
				cout << "  Attribute " << endl;
				cout << "    Product Name: " << cur_obj.getProductName() << endl;
				cout << "    Product Revision: " << cur_obj.getProductRevision() << endl;
				cout << "    Product Serial: " << cur_obj.getProductSerial() << endl;
				cout << "    Firm Version: " << cur_obj.getFirmVersion() << endl;
				cur_obj.close();
			}

			printf("\n");
			printf("\n");

			cur_dev = cur_dev->next;
		}
	}
}

const char* TbiDeviceManager::getPath(string name)
{
	struct hid_device_info *cur_dev;
	TbiCore cur_obj;
	const char *path = NULL;

	for (int i = 0; i < USB_VID_NUM_MAX; i++) {

		cur_dev = devs[i];
		while (cur_dev && !path) {

			printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
				cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
			printf("\n");
			printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
			printf("  Product:      %ls\n", cur_dev->product_string);

			if (cur_obj.openPath(cur_dev->path)) {
				if (!name.compare(cur_obj.getProductName()))
					path = cur_dev->path;
				cur_obj.close();
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
