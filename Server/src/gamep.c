#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "game.h"
#include "util.h"

wchar_t about[] = L"This is game Server version 0.0.1";
Map* g_events_map;

int Initialize()
{
    printf("Initialize\n");

    g_events_map = Map_init();
    Map_insert(g_events_map, L"kinaz", (void*)1);
    Map_insert(g_events_map, L"rezek", (void*)2);
    Map_insert(g_events_map, L"rr", (void*)6);
    Map_insert(g_events_map, L"ra", (void*)6);
    Map_insert(g_events_map, L"first", (void*)3);
    Map_insert(g_events_map, L"fr", (void*)4);
    Map_insert(g_events_map, L"fa", (void*)4);
    Map_insert(g_events_map, L"rb", (void*)4);

    Map_traversal(g_events_map);
    Map_remove(g_events_map, L"kinaz");
    Map_traversal(g_events_map);

    return 0;
}

void Destroy()
{
    printf("Destroy\n");

    Map_free(g_events_map);
}

void GetServerInfo(
    /* [out] */ long* size,
    /* [size_is][size_is][out] */ wchar_t** outString)
{
    *size = (int)wcslen(about) + 1;
    *outString = (wchar_t*)midl_user_allocate(*size * sizeof(wchar_t));
    wcscpy_s(*outString, *size, about);
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
