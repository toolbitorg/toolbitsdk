#ifndef TOOLBITSDK_TBIT_H_
#define TOOLBITSDK_TBIT_H_

#include "tbi_core.h"
#include "gpio.h"
#include "adc.h"
#include "i2c.h"

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

	// Hardware module
	Gpio gpio;
	Adc  adc;
	I2c  i2c;

protected:
private:
};

#endif /* TOOLBITSDK_TBIT_H_ */
