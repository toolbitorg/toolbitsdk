/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include "pin.h"

Pin::Pin(Tbit* p, uint8_t pinnum)
{
	mTbit = p;
	mPinNum = pinnum;
	val = false;
}

Pin::Pin(Tbit* p, uint8_t pinnum, PinMode m)
{
	mTbit = p;
	mPinNum = pinnum;
	val = false;
	mode(m);
}

Pin::~Pin()
{
}

bool Pin::mode(PinMode m)
{
	mPinMode = m;
	return mTbit->gpiohw.pinMode(mPinNum, mPinMode);
}

bool Pin::value()
{
	return mTbit->gpiohw.digitalRead(mPinNum);
}

bool Pin::value(bool v)
{
	return mTbit->gpiohw.digitalWrite(mPinNum, v);
}

bool Pin::on()
{
	return mTbit->gpiohw.digitalWrite(mPinNum, true);
}

bool Pin::off()
{
	return mTbit->gpiohw.digitalWrite(mPinNum, false);
}
