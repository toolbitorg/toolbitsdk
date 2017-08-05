#ifndef TOOLBITSDK_LUKE_H_
#define TOOLBITSDK_LUKE_H_

#include <stdint.h>
#include "tbit.h"
#include "attribute.h"

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


class Luke : public Tbit
{
public:
	Luke();
	~Luke();

	float getVoltage();
	float getCurrent();
	void setVoltageRange(VoltageRange r);
	void setCurrentRange(CurrentRange r);

	string showReg();
	uint16_t getDieID();

protected:

private:
	// Product specific attribute ID
	Attribute mAttVoltageRange;
	Attribute mAttVoltage;
	Attribute mAttCurrentRange;
	Attribute mAttCurrent;
	VoltageRange vrange;
	CurrentRange crange;
};

#endif /* TOOLBITSDK_LUKE_H_ */
