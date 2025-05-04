#pragma once

#ifdef BIGN_SHARED
#if defined(_WIN32)
#ifdef BIGN_PRIVATE
#define BIGN_API __declspec(dllexport)
#else
#define BIGN_API __declspec(dllimport)
#endif
#else
#if __GNUC__ >= 4
#define BIGN_API __attribute__ ((visibility ("default")))
#else
#define BIGN_API
#endif
#endif
#else
#define BIGN_API
#endif
