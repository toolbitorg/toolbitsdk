/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_PIN_H_
#define TOOLBITSDK_PIN_H_

#include "tbit.h"

class Pin
{
public:
	Pin(Tbit *p, uint8_t pinnum);
	Pin(Tbit *p, uint8_t pinnum, PinMode mode);
	~Pin();

	bool mode(PinMode m);
	bool value();
	bool value(bool v);
	bool on();
	bool off();

protected:
	Tbit *mTbit;
	uint8_t mPinNum;
	bool val;
	PinMode mPinMode;
};

#endif /* TOOLBITSDK_PIN_H_ */
