/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "tbi_device.h"

TbiDevice::TbiDevice()
{
	handle = NULL;
}

TbiDevice::~TbiDevice()
{
	close();
}


bool TbiDevice::open(uint16_t vid, uint16_t pid)
{
	// Open the device using the VID, PID
	handle = hid_open(vid, pid, NULL);
	if (!handle) {
		fprintf(stderr, "[ERR] Unable to open device\n");
		return true;
	}

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);

	return false;
}

bool TbiDevice::open(uint16_t vid, uint16_t pid, wchar_t *serial_num)
{
	// Open the device using the VID, PID, and Serial number
	handle = hid_open(vid, pid, serial_num);
	if (!handle) {
		fprintf(stderr, "[ERR] Unable to open device\n");
		return true;
	}

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);

	return false;
}

bool TbiDevice::open(const char *path)
{
	// Open the device using path name
	handle = hid_open_path(path);
	if (!handle) {
		fprintf(stderr, "[ERR] Unable to open device\n");
		return true;
	}

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);

	return false;
}

bool TbiDevice::isOpen()
{
	return handle != NULL;
}

bool TbiDevice::close()
{
	if (!handle)
		return true;

	hid_close(handle);
	handle = NULL;
	hid_exit();          // Free static HIDAPI objects

	return false;
}

bool TbiDevice::write(uint8_t *sndbuf, uint8_t num)
{
	uint8_t buf[BUF_LEN];

	if (!handle || (num > BUF_LEN-1))
		return true;

	// Copy sndbuf to buf
	buf[0] = 0x0;       // The first byte is the report number (0x0).
	memcpy(&buf[1], sndbuf, num);

	// Write to HID device
	hid_write(handle, buf, BUF_LEN);

	return false;
}

int TbiDevice::read(uint8_t *rcvbuf)
{
	// Read response from HID device
	return hid_read(handle, rcvbuf, BUF_LEN);
}


//
// Protected functions
//
