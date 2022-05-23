//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Windows.h>
#include "Header.h"
#include <string>

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{

	typedef INT(CALLBACK* PCreateMessageGroup)();
	typedef wchar_t*(CALLBACK* PCreateMessageFIO)();
	HINSTANCE hDLL = NULL;

	PCreateMessageGroup CreateMessageGroup = NULL;
	PCreateMessageFIO CreateMessageFIO = NULL;
	hDLL = LoadLibraryW(L"DLL.dll");

	if (hDLL != NULL) {

		CreateMessageGroup = (PCreateMessageGroup)GetProcAddress(hDLL,"_printGroup");
		CreateMessageFIO = (PCreateMessageFIO)GetProcAddress(hDLL,"_printFIO");

		if (CreateMessageGroup != NULL || CreateMessageFIO != NULL )
		{

			int result = CreateMessageGroup();
			Edit1->Text = result;

			wchar_t* FIO = CreateMessageFIO();

			Edit2->Text = FIO;
		}
		else
		{
			Edit1->Text = "Функция не найдена";
		}
	}
	else
	{
	   Edit1->Text = "Ошибка DLL";
	}

   FreeLibrary(hDLL);
}
//---------------------------------------------------------------------------
