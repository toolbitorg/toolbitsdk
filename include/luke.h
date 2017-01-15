#ifndef TOOLBITSDK_LUKE_H_
#define TOOLBITSDK_LUKE_H_

#include <stdint.h>
#include "tbi_core.h"
#include "attribute.h"
#include "pic16f145x.h"

// Product specific attribute ID
#define ATT_VOLTAGE_RANGE 0x8100
#define ATT_VOLTAGE       0x8101
#define ATT_CURRENT_RANGE 0x8102
#define ATT_CURRENT       0x8103


typedef enum
{
	VOLTAGE_RANGE_AUTO = 0,
	VOLTAGE_RANGE_LOW = 1,
	VOLTAGE_RANGE_HIGH = 2
} VoltageRange;

typedef enum
{
	CURRENT_RANGE_AUTO = 0,
	CURRENT_RANGE_LOW = 1,
	CURRENT_RANGE_HIGH = 2
} CurrentRange;


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
    // Platform specific attribute ID
	Attribute mAttI2C0Addr;
	Attribute mAttI2C0RW2Byte;
    // Product specific attribute ID
	Attribute mAttVoltageRange;
	Attribute mAttVoltage;
	Attribute mAttCurrentRange;
	Attribute mAttCurrent;
	VoltageRange vrange;
	CurrentRange crange;
};

#endif /* TOOLBITSDK_LUKE_H_ */
