//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
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
void __fastcall TForm2::Button1Click(TObject *Sender)   //������ ������ ������ ������
{
	Read_Thread_Ptr = new Read_Thread(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)  //������ ��������� ������ ������
{
		Read_Thread_Ptr->Terminate();
}
//---------------------------------------------------------------------------

