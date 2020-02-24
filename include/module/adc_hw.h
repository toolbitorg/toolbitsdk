/*  Toolbit SDK
 *  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 */
#ifndef TOOLBITSDK_ADC_HW_H_
#define TOOLBITSDK_ADC_HW_H_

#include "tbi_core.h"

class AdcHw
{
public:
	AdcHw(TbiService *tbisrv, ToolbitAttributionID base);
	~AdcHw();
	uint32_t analogRead(uint8_t pin);

protected:
	TbiService *mTbiSrv;
	Attribute *mAttAdcR[12];
};

#endif /* TOOLBITSDK_ADC_HW_H_ */
