#pragma hdrstop
#pragma argsused
#include <string>
#include "Header.h"

extern "C"
{
	__declspec(dllexport) int myGroup()
	{
		int GroupNumber = 571227;
		return GroupNumber;
	}

	__declspec(dllexport) wchar_t* myName()
	{
		wchar_t *name = new wchar_t[80];
		wcscpy(name,L"�������� ������");
		return name;
	}
}

