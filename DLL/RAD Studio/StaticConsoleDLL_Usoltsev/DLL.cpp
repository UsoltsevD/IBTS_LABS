#pragma hdrstop
#pragma argsused
#include <iostream>
#include "Header.h"
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

extern "C"
{
	int myGroup()
	{
		int GroupNumber = 571227;
		return GroupNumber;
	}

	wchar_t* myName(){
		wchar_t *name = new wchar_t [80];
		wcscpy(name,L"Усольцев Даниил");
		return name;
	}
}

