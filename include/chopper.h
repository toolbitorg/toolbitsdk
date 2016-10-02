#ifndef TOOLBITSDK_CHOPPER_H_
#define TOOLBITSDK_CHOPPER_H_

#include <stdint.h>
#include "tbi_core.h"
#include "attribute.h"

class Chopper : public TbiCore
{
public:
    Chopper();
    ~Chopper();
    
    void CountUp();
    uint8_t GetCount();
protected:

private:
	Attribute mAttCount;
};

#endif /* TOOLBITSDK_CHOPPER_H_ */
