#ifdef _WIN32
#include <tchar.h>
#endif
#pragma once
#include <string>

extern "C" __declspec(dllexport) int myGroup();
extern "C" __declspec(dllexport) wchar_t* myName();
