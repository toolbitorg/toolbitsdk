/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_TBI_SERVICE_H_
#define TOOLBITSDK_TBI_SERVICE_H_

#include <stdint.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <atomic>
#include "tbi_device.h"
#include "attribute.h"

using namespace std;

#define BUF_LEN 65
#define MAX_STR 255

#define PROTOCOL_VERSION 0x00  // 7-6bits is effective

#define byte uint8_t
#define ATTID uint16_t

typedef struct
{
	uint8_t dat[BUF_LEN];
} tbiPacket;

typedef enum
{
	// Operation Code
	OP_METADATA_GET = 0x10,
	OP_CONFIG_SET,
	OP_ATT_VALUE_SET,
	OP_ATT_VALUE_GET,
	// Event Code
	EVT_NOTIFY = 0xA0
} OperationCode;

typedef enum
{
	// Return Code
	RC_FAIL = 0x0,
	RC_OK   = 0x1,
} ReturnCode;


template <class T>
struct LockedQueue {
	explicit LockedQueue(int capacity)
		: capacity(capacity)
	{}

	void enqueue(const T& x) {
		unique_lock<mutex> lock(m);
		c_enq.wait(lock, [this] { return data.size() != capacity; });
		data.push_back(x);
		c_deq.notify_one();
	}

	T dequeue() {
		unique_lock<mutex> lock(m);
		c_deq.wait(lock, [this] { return !data.empty(); });
		T ret = data.front();
		data.pop_front();
		c_enq.notify_one();
		return ret;
	}

private:
	mutex m;
	deque<T> data;
	size_t capacity;
	condition_variable c_enq;
	condition_variable c_deq;
};

class TbiService {
public:
	TbiService(TbiDevice *p);
	~TbiService();

	bool readAttribute(Attribute *att);
	bool writeAttribute(Attribute att);

private:
	void worker();
	void eventHandler(tbiPacket pckt);
	TbiDevice *tdev;
	thread *th;
	std::atomic<bool> thAbort;
	LockedQueue<tbiPacket> resque;
};

#endif /* TOOLBITSDK_TBI_SERVICE_H_ */
