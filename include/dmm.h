#ifndef TOOLBITSDK_DMM_H_
#define TOOLBITSDK_DMM_H_

#include <stdint.h>
#include "i2c_hw.h"
#include "attribute.h"

// Platform commom attribute ID
#define ATT_GPIO0_BASE 0x1200
#define ATT_ADC_BASE   0x1300
#define ATT_IC20_BASE  0x1400
// Product specific attribute ID
#define ATT_CALIBRATION   0x8100
#define ATT_VOLTAGE       0x8101
#define ATT_CURRENT       0x8102


class Dmm : public TbiCore
{
public:
	Dmm();
	~Dmm();

	// Hardware module
	I2cHw  i2chw;

	bool open();
	bool calibration();
	float getVoltage();
	float getCurrent();

	string showReg();
	uint16_t getDieID();

protected:

private:
	// Product specific attribute ID
	Attribute* mAttCalibration;
	Attribute* mAttVoltage;
	Attribute* mAttCurrent;
};

#endif /* TOOLBITSDK_DMM_H_ */
