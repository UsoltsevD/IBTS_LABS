//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Thread_1.h"

#include "FileCtrl.hpp"
#include <fstream>

#include "FabricMethod.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
FileSystem File;


//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------------------------------------------------------------

void __fastcall TForm1::OpenDiskButtonClick(TObject *Sender)   //Кнопка открытия диска
{
	if(Edit1->Text !="")
	{
		Factory Factory;
		UnicodeString str1 = "\\\\.\\";
		UnicodeString str2 = Edit1->Text;      //Получить букву диска
		UnicodeString str3 = ":\\";
		str2+= str3;

		if(str2[str2.Length()] == '\\')
		str2[str2.Length()]='\0';
		str2 = StringReplace(str2,"\\","\\\\",TReplaceFlags()<<rfReplaceAll);
		UnicodeString str4 = str1 + str2 ;

		wchar_t *fileName=str4.t_str();
		File=Factory.CreateFS(fileName);  //Передача пути до диска в фабричный метод для создания ФС

		File.ViewInfo(Label1);   //Вывод названия файловой системы
	}
}

//---------------------------------------------------------------------------
