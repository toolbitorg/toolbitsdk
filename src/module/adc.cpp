/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include "adc.h"

Adc::Adc(Tbit *p, uint8_t pinnum)
{
	mTbit = p;
	mPinNum = pinnum;
	val = 0;
}

Adc::~Adc()
{
}

int Adc::value()
{
	return mTbit->adchw.analogRead(mPinNum);
}
