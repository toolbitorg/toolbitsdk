/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_I2C_HW_H_
#define TOOLBITSDK_I2C_HW_H_

#include "tbi_core.h"

typedef enum
{
	ATT_I2C_DEVICE_ADDR = 0x00,
	ATT_I2C_REG_ADDR = 0x01,
	ATT_I2C_RW_1BYTE = 0x02,
	ATT_I2C_RW_2BYTE = 0x03,
	ATT_I2C_RW_3BYTE = 0x04,
	ATT_I2C_RW_4BYTE = 0x05
} AttI2cHw;


class I2cHw
{
public:
	I2cHw(TbiService *tbisrv, ToolbitAttributionID base);
	~I2cHw();
	bool setI2cDeviceAddr(uint8_t dev_addr);
	bool write2byte(uint8_t addr, uint16_t val);
	uint16_t read2byte(uint8_t addr);

protected:
	TbiService *mTbiSrv;
	Attribute *mAttI2cDeviceAddr;
	Attribute *mAttI2cRegAddr;
	Attribute *mAttI2cRw1Byte;
	Attribute *mAttI2cRw2Byte;
	Attribute *mAttI2cRw3Byte;
	Attribute *mAttI2cRw4Byte;
};

#endif /* TOOLBITSDK_I2C_HW_H_ */
