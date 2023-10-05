#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "game.h"

wchar_t msg[] = L"This is a game Server version 0.0";

void SrvInfo(
    /* [out] */ long* size,
    /* [size_is][size_is][out] */ wchar_t** outString)
{
    *size = (int)wcslen(msg) + 1;
    *outString = (wchar_t*)midl_user_allocate(*size * sizeof(wchar_t));
    wcscpy_s(*outString, *size, msg);
}

