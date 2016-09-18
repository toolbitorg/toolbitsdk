#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

#include "attp_service_callback.h"


AttpServiceCallback::AttpServiceCallback()
{

}

AttpServiceCallback::~AttpServiceCallback()
{

}

void AttpServiceCallback::~AttpServiceCallback()
{

}

bool onAttributeRead(AttpService attps, AttpService att, int status);
bool onAttributeWrite(AttpService attps, AttpService att, int status);
bool onAttributeChanged(AttpService attps, AttpService att);
