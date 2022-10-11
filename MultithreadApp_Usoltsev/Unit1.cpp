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
	FreeOnTerminate = true;          //����� ����������� �� ���������� ������
	MyEvent = new TEvent(NULL, true, false, "", false);   //�������� ������� ������
	ProcessThreadPtr = new ProcessThread(MyEvent, true);  //�������� ������� ������ � ���������� � ����� ��������
}
//---------------------------------------------------------------------------

void __fastcall Read_Thread::Execute()
{
	DWORD bytes = 512;
	wchar_t MediaType[64];

	UnicodeString deviceName = Form2->Edit1->Text;
	wchar_t MediaType1 = deviceName.w_str()[0];
	swprintf(MediaType,L"\\\\.\\%c:",MediaType1);   //������ � ���������� ����� ����� �� ��������

	//�������� �����
	HANDLE fileHandle = CreateFile(MediaType, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(fileHandle == INVALID_HANDLE_VALUE)   //��������� ������
	{
	   Application->MessageBox(L"������ ������. �� ������� ������� ����.",L"������!", MB_OK);
	   CloseHandle(fileHandle);
	   return;
	}

    bytes = (Form2 -> Edit2 -> Text).ToInt();  //��������� ������
	if (bytes < 512)
	{
		Application->MessageBox(L"������, ���� �� ����� ���� ������, ��� 512 ����!",L"������!", MB_OK);
		CloseHandle(fileHandle);
		return;
	}

	LARGE_INTEGER sectorOffset; //������� ���������������� �� ������ �������
	sectorOffset.QuadPart = 0;

	//������� �� �����������������
	unsigned long currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);

	if(currentPosition != sectorOffset.LowPart)  //��������� ������
	{
	 Application->MessageBox(L"������ ������. ������ ����������������.",L"������!", MB_OK);
	 CloseHandle(fileHandle);
	 return;
	}

	ProcessThreadPtr->Start();     //������ ������� ������

	DWORD bytesToRead = bytes*1024; //������� ������ ����� �������
	BYTE *dataBuffer = new BYTE[bytesToRead]; //��������� ������ ��� ���������, ���� ����� ������������ ������
	DWORD bytesRead;  //������� ������ ������� �������

	while(true)
	{

		bool readResult = ReadFile(fileHandle, dataBuffer, bytesToRead, &bytesRead, NULL);  //������ ������

		if(readResult == false || bytesRead != bytesToRead)  //��������� ������
		{
			Application->MessageBox(L"������ ������. �� ������� ������� ������ ��� ���������� ��������� ������ �� ����� ���������� �������� ������ �� ����������.",L"������!", MB_OK);
			break;
		}

		MyEvent->SetEvent(); //����������� �������� ������ � ���������� ������ � ����������
		Sleep(20);

		while (MyEvent->WaitFor(0) == wrSignaled) //��������, ���� ������ ����� ������� ������
		{
			Sleep(10);
		}
		if(Terminated) break;   //����� �� ������ ������ ������ ��� ����� Terminated
	}
	CloseHandle(fileHandle);          //�������� �����
	ProcessThreadPtr->Terminate();    //��������� ������� ������
	delete ProcessThreadPtr;          //������� ������
}
//---------------------------------------------------------------------------
