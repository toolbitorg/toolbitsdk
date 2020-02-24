/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include "i2c_hw.h"

I2cHw::I2cHw(TbiService *tbisrv, int base)
{
	mTbiSrv = tbisrv;
	mAttI2cDeviceAddr = new Attribute(base + ATT_I2C_DEVICE_ADDR, 0x00, 0x00);
	mAttI2cRegAddr = new Attribute(base + ATT_I2C_REG_ADDR, 0x00, 0x00);
	mAttI2cRw1Byte = new Attribute(base + ATT_I2C_RW_1BYTE, 0x00, 0x00);
	mAttI2cRw2Byte = new Attribute(base + ATT_I2C_RW_2BYTE, 0x00, 0x00);
	mAttI2cRw3Byte = new Attribute(base + ATT_I2C_RW_2BYTE, 0x00, 0x00);
	mAttI2cRw4Byte = new Attribute(base + ATT_I2C_RW_2BYTE, 0x00, 0x00);
}

I2cHw::~I2cHw()
{
	delete mAttI2cDeviceAddr;
	delete mAttI2cRegAddr;
	delete mAttI2cRw1Byte;
	delete mAttI2cRw2Byte;
	delete mAttI2cRw3Byte;
	delete mAttI2cRw4Byte;
}


bool I2cHw::setI2cDeviceAddr(uint8_t dev_addr)
{
	bool status;

	mAttI2cDeviceAddr->setValue(dev_addr);
	status = mTbiSrv->writeAttribute(*mAttI2cDeviceAddr);
	if (status) {
		// error
		return true;
	}

	return false;
}


bool I2cHw::write2byte(uint8_t reg_addr, uint16_t val)
{
	bool status;

	mAttI2cRegAddr->setValue(reg_addr);
	status = mTbiSrv->writeAttribute(*mAttI2cRegAddr);
	if (status) {
		// error
		return true;
	}

	mAttI2cRw2Byte->setValue(val);
	status = mTbiSrv->writeAttribute(*mAttI2cRw2Byte);
	if (status) {
		// error
		return true;
	}

	return false;
}

uint16_t I2cHw::read2byte(uint8_t reg_addr)
{
	bool status;

	mAttI2cRegAddr->setValue(reg_addr);
	status = mTbiSrv->writeAttribute(*mAttI2cRegAddr);
	if (status) {
		// error
		return 0;
	}

	status = mTbiSrv->readAttribute(mAttI2cRw2Byte);
	if (status) {
		// error
		return 0;
	}
	return mAttI2cRw2Byte->getValueInt16();
}
