//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Thread_1.h"
#include "Thread_2.h"

#include "FileCtrl.hpp"
#include <sqlite3.h>
#include <fstream>

#include "FabricMethod.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
FileSystem File;

char const *db_name = "Database.db";  //База данных, для записи выведенных значений

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1->NodeDataSize = sizeof(TreeNodeStruct);  //Задание размера узла
	Thread2Ptr = NULL;
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

		ofstream out(db_name);   //Создание потока вывода для базы данных
		out.close();

		AnsiString str = "CREATE TABLE FILE (ID INT NOT NULL, NAME TEXT NOT NULL);";  //Создание SQL запроса для базы данных
		sqlite3 *DataBase;     //Объявление перменной для базы данных

		if ( sqlite3_open(db_name,&DataBase)) //Открытие базы данных и сразу же обработка, при возникновении ошибки
		{
			ShowMessage("Невозможно окрыть базу данных: " + (String)sqlite3_errmsg(DataBase));
			sqlite3_close(DataBase);     //Закрытие базы данных при ошибке
		}
		sqlite3_exec(DataBase, str.c_str(), NULL, 0, NULL); //Передача SQL запроса в базу данных

		Thread2Ptr = new Thread2(File,false); //Создание второго потока
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

//Определение колонок в VirtualStringView
{
  TreeNodeStruct *nodeData = (TreeNodeStruct*) VirtualStringTree1->GetNodeData(Node);

	switch(Column)
	{
		case 0:
		{
			CellText = nodeData->clusterNum;
			break;
		}
		case 1:
		{
			CellText = nodeData->name;
			break;
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::ClearDBButtonClick(TObject *Sender)  //Кнопка очистки таблицы и базы данных
{
		AnsiString str="DELETE from FILE;";
		SQLtoDB(str);
		VirtualStringTree1->Clear();
		Form1->Label2->Caption="Кластеров считано: ";
		Form1->Label1->Caption="Файловая система: ";
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteStringButtonClick(TObject *Sender)   //Кнопка удаления записи из таблицы и из базы данных
{
	PVirtualNode numstr =  VirtualStringTree1->GetFirstSelected();

	if(numstr==NULL)
	 {
		return;
	 }

	TreeNodeStruct *nodeData = (TreeNodeStruct*) VirtualStringTree1->GetNodeData(numstr);
	AnsiString str="DELETE from FILE where id = "+(AnsiString)nodeData->clusterNum +" ;";
	SQLtoDB(str);
	ReloadViewDB();
}

//---------------------------------------------------------------------------

void TForm1::ReloadViewDB()
{
	VirtualStringTree1->Clear();
	VirtualStringTree1->BeginUpdate();

	AnsiString str = "Select * from FILE ;";
	sqlite3 *DataBase;
	sqlite3_stmt *pStatement;
	int stepResult,stringsCount,i;

	int openResult = sqlite3_open(db_name,&DataBase); //Открытие базы данных

	if(openResult != 0)     //Обработка ошибки
	{
		Application->MessageBox(L"Ошибка чтения. Не удалось открыть базу данных.",L"Ошибка!", MB_OK);
		sqlite3_close(DataBase);
		return;
	}

	int prepResult = sqlite3_prepare(DataBase, str.c_str(), -1, &pStatement, NULL);

	if(prepResult != 0)
	{
		Application->MessageBox(L"Ошибка в запросе к базе данных.",L"Ошибка!", MB_OK);
		sqlite3_finalize(pStatement);
		sqlite3_close(DataBase);
	}

	while((stepResult = sqlite3_step(pStatement)) == SQLITE_ROW)
	{
		PVirtualNode entryNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);    //Создание узла
		TreeNodeStruct *nodeData = (TreeNodeStruct*) VirtualStringTree1->GetNodeData(entryNode); //Заполнение данных узла
		stringsCount = sqlite3_data_count(pStatement);

		for(i=0; i<stringsCount; i++)
		{
		AnsiString answer;
		answer.printf("%s",sqlite3_column_text(pStatement, i));
		switch (i)
			{
				case 0:
				{
					nodeData->clusterNum = answer.ToInt();;
					break;
				}
				case 1:
				{
					nodeData->name = UnicodeString(answer);
					break;
				}
			}
		}
	}

	sqlite3_finalize(pStatement);
	sqlite3_close(DataBase);
	VirtualStringTree1->EndUpdate();
}

//---------------------------------------------------------------------------

void TForm1::SQLtoDB(AnsiString str){     //Запрос к базе данных

		sqlite3 *DataBase;

		int openResult = sqlite3_open(db_name,&DataBase);

		if(openResult != 0)     //Обработка ошибки
		{
			Application->MessageBox(L"Ошибка чтения. Не удалось открыть базу данных.",L"Ошибка!", MB_OK);
			sqlite3_close(DataBase);
			return;
		}

		sqlite3_exec(DataBase, str.c_str(), NULL, 0,NULL);
		sqlite3_close(DataBase);
}
