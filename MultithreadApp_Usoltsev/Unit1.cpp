//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall Read_Thread::Read_Thread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;          //Вызов деструктора по завершению работы
	MyEvent = new TEvent(NULL, true, false, "", false);   //Создание события потока
	ProcessThreadPtr = new ProcessThread(MyEvent, true);  //Создание второго потока и постановка в режим ожидания
}
//---------------------------------------------------------------------------

void __fastcall Read_Thread::Execute()
{
	DWORD bytes = 512;
	wchar_t MediaType[64];

	UnicodeString deviceName = Form2->Edit1->Text;
	wchar_t MediaType1 = deviceName.w_str()[0];
	swprintf(MediaType,L"\\\\.\\%c:",MediaType1);   //Запись в переменную буквы диска на открытие

	//Открытие диска
	HANDLE fileHandle = CreateFile(MediaType, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(fileHandle == INVALID_HANDLE_VALUE)   //Обработка ошибки
	{
	   Application->MessageBox(L"Ошибка чтения. Не удалось открыть диск.",L"Ошибка!", MB_OK);
	   CloseHandle(fileHandle);
	   return;
	}

    bytes = (Form2 -> Edit2 -> Text).ToInt();  //Обработка ошибки
	if (bytes < 512)
	{
		Application->MessageBox(L"Ошибка, блок не может быть меньше, чем 512 байт!",L"Ошибка!", MB_OK);
		CloseHandle(fileHandle);
		return;
	}

	LARGE_INTEGER sectorOffset; //Задание позиционирования на начале массива
	sectorOffset.QuadPart = 0;

	//Команда на позиционированние
	unsigned long currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);

	if(currentPosition != sectorOffset.LowPart)  //Обработка ошибки
	{
	 Application->MessageBox(L"Ошибка чтения. Ошибка позиционирования.",L"Ошибка!", MB_OK);
	 CloseHandle(fileHandle);
	 return;
	}

	ProcessThreadPtr->Start();     //Запуск второго потока

	DWORD bytesToRead = bytes*1024; //Сколько байтов будет считано
	BYTE *dataBuffer = new BYTE[bytesToRead]; //Выделение памяти для перемнной, куда будут записываться данные
	DWORD bytesRead;  //Сколько байтов удалось считать

	while(true)
	{

		bool readResult = ReadFile(fileHandle, dataBuffer, bytesToRead, &bytesRead, NULL);  //Чтение данных

		if(readResult == false || bytesRead != bytesToRead)  //Обработка ошибки
		{
			Application->MessageBox(L"Ошибка чтения. Не удалось считать данные или количество считанных байтов не равно количеству заданных байтов на считывание.",L"Ошибка!", MB_OK);
			break;
		}

		MyEvent->SetEvent(); //Уведомление воторого потока о готовности данных к считыванию
		Sleep(20);

		while (MyEvent->WaitFor(0) == wrSignaled) //Ожидание, пока второй поток считает данные
		{
			Sleep(10);
		}
		if(Terminated) break;   //Выход из потока чтения данных при флаге Terminated
	}
	CloseHandle(fileHandle);          //Закрытие диска
	ProcessThreadPtr->Terminate();    //Остановка второго потока
	delete ProcessThreadPtr;          //Очистка памяти
}
//---------------------------------------------------------------------------
