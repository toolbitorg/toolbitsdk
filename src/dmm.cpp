/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "tbi_device_manager.h"
#include "dmm.h"

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

Dmm::Dmm() :
	i2chw(mTbiService, ATT_IC20_BASE)
{
	mAttCalibration = new Attribute(ATT_CALIBRATION, 0x00, 0x00);
	mAttVoltage = new Attribute(ATT_VOLTAGE, 0x00, 0x00);
	mAttCurrent = new Attribute(ATT_CURRENT, 0x00, 0x00);
}

Dmm::~Dmm()
{
	close();

	delete mAttCalibration;
	delete mAttVoltage;
	delete mAttCurrent;
}

bool Dmm::open()
{
	TbiDeviceManager devm;
	return openPath(devm.getPathByName("DMM"));
}

bool Dmm::open(string serial)
{
	TbiDeviceManager devm;
	return openPath(devm.getPathByNameAndSerial("DMM", serial));
}

bool Dmm::calibration()
{
	// Triger calibration by writting any value on mAttCalibration attribute
	mAttCalibration->setValue(0x00);
	return mTbiService->writeAttribute(*mAttCalibration);
}

string Dmm::getCalibrationData()
{
	stringstream ss;
	if (mTbiService->readAttribute(mAttCalibration)) {
		// error
	}
	else {
		uint32_t dat = mAttCalibration->getValueUint32();
		uint8_t u8;
		int8_t  i8;

		u8 = dat & 0xFF;
		ss << "LOW_CURRENT_OFFSET: " << int(*(int8_t*)& u8)  << endl;
		dat = dat >> 8;
		u8 = dat & 0xFF;
		ss << "HIGH_CURRENT_OFFSET: " << int(*(int8_t*)& u8) << endl;
		dat = dat >> 8;
		u8 = dat & 0xFF;
		ss << "LOW_VOLTAGE_OFFSET: " << int(*(int8_t*)& u8) << endl;
		dat = dat >> 8;
		u8 = dat & 0xFF;
		ss << "HIGH_VOLTAGE_OFFSET: " << int(*(int8_t*)& u8) << endl;
	}
	return ss.str();
}

float Dmm::getVoltage()
{
	if (mTbiService->readAttribute(mAttVoltage)) {
		// error
		return -999.9;
	}
	return mAttVoltage->getValueFloat();
}

float Dmm::getCurrent()
{
	if (mTbiService->readAttribute(mAttCurrent)) {
		// error
		return -999.9;
	}
	return mAttCurrent->getValueFloat();
}

string Dmm::showReg()
{
	stringstream ss;
	for (int addr = 0; addr <= REG_POWER_VALID_LOWER_LIMIT; addr++) {
		ss << hex << addr << ": 0x" << i2chw.read2byte(addr) << endl;
	}
	return ss.str();
}

uint16_t Dmm::getDieID()
{
	return i2chw.read2byte(REG_DIE_ID);
}
