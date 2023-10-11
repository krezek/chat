#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <libpq-fe.h>

#include "game.h"
#include "util.h"
#include "log.h"

wchar_t about[] = L"This is game Server version 0.0.1";
Map* g_events_map;
PGconn* g_conn;

void do_exit(PGconn* conn) {

    PQfinish(conn);
    exit(1);
}

int Initialize()
{
    Logger_init();
    Log_info(about);

    g_events_map = Map_init();

    //Map_traversal(g_events_map);
    //Map_remove(g_events_map, L"kinaz");
    //Map_traversal(g_events_map);

    g_conn = PQconnectdb("user=postgres password=rezekkinaz76 dbname=postgres");

    if (PQstatus(g_conn) == CONNECTION_BAD)
    {
        wchar_t buf[200];
        wsprintf(buf, L"Connection to database failed: %S\n",
            PQerrorMessage(g_conn));
        Log_info(buf);
        PQfinish(g_conn);
        g_conn = NULL;
    }
    else
    {
        int ver = PQserverVersion(g_conn);
        wchar_t buf[50];
        wsprintf(buf, L"Database Server version: %d\n", ver);
        Log_info(buf);
    }
    
    return 0;
}

void Destroy()
{
    Map_free(g_events_map);

    if(g_conn)
        PQfinish(g_conn);

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
    printf("Try to login as '%S'\n", *alias);
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
