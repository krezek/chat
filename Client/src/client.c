#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <windows.h>

#include "game.h"

DWORD dwThreadId;
HANDLE  hThread;

DWORD WINAPI WaitFor(LPVOID lpParam)
{
    unsigned long ulCode;
    const wchar_t* cname = L"rezek";
    printf("Wait for ... %S\n", cname);

    RpcTryExcept
    {
        //WaitForClientMessage((int)wcslen(cname) + 1, &cname);
        SendClientMessage((int)wcslen(cname) + 1, &cname, (int)wcslen(cname) + 1, &cname);
    }
    RpcExcept(1)
    {
        ulCode = RpcExceptionCode();
        printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
    }
    RpcEndExcept

    return 0;
}

void main()
{
    RPC_STATUS status;
    wchar_t* pszUuid = NULL;
    wchar_t* pszProtocolSequence = L"ncacn_ip_tcp";
    wchar_t* pszNetworkAddress = L"localhost";
    wchar_t* pszEndpoint = L"9300";
    wchar_t* pszOptions = NULL;
    wchar_t* pszStringBinding = NULL;
    unsigned long ulCode;

    status = RpcStringBindingCompose(pszUuid,
        pszProtocolSequence,
        pszNetworkAddress,
        pszEndpoint,
        pszOptions,
        &pszStringBinding);
    if (status) exit(status);

    status = RpcBindingFromStringBinding(pszStringBinding, &hello_IfHandle);

    if (status) exit(status);
    //for(;;){
    RpcTryExcept
    {
        wchar_t* info = NULL;
        long size = 0;
        GetServerInfo(&size, &info);
        printf("gsrv> %S\n", info);

        const wchar_t* msg = L"Kinaz";
        TryLogin((int)wcslen(msg) + 1, &msg);

        hThread = CreateThread(NULL, 0, WaitFor, NULL, 0, &dwThreadId);

        if (hThread == NULL)
        {
            fprintf(stderr, "CreateThread error\n");
            ExitProcess(3);
        }

        WaitForSingleObject(hThread, INFINITE);

        CloseHandle(hThread);

        Logout((int)wcslen(msg) + 1, &msg);

        //Shutdown();
    }
        RpcExcept(1)
    {
        ulCode = RpcExceptionCode();
        printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
    }
    RpcEndExcept
    //}
        status = RpcStringFree(&pszStringBinding);

    if (status) exit(status);

    status = RpcBindingFree(&hello_IfHandle);

    if (status) exit(status);

    exit(0);
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR* ptr)
{
    free(ptr);
}
