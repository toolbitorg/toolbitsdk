/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_GPIO_HW_H_
#define TOOLBITSDK_GPIO_HW_H_

#include "tbi_core.h"

typedef enum
{
	ATT_GPIO_INOUT_MODE = 0x00,
	ATT_GPIO_PULL_UP    = 0x01,
	ATT_GPIO_PULL_DOWN  = 0x02,
	ATT_GPIO_RW         = 0x03
} AttGpioHw;

typedef enum
{
	// Operation Code
	OUTPUT_PIN,
	INPUT_PIN,
	INPUT_PULLUP_PIN,
	INPUT_PULLDOWN_PIN
} PinMode;

#define HIGH 1
#define LOW  0


class GpioHw
{
public:
	GpioHw(TbiService *tbisrv, ToolbitAttributionID base);
	~GpioHw();
	// GPIO
	bool pinMode(uint8_t pin, PinMode mode);
	bool write(uint32_t dat);
	uint32_t read();

	bool digitalWrite(uint8_t pin, bool val);
	bool digitalRead(uint8_t pin);

protected:
	TbiService *mTbiSrv;
	Attribute *mAttGpioInoutMode;
	Attribute *mAttGpioPullUp;
	Attribute *mAttGpioPullDown;
	Attribute *mAttGpioRw;
};

#endif /* TOOLBITSDK_GPIO_HW_H_ */
