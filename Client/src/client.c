#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <windows.h>

#include "game.h" 

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

    RpcTryExcept
    {
        wchar_t* info = NULL;
        long size = 0;
        GetServerInfo(&size, &info);
        printf("gsrv> %S\n", info);

        const wchar_t* msg = L"Kinaz";
        TryLoggin((int)wcslen(msg) + 1, &msg);
        Logout((int)wcslen(msg) + 1, &msg);
    }
        RpcExcept(1)
    {
        ulCode = RpcExceptionCode();
        printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
    }
    RpcEndExcept

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
