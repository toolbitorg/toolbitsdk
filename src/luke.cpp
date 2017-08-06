#include <stdio.h>
#include <wchar.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "tbi_device_manager.h"
#include "luke.h"

#define REG_CONFIG 0x00
#define REG_SHUNTV_1 0x01
#define REG_BUSV_1   0x02
#define REG_SHUNTV_2 0x03
#define REG_BUSV_2   0x04
#define REG_SHUNTV_3 0x05
#define REG_BUSV_3   0x06
#define REG_CRITICAL_LIMIT_1 0x07
#define REG_WARNING_LIMIT_1  0x08
#define REG_CRITICAL_LIMIT_2 0x09
#define REG_WARNING_LIMIT_2  0x0A
#define REG_CRITICAL_LIMIT_3 0x0B
#define REG_WARNING_LIMIT_3  0x0C
#define REG_SHUNTV_SUM       0x0D
#define REG_SHUNTV_SUM_LIMIT 0x0E
#define REG_MASK_ENABLE      0x0F
#define REG_POWER_VALID_UPPER_LIMIT 0x10
#define REG_POWER_VALID_LOWER_LIMIT 0x11
#define REG_MANUFACTURER_ID 0xFE
#define REG_DIE_ID 0xFF

Luke::Luke() :
	i2c(mTbiService, ATT_IC20_BASE)
{
	mAttVoltageRange = new Attribute(ATT_VOLTAGE_RANGE, 0x00, 0x00);
	mAttVoltage = new Attribute(ATT_VOLTAGE, 0x00, 0x00);
	mAttCurrentRange = new Attribute(ATT_CURRENT_RANGE, 0x00, 0x00);
	mAttCurrent = new Attribute(ATT_CURRENT, 0x00, 0x00);

	TbiDeviceManager devm;

	if(open(devm.getPath("Luke"))) {

		setVoltageRange(VOLTAGE_RANGE_AUTO);
		setCurrentRange(CURRENT_RANGE_AUTO);

	}
}

Luke::~Luke()
{
	close();

	delete mAttVoltageRange;
	delete mAttVoltage;
	delete mAttCurrentRange;
	delete mAttCurrent;
}

float Luke::getVoltage()
{
	bool status = mTbiService->readAttribute(mAttVoltage);
	if (!status) {
		// error
		return 0.0;
	}
	return mAttVoltage->getValueFloat();
}

float Luke::getCurrent()
{
	bool status = mTbiService->readAttribute(mAttCurrent);
	if (!status) {
		// error
		return 0.0;
	}
	return mAttCurrent->getValueFloat();
}

void Luke::setVoltageRange(VoltageRange r)
{
	mAttVoltageRange->setValue(r);
	bool status = mTbiService->writeAttribute(*mAttVoltageRange);
	if (!status) {
		// error
		return;
	}
}

void Luke::setCurrentRange(CurrentRange r)
{
	mAttCurrentRange->setValue(r);
	bool status = mTbiService->writeAttribute(*mAttCurrentRange);
	if (!status) {
		// error
		return;
	}
}

string Luke::showReg()
{
	stringstream ss;
	for (int addr = 0; addr <= REG_POWER_VALID_LOWER_LIMIT; addr++) {	
		ss << hex << addr << ": 0x" << i2c.read(addr) << endl;
	}
	return ss.str();
}

uint16_t Luke::getDieID()
{
	return i2c.read(REG_DIE_ID);
}
