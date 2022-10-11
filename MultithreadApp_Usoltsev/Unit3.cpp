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
	FreeOnTerminate = true;      //����� ����������� �� ���������� ������
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::Execute()
{
	i = 0;
	while(true)
	{
		if(MyEvent->WaitFor(0) == wrSignaled)   //���� ����� ����� ������� ������ �� ������� ������, �� ���������
		{
			MyEvent->ResetEvent();             //����� ����� � ���������� ������� ����� ������
		}
		Sleep(200);
		if(Terminated) break;     //���� ���� Terminated, �� ����� �� ������
		Synchronize(&UpdateLabel); //������������� ������
		i++;
	}
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::UpdateLabel()       //��������� ��������� ��������� ������ � �����
{
	Form2->Label2->Caption = UnicodeString(i);
}
