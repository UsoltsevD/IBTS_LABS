//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ProcessThread::ProcessThread(TEvent* MyEvent, bool CreateSuspended)
	: TThread(CreateSuspended), MyEvent(MyEvent)
{
	FreeOnTerminate = true;      //Вызов деструктора по завершению работы
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::Execute()
{
	i = 0;
	while(true)
	{
		if(MyEvent->WaitFor(0) == wrSignaled)   //Если поток готов принять данные из первого потока, то принимаем
		{
			MyEvent->ResetEvent();             //Сброс флага о готовности принять новые данные
		}
		Sleep(200);
		if(Terminated) break;     //Если флаг Terminated, то выход из потока
		Synchronize(&UpdateLabel); //Синхронизация потока
		i++;
	}
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::UpdateLabel()       //Иммитация обработки считанных данных с диска
{
	Form2->Label2->Caption = UnicodeString(i);
}
