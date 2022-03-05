// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

void OnAttach(HMODULE hModule);
void OnDetach(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OnAttach(hModule);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        OnDetach(hModule);
        break;
    }
    return TRUE;
}

