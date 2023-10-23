#include "platform.h"

#include "game.h"
#include "map.h"
#include "log.h"

wchar_t about[] = L"This is game Server version 0.0.1";
Map* g_events_map;


int Initialize()
{
    Logger_init();
    Log_info(about);

    g_events_map = Map_init();

    //Map_traversal(g_events_map);
    //Map_remove(g_events_map, L"kinaz");
    //Map_traversal(g_events_map);
    
    return 0;
}

void GetClientIPAddress(wchar_t* ntAddrStr)
{
    RPC_BINDING_HANDLE sb;
    RPC_STATUS status = RpcBindingServerFromClient(NULL, &sb);
    if (status)
    {
        Log_error(L"GetClientIPAddress::RpcBindingServerFromClient");
        return;
    }

    RPC_WSTR buf;
    status = RpcBindingToStringBinding(sb, &buf);
    if (status)
    {
        Log_error(L"GetClientIPAddress::RpcBindingToStringBinding");
        return;
    }

    RPC_WSTR networkAddr;
    status = RpcStringBindingParse(buf, NULL, NULL, &networkAddr, NULL, NULL);
    if (status)
    {
        Log_error(L"GetClientIPAddress::RpcStringBindingParse");
        RpcStringFree(&buf);
        return;
    }

    wcscpy_s(ntAddrStr, wcslen(networkAddr) + 1, networkAddr);

    RpcStringFree(&networkAddr);
    RpcStringFree(&buf);
}

void Destroy()
{
    Map_free(g_events_map);

    Log_info(L"Server stopped");
    Logger_destroy();
}

void GetServerInfo(
    /* [out] */ long* size,
    /* [size_is][size_is][out] */ wchar_t** outString)
{
    *size = (int)wcslen(about) + 1;
    *outString = (wchar_t*)midl_user_allocate(*size * sizeof(wchar_t));
    wcscpy_s(*outString, *size, about);
}

void Shutdown(void)
{
    RPC_STATUS status;

    status = RpcMgmtStopServerListening(NULL);

    if (status)
    {
        exit(status);
    }

    status = RpcServerUnregisterIf(NULL, NULL, FALSE);

    if (status)
    {
        exit(status);
    }
}

int TryLogin(
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t** alias)
{
    wchar_t ipStr[50];
    GetClientIPAddress(ipStr);

    wchar_t logBuf[255];
    wsprintf(logBuf, L"TryLogin:IP(%s) as %s", ipStr, *alias);
    Log_info(logBuf);

    return 0;
}

void Logout(
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t** alias)
{
    printf("Logout'%S'\n", *alias);
}

void WaitForClientMessage(
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t** cname)
{
    DWORD id = GetCurrentThreadId();
    printf("Wait for %d '%S'\n", id, *cname);

    HANDLE event = CreateEvent(
        NULL,               // default security attributes
        TRUE,               // manual-reset event
        FALSE,              // initial state is nonsignaled
        *cname  // object name
    );

    if (event == NULL)
    {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return;
    }

    Map_insert(g_events_map, *cname, event);
    WaitForSingleObject(event, INFINITE);


}

void SendClientMessage(
    /* [in] */ long csize,
    /* [size_is][size_is][in] */ wchar_t** cname,
    /* [in] */ long msize,
    /* [size_is][size_is][in] */ wchar_t** msg)
{
    HANDLE event = (HANDLE)Map_get(g_events_map, L"rezek");

    if (!SetEvent(event))
    {
        printf("SetEvent failed (%d)\n", GetLastError());
        return;
    }

}
