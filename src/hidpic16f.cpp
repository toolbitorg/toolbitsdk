#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidluke.h"


HidPic16f::HidPic16f()
{
}

HidPic16f::~HidPic16f()
{
}

//
// Platform commom commands
//
uint32_t HidPic16f::GetGpioIn()
{
	uint8_t rcvbuf[BUF_LEN];

	if (!SendByteCmd(CMD_GET_ADC_IN, DEFAULT_DEALY, rcvbuf))
			return 0;
	else
		return rcvbuf[0] + (rcvbuf[1] << 8) + (rcvbuf[2] << 16) + (rcvbuf[3] << 24);
}

uint32_t HidPic16f::GetAdcIn(uint8_t ch)
{
	uint8_t rcvbuf[BUF_LEN];

	if (!SendByteCmd(CMD_GET_ADC_IN, ch, DEFAULT_DEALY, rcvbuf))
		return 0;
	else
		return rcvbuf[0] + (rcvbuf[1] << 8);
}

