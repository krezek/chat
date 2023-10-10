#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "game.h"

wchar_t msg[] = L"This is game Server version 0.0.1";

void GetServerInfo(
    /* [out] */ long* size,
    /* [size_is][size_is][out] */ wchar_t** outString)
{
    *size = (int)wcslen(msg) + 1;
    *outString = (wchar_t*)midl_user_allocate(*size * sizeof(wchar_t));
    wcscpy_s(*outString, *size, msg);
}

int TryLogin(
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t** alias)
{
    printf("Try to login as '%S'\n", *alias);
    return 0;
}

void Logout(
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t** alias)
{
    printf("Logout'%S'\n", *alias);
}

void WaitForClient(
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t** cname)
{
    DWORD id = GetCurrentThreadId();
    printf("Wait for %d '%S'\n", id, *cname);
}
