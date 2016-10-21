#ifndef TOOLBITSDK_TBI_DEVICE_H_
#define TOOLBITSDK_TBI_DEVICE_H_

#include <stdint.h>
#include <string>
#ifndef _WIN32
#include <chrono>
#include <thread>
#endif
#include "hidapi.h"

using namespace std;

// Macro
#ifdef _WIN32
#include <windows.h>
#define msleep(X) Sleep(X)
#else
#define msleep(X) std::this_thread::sleep_for(std::chrono::milliseconds(X));
#endif

#define BUF_LEN 65   // The first byte is report number so acutual transfer data size is 64
#define MAX_STR 255

#define DEFAULT_DEALY 10   // Wait response for 10msec

class TbiDevice
{
public:
	TbiDevice();
	~TbiDevice();

	void getDeviceList(uint16_t vid, uint16_t pid);
	bool open(uint16_t vid, uint16_t pid);
	bool open(uint16_t vid, uint16_t pid, wchar_t *serial_num);
	bool isOpen();
	bool close();

	bool write(uint8_t *sndbuf, uint8_t num);
	int read(uint8_t *rcvbuf);

	/*
	bool open(int num);

	int GetDeviceNum();
    void ShowDeviceList();

	bool GetInfo();

	bool connectTbi();

	bool SendPacket(uint8_t *sndbuf, uint8_t num);
	bool ReceivePacket(uint8_t *rcvbuf);
	*/

protected:

private:
    struct hid_device_info *devs;
    int deviceNum;
    hid_device *handle;
};

#endif /* TOOLBITSDK_TBI_DEVICE_H_ */
