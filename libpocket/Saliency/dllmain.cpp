// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

