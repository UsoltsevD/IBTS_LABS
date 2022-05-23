#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include "Header.h"
#include "DLL.cpp"


int _tmain(int argc, _TCHAR* argv[])
{
	//system("chcp 1251");
	setlocale(LC_ALL,"RUS");
	std::system("cls");

	std::wcout<<L"Ãðóïïà: "<<	printGroup()<<"\n";

	wchar_t *Pointer;
	Pointer = printFIO();

	wchar_t Result = *Pointer;
	std::wcout<<L"\nÔÈÎ: "<< Pointer <<"\n";

	std::system("pause");
	return 0;
}
