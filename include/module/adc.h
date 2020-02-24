/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_ADC_H_
#define TOOLBITSDK_ADC_H_

#include "tbit.h"

class Adc
{
public:
	Adc(Tbit *p, uint8_t pinnum);
	~Adc();

	int value();

protected:
	Tbit *mTbit;
	uint8_t mPinNum;
	int val;
};

#endif /* TOOLBITSDK_ADC_H_ */
