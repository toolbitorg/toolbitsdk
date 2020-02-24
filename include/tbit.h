/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_TBIT_H_
#define TOOLBITSDK_TBIT_H_

#include "tbi_core.h"
#include "gpio_hw.h"
#include "adc_hw.h"
#include "i2c_hw.h"

// Target MCU
// PIC16F145X
// ATmega32U4

// Platform commom attribute ID
#define ATT_GPIO0_BASE 0x1200
#define ATT_ADC_BASE   0x1300
#define ATT_IC20_BASE  0x1400
// Product specific attribute ID
//

class Tbit : public TbiCore
{
public:
	Tbit();
	~Tbit();

	bool open();
	bool open(string serial);

	// Hardware module
	GpioHw gpiohw;
	AdcHw  adchw;
	I2cHw  i2chw;

protected:
private:
};

#endif /* TOOLBITSDK_TBIT_H_ */
