#include <iostream>
#include <Windows.h>
#include "UDHeader.h"

int main()
{
    HINSTANCE load;
    load = LoadLibrary(L"VSLibrary_Usoltsev.dll");
    setlocale(LC_ALL, "Russian");
    std::cout << "Группа: " << MyGroup() << "\n";
    std::cout << "Фамилия и Имя: " << MyName() << "\n";

    std::system("pause");
    return 0;
}