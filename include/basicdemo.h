#ifndef TOOLBITSDK_BASICDEMO_H_
#define TOOLBITSDK_BASICDEMO_H_

#include <stdint.h>
#include "tbi_core.h"
#include "attribute.h"

class BasicDemo : public TbiCore
{
public:
    BasicDemo();
    ~BasicDemo();
    
	void CountUp();
	uint8_t GetCount();
protected:

private:
	Attribute mAttCount;
};

#endif /* TOOLBITSDK_BASICDEMO_H_ */
