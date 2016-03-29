#pragma once


#if defined(IMGPOCKET_EXPORTS)
#define IMGPOCKET_API _declspec(dllexport)
#elif !defined(IMGPOCKET_STATIC)
#define IMGPOCKET_API _declspec(dllimport)
#else
#define IMGPOCKET_API
#endif


