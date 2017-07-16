#include <iostream>
#include "tbi_device_manager.h"
#include "tbi_core.h"


TbiDeviceManager::TbiDeviceManager()
{
	devs = NULL;

	updateDeviceList();
}

TbiDeviceManager::~TbiDeviceManager()
{
    if(!devs)
        hid_free_enumeration(devs);
}

void TbiDeviceManager::updateDeviceList()
{
	if (!devs)
		hid_free_enumeration(devs);

	// Enumerate and print the HID devices on the system
	devs = hid_enumerate(USB_VID_PICBIT, USB_PID_PICBIT);

}

void TbiDeviceManager::showDeviceList()
{
	struct hid_device_info *cur_dev;
	TbiCore cur_obj;
	
	cur_dev = devs;
	while (cur_dev) {

		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
			cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);

		if (cur_obj.open(cur_dev->path)) {					
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

const char* TbiDeviceManager::getPath(string name)
{
	struct hid_device_info *cur_dev;
	TbiCore cur_obj;
	const char *path = NULL;

	cur_dev = devs;
	while (cur_dev && !path) {

		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
			cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);

		if (cur_obj.open(cur_dev->path)) {
			if (!name.compare(cur_obj.getProductName()))
				path = cur_dev->path;
			cur_obj.close();
		}
		cur_dev = cur_dev->next;
	}

	return path;
}

int TbiDeviceManager::getDeviceNum()
{
	struct hid_device_info *cur_dev = devs;
	int i = 0;
	while (cur_dev) {
		cur_dev = cur_dev->next;
		i++;
	}
	return i;
}


//
// Protected functions
//
