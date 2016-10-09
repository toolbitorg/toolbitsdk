#include <stdio.h>
#include <wchar.h>
#include <string>
#include <sstream>
#include <stdlib.h>
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
	mAttRegAddr(0x2000, 0x00, 0x00),
	mAttRegVal(0x2001, 0x00, 0x00)
{
	setVoltageRange(VOLTAGE_RANGE_HIGH);
	setCurrentRange(CURRENT_RANGE_HIGH);
}

Luke::~Luke()
{
}

float Luke::getVoltage()
{
	int val = readReg(REG_SHUNTV_3) >> 3;
	if (val & 0x1000) {
		val = val - 0x2000;   // In case of negative number
	}
	if (vrange == VOLTAGE_RANGE_HIGH) {
		return 14.81 / 1000.0 * val;
	}
	else if (vrange == VOLTAGE_RANGE_LOW) {
		return 1.498 / 1000.0 * val;
	}
	return 0.0;
}

float Luke::getCurrent()
{
	if (crange == CURRENT_RANGE_HIGH) {
		int val = readReg(REG_SHUNTV_2) >> 3;
 		if (val & 0x1000) {
			val = val - 0x2000;   // In case of negative number
		}
		return 0.8 / 1000.0 * val;
	}
	else if (crange == CURRENT_RANGE_LOW) {
		int val = readReg(REG_SHUNTV_1) >> 3;
		if (val & 0x1000) {
			val = val - 0x2000;   // In case of negative number
		}
 		return 40.0 / 1000000.0 * val;
	}
}

void Luke::setVoltageRange(VoltageRange r)
{
	if (r == VOLTAGE_RANGE_HIGH) {
		// Set the lowest limit to assert WARNING pin of INA3221
		writeReg(REG_WARNING_LIMIT_1, 0x8000);
		vrange = r;
	}
	else if (r == VOLTAGE_RANGE_LOW) {
		// Set the highest limit to deassert WARNING pin of INA3221
		writeReg(REG_WARNING_LIMIT_1, 0x7FF8);
		vrange = r;
	}
}

void Luke::setCurrentRange(CurrentRange r)
{
	if (r == CURRENT_RANGE_HIGH) {
		// Set the lowest limit to assert CRITICAL pin of INA3221
		writeReg(REG_CRITICAL_LIMIT_1, 0x8000);
		crange = r;
	}
	else if (r == CURRENT_RANGE_LOW) {
		// Set the highest limit to deassert CRITICAL pin of INA3221
		writeReg(REG_CRITICAL_LIMIT_1, 0x7FF8);
		crange = r;
	}
}

string Luke::showReg()
{
	stringstream ss;
	for (int addr = 0; addr <= REG_POWER_VALID_LOWER_LIMIT; addr++) {	
		ss << hex << addr << ": 0x" << readReg(addr) << endl;
	}
	return ss.str();
}

uint16_t Luke::readReg(uint8_t addr)
{
	bool status;

	mAttRegAddr.setValue(addr);
	status = mTbiService->writeAttribute(mAttRegAddr);
	if (!status) {
		// error
		return 0;
	}

	status = mTbiService->readAttribute(&mAttRegVal);
	if (!status) {
		// error
		return 0;
	}
	return mAttRegVal.getValueInt16();
}

bool Luke::writeReg(uint8_t addr, uint16_t val)
{
	bool status;

	mAttRegAddr.setValue(addr);
	status = mTbiService->writeAttribute(mAttRegAddr);
	if (!status) {
		// error
		return false;
	}

	mAttRegVal.setValue(val);
	status = mTbiService->writeAttribute(mAttRegVal);
	if (!status) {
		// error
		return false;
	}

	return true;
}

uint16_t Luke::getDieID()
{
	return readReg(REG_DIE_ID);
}
