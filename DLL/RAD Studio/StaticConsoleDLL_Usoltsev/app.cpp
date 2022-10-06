#pragma hdrstop
#pragma argsused

typedef char _TCHAR;

#include <stdio.h>
#include <iostream>
#include "Header.h"
#include "DLL.cpp"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"RUS");
	std::system("cls");

	std::wcout<<L"Группа: "<< myGroup() <<"\n";

	wchar_t *name;
	name = myName();

	wchar_t Result = *name;
	std::wcout<<L"Фамилия и Имя: "<< name <<"\n";

	std::system("pause");
	return 0;
}
