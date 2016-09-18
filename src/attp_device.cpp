#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "attp_device.h"

AttpDevice::AttpDevice()
{
	handle = NULL;
	devs = NULL;
}

AttpDevice::~AttpDevice()
{
    Close();
    if(!devs)
        hid_free_enumeration(devs);
}

void AttpDevice::GetDeviceList(uint16_t vid, uint16_t pid)
{
    if (!devs)
        hid_free_enumeration(devs);
    
    // Enumerate and print the HID devices on the system
	devs = hid_enumerate(vid, pid);

/*
	struct hid_device_info *cur_dev;

    cur_dev = devs;	
	while (cur_dev) {
		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
			cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);
		printf("\n");
		cur_dev = cur_dev->next;
	}
    handle = hid_open_path(devs->path);
 */
    
    struct hid_device_info *cur_dev = devs;
    int i = 0;
	while (cur_dev) {
		cur_dev = cur_dev->next;
        i++;
	}
    deviceNum = i;
}

int AttpDevice::GetDeviceNum()
{
    return deviceNum;
}

void AttpDevice::ShowDeviceList()
{
	struct hid_device_info *cur_dev;
    
    cur_dev = devs;
	while (cur_dev) {
		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
			cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);
		printf("\n");
		cur_dev = cur_dev->next;
	}
}

bool AttpDevice::Open(int num)
{
    if (!devs)
        return false;
    
    struct hid_device_info *cur_dev = devs;
    int i = 0;
	while(i<num) {
        i++;
		cur_dev = cur_dev->next;
        if(!cur_dev) break;
	}
    if(!cur_dev)
        return false;

    handle = hid_open_path(cur_dev->path);
    
	if (!handle) {
		fprintf(stderr, "[ERR] Unable to open device\n");
		return false;
	}
    
	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);
    
	return true;
}

bool AttpDevice::Open(uint16_t vid, uint16_t pid)
{
	// Open the device using the VID, PID
    handle = hid_open(vid, pid, NULL);
	if (!handle) {
		fprintf(stderr, "[ERR] Unable to open device\n");
		return false;
	}

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);
    
	return true;
}

bool AttpDevice::Open(uint16_t vid, uint16_t pid, wchar_t *serial_num)
{
	// Open the device using the VID, PID, and Serial number
	handle = hid_open(vid, pid, serial_num);
	if (!handle) {
		fprintf(stderr, "[ERR] Unable to open device\n");
		return false;
	}

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);

	return true;
}

bool AttpDevice::IsOpen()
{
	return handle != NULL;
}

bool AttpDevice::Close()
{
	if (!handle)
		return false;

	hid_close(handle);
	hid_exit();          // Free static HIDAPI objects

	return true;
}


bool AttpDevice::GetInfo()
{
	wchar_t wstr[MAX_STR];

	if (!handle)
		return false;

	// Read the Manufacturer String
	int res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	wprintf(L"Manufacturer String: %s\n", wstr);

	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	wprintf(L"Product String: %s\n", wstr);

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	wprintf(L"Serial Number String: (%d) %s\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	wprintf(L"Indexed String 1: %s\n", wstr);

	return true;
}

bool AttpDevice::connectAttp()
{

}

bool AttpDevice::SendPacket(uint8_t *sndbuf, uint8_t num)
{
	uint8_t buf[BUF_LEN];

	if (!handle || (num > BUF_LEN-1))
		return false;
    
	// Copy sndbuf to buf
	buf[0] = 0x0;       // The first byte is the report number (0x0).
    memcpy(&buf[1], sndbuf, num);

	// Write to HID device
	hid_write(handle, buf, BUF_LEN);

	return true;
}

bool AttpDevice::ReceivePacket(uint8_t *rcvbuf)
{
	// Read response from HID device
	int res = hid_read(handle, rcvbuf, BUF_LEN);
    if (res < 0)
		return false;
    
    return true;
}


//
// Protected functions
//
