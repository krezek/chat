#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>

#include "game.h"

int Initialize();
void Destroy();

RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE hInterface, void* pBindingHandle)
{
    return RPC_S_OK; // Always allow anyone.
}


void main()
{
    RPC_STATUS status;
    wchar_t* pszProtocolSequence = L"ncacn_ip_tcp";
    wchar_t* pszSecurity = NULL;
    wchar_t* pszEndpoint = L"9300";
    unsigned int    cMinCalls = 1;
    unsigned int    fDontWait = FALSE;

    if (Initialize())
        exit(-1);

    status = RpcServerUseProtseqEp(pszProtocolSequence,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        pszEndpoint,
        pszSecurity);

    if (status) exit(status);

    status = RpcServerRegisterIf2(
        Game_v1_0_s_ifspec,
        NULL,
        NULL,
        RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        (unsigned)-1,
        SecurityCallback);

    if (status) exit(status);

    status = RpcServerListen(cMinCalls,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        fDontWait);

    if (status) exit(status);

    Destroy();
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
