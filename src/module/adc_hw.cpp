/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#include "adc_hw.h"

AdcHw::AdcHw(TbiService *tbisrv, ToolbitAttributionID base)
{
	mTbiSrv = tbisrv;
	for (int i = 0; i<8; i++)
		mAttAdcR[i] = new Attribute(base + i, 0x00, 0x00);
}

AdcHw::~AdcHw()
{
	for (int i = 0; i < 8; i++)
		delete mAttAdcR[i];
}

uint32_t AdcHw::analogRead(uint8_t pin)
{
	if (pin >= 8)
		return 0xFFFFFFFF;  // error

	bool status = mTbiSrv->readAttribute(mAttAdcR[pin]);
	if (status)
		return 0xFFFFFFFF;   // error
	return mAttAdcR[pin]->getValueUint32();
}
