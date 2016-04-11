#ifndef TOOLBITSDK_LIBHIDCOMM_H_
#define TOOLBITSDK_LIBHIDCOMM_H_

#include <stdint.h>
#include <string>
#include "hidapi.h"

using namespace std;

#define BUF_LEN 65   // The first byte is report number so acutual transfer data size is 64
#define MAX_STR 255

#define DEFAULT_DEALY 10   // Wait response for 10msec

typedef enum
{
	// Basic commands
    CMD_BOOTLOADER_MODE = 0x01,
	CMD_RESET_DEVICE = 0x02,
	CMD_GET_PRODUCT_NAME = 0x10,
	CMD_GET_PRODUCT_REVISION = 0x11,
	CMD_GET_PRODUCT_SERIAL = 0x12,
	CMD_GET_FIRM_VERSION = 0x13,
} HidCommBasicCommands;


class HidComm
{
public:
	HidComm();
	~HidComm();

	void GetDeviceList(uint16_t vid, uint16_t pid);
	int GetDeviceNum();
    void ShowDeviceList();
    bool Open(int num);
	bool Open(uint16_t vid, uint16_t pid);
	bool Open(uint16_t vid, uint16_t pid, wchar_t *serial_num);
    bool IsOpen();
	bool Close();

	bool BootloaderMode();
	bool GetInfo();

	// Basic commands
    string GetProductName();
	string GetProductRevision();
	string GetProductSerial();
	string GetFirmVersion();


protected:
	bool Write(uint8_t *sndbuf);
	bool Read(uint8_t *rcvbuf);
	bool SendCmd(uint8_t *sndbuf, uint32_t t, uint8_t *rcvbuf);
	bool SendByteCmd(uint8_t cmd, uint32_t t, uint8_t *rcvbuf);
	bool SendByteCmd(uint8_t cmd, uint8_t arg1, uint32_t t, uint8_t *rcvbuf);
	bool SendByteCmd(uint8_t cmd, uint32_t arg1, uint32_t t, uint8_t *rcvbuf);
	bool SendByteCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint32_t t, uint8_t *rcvbuf);

private:
    struct hid_device_info *devs;
    int deviceNum;
    hid_device *handle;
};

#endif /* TOOLBITSDK_LIBHIDCOMM_H_ */
