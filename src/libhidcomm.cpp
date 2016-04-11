#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "libhidcomm.h"

// Macro
#ifdef _WIN32
#include <windows.h>
#define msleep(X) Sleep(X)
#else
#define msleep(X) usleep((X) * 1000)
#endif


HidComm::HidComm()
{
	handle = NULL;
	devs = NULL;
}

HidComm::~HidComm()
{
    Close();
    if(!devs)
        hid_free_enumeration(devs);
}

void HidComm::GetDeviceList(uint16_t vid, uint16_t pid)
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

int HidComm::GetDeviceNum()
{
    return deviceNum;
}

void HidComm::ShowDeviceList()
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

bool HidComm::Open(int num)
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

bool HidComm::Open(uint16_t vid, uint16_t pid)
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

bool HidComm::Open(uint16_t vid, uint16_t pid, wchar_t *serial_num)
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

bool HidComm::IsOpen()
{
	return handle != NULL;
}

bool HidComm::Close()
{
	if (!handle)
		return false;

	hid_close(handle);
	hid_exit();          // Free static HIDAPI objects

	return true;
}

//
// Basic commands
//
bool HidComm::BootloaderMode()
{
	unsigned char buf[BUF_LEN];

	if (!handle)
		return false;

	// Go to bootloader entry
	buf[0] = 0x0;
	buf[1] = CMD_BOOTLOADER_MODE;
	hid_write(handle, buf, BUF_LEN);

	hid_close(handle);
	hid_exit();          // Free static HIDAPI objects
	handle = NULL;

	return true;
}

bool HidComm::GetInfo()
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

string HidComm::GetProductName()
{
	uint8_t rcvbuf[BUF_LEN];

	if (!SendByteCmd(CMD_GET_PRODUCT_NAME, DEFAULT_DEALY, rcvbuf))
		return "";
	else
		return string((char*)rcvbuf);
}

string HidComm::GetProductRevision()
{
	uint8_t rcvbuf[BUF_LEN];

	if (!SendByteCmd(CMD_GET_PRODUCT_REVISION, DEFAULT_DEALY, rcvbuf))
		return "";
	else
		return string((char*)rcvbuf);
}

string HidComm::GetProductSerial()
{
	uint8_t rcvbuf[BUF_LEN];

	if (!SendByteCmd(CMD_GET_PRODUCT_SERIAL, DEFAULT_DEALY, rcvbuf))
		return "";
	else
		return string((char*)rcvbuf);
}

string HidComm::GetFirmVersion()
{
	uint8_t rcvbuf[BUF_LEN];

	if (!SendByteCmd(CMD_GET_FIRM_VERSION, DEFAULT_DEALY, rcvbuf))
		return "";
	else
		return string((char*)rcvbuf);
}

//
// Protected functions
//
bool HidComm::Write(uint8_t *sndbuf)
{
	uint8_t buf[BUF_LEN];

	if (!handle)
		return false;

	// Copy sndbuf to buf
	buf[0] = 0x0;       // The first byte is the report number (0x0).
	memcpy(&buf[1], sndbuf, BUF_LEN);

	// Write to HID device
	hid_write(handle, buf, BUF_LEN);

	return true;
}

bool HidComm::Read(uint8_t *rcvbuf)
{
	uint8_t buf[BUF_LEN];

	if (!handle)
		return false;

	// Read from HID device
	int res = hid_read(handle, buf, BUF_LEN);
	if (res < 0)
		return false;
    buf[BUF_LEN-1] = '\0';   // The last element is always empty
	memcpy(rcvbuf, buf, BUF_LEN);

	return true;
}

bool HidComm::SendCmd(uint8_t *sndbuf, uint32_t t, uint8_t *rcvbuf)
{
	uint8_t buf[BUF_LEN];

	// Send command to HID device
	if(!Write(sndbuf))
		return false;
	
	msleep(t);

	// Read response from HID device
	int res = hid_read(handle, buf, BUF_LEN);
	if (res < 0)
		return false;
	if (*buf != *sndbuf)   // Check echo back
		return false;
    buf[BUF_LEN-1] = '\0';   // The last element is always empty
    memcpy(rcvbuf, &buf[1], BUF_LEN);

    return true;
}

bool HidComm::SendByteCmd(uint8_t cmd, uint32_t t, uint8_t *rcvbuf)
{
	uint8_t sndbuf[BUF_LEN];
	sndbuf[0] = cmd;
	return SendCmd(sndbuf, t, rcvbuf);
}

bool HidComm::SendByteCmd(uint8_t cmd, uint8_t arg1, uint32_t t, uint8_t *rcvbuf)
{
	uint8_t sndbuf[BUF_LEN];
	sndbuf[0] = cmd;
	sndbuf[1] = arg1;
	return SendCmd(sndbuf, t, rcvbuf);
}

bool HidComm::SendByteCmd(uint8_t cmd, uint32_t arg1, uint32_t t, uint8_t *rcvbuf)
{
	uint8_t sndbuf[BUF_LEN];
	sndbuf[0] = cmd;
	sndbuf[1] = uint8_t(arg1 & 0x0FF);
	sndbuf[2] = uint8_t((arg1 << 8) & 0x0FF);
	sndbuf[3] = uint8_t((arg1 << 16) & 0x0FF);
	sndbuf[4] = uint8_t((arg1 << 24) & 0x0FF);
	return SendCmd(sndbuf, t, rcvbuf);
}

bool HidComm::SendByteCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint32_t t, uint8_t *rcvbuf)
{
	uint8_t sndbuf[BUF_LEN];
	sndbuf[0] = cmd;
	sndbuf[1] = arg1;
	sndbuf[2] = arg2;
	return SendCmd(sndbuf, t, rcvbuf);
}


