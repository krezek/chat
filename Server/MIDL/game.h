

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for game.idl, game.acf:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __game_h__
#define __game_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __Game_INTERFACE_DEFINED__
#define __Game_INTERFACE_DEFINED__

/* interface Game */
/* [implicit_handle][version][uuid] */ 

void GetServerInfo( 
    /* [out] */ long *size,
    /* [size_is][size_is][out] */ wchar_t **outString);

void Shutdown( void);

int TryLogin( 
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t **alias);

void Logout( 
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t **alias);

void WaitForClientMessage( 
    /* [in] */ long size,
    /* [size_is][size_is][in] */ wchar_t **cname);

void SendClientMessage( 
    /* [in] */ long csize,
    /* [size_is][size_is][in] */ wchar_t **cname,
    /* [in] */ long msize,
    /* [size_is][size_is][in] */ wchar_t **msg);


extern handle_t hello_IfHandle;


extern RPC_IF_HANDLE Game_v1_0_c_ifspec;
extern RPC_IF_HANDLE Game_v1_0_s_ifspec;
#endif /* __Game_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


