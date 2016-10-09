#ifndef TOOLBITSDK_LUKE_H_
#define TOOLBITSDK_LUKE_H_

#include <stdint.h>
#include "tbi_core.h"
#include "attribute.h"


typedef enum
{
	CURRENT_RANGE_LOW = 0,
	CURRENT_RANGE_HIGH = 1
} CurrentRange;

typedef enum
{
	VOLTAGE_RANGE_LOW = 0,
	VOLTAGE_RANGE_HIGH = 1
} VoltageRange;


class Luke : public TbiCore
{
public:
	Luke();
	~Luke();

	float getVoltage();
	float getCurrent();
	void setVoltageRange(VoltageRange r);
	void setCurrentRange(CurrentRange r);

	string showReg();

protected:

private:
	uint16_t readReg(uint8_t addr);
	bool writeReg(uint8_t addr, uint16_t val);
	uint16_t getDieID();
	Attribute mAttRegAddr;
	Attribute mAttRegVal;
	VoltageRange vrange;
	CurrentRange crange;
};

#endif /* TOOLBITSDK_LUKE_H_ */
