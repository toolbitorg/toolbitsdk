/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_TBI_DEVICE_H_
#define TOOLBITSDK_TBI_DEVICE_H_

#include <stdint.h>
#include <string>
#ifndef _WIN32
//#include <chrono>
//#include <thread>
#include <unistd.h>
#endif
#include "hidapi.h"

using namespace std;

// Macro
#ifdef _WIN32
#include <windows.h>
#define msleep(X) Sleep(X)
#else
//#define msleep(X) std::this_thread::sleep_for(std::chrono::milliseconds(X));
#define msleep(X) usleep((X) * 1000)
#endif

#define BUF_LEN 65   // The first byte is report number so acutual transfer data size is 64
#define MAX_STR 255

#define DEFAULT_DEALY 10   // Wait response for 10msec

class TbiDevice
{
public:
	TbiDevice();
	~TbiDevice();

	bool open(uint16_t vid, uint16_t pid);
	bool open(uint16_t vid, uint16_t pid, wchar_t *serial_num);
	bool open(const char *path);
	bool isOpen();
	bool close();

	bool write(uint8_t *sndbuf, uint8_t num);
	int read(uint8_t *rcvbuf);

protected:

private:
    hid_device *handle;
};

#endif /* TOOLBITSDK_TBI_DEVICE_H_ */
