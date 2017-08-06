#include "i2c.h"


I2c::I2c(TbiService *tbisrv, int base)
{
	mTbiSrv = tbisrv;
	mAttI2cDeviceAddr = new Attribute(base + ATT_I2C_DEVICE_ADDR, 0x00, 0x00);
	mAttI2cRegAddr = new Attribute(base + ATT_I2C_REG_ADDR, 0x00, 0x00);
	mAttI2cRw1Byte = new Attribute(base + ATT_I2C_RW_1BYTE, 0x00, 0x00);
	mAttI2cRw2Byte = new Attribute(base + ATT_I2C_RW_2BYTE, 0x00, 0x00);
	mAttI2cRw3Byte = new Attribute(base + ATT_I2C_RW_2BYTE, 0x00, 0x00);
	mAttI2cRw4Byte = new Attribute(base + ATT_I2C_RW_2BYTE, 0x00, 0x00);
}

I2c::~I2c()
{
	delete mAttI2cDeviceAddr;
	delete mAttI2cRegAddr;
	delete mAttI2cRw1Byte;
	delete mAttI2cRw2Byte;
	delete mAttI2cRw3Byte;
	delete mAttI2cRw4Byte;
}

bool I2c::write(uint8_t reg_addr, uint16_t val)
{
	bool status;

	mAttI2cRegAddr->setValue(reg_addr);
	status = mTbiSrv->writeAttribute(*mAttI2cRegAddr);
	if (!status) {
		// error
		return false;
	}

	mAttI2cRw2Byte->setValue(val);
	status = mTbiSrv->writeAttribute(*mAttI2cRw2Byte);
	if (!status) {
		// error
		return false;
	}

	return true;
}

uint16_t I2c::read(uint8_t reg_addr)
{
	bool status;

	mAttI2cRegAddr->setValue(reg_addr);
	status = mTbiSrv->writeAttribute(*mAttI2cRegAddr);
	if (!status) {
		// error
		return 0;
	}

	status = mTbiSrv->readAttribute(mAttI2cRw2Byte);
	if (!status) {
		// error
		return 0;
	}
	return mAttI2cRw2Byte->getValueInt16();
}
