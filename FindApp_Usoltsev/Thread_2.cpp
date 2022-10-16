//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <sqlite3.h>
#include <typeinfo>

#include "Thread_2.h"
#include "Thread_1.h"

#include "Decorator.h"
#include "CheckSign.h"

#pragma package(smart_init)
unsigned long count;
__fastcall Thread2::Thread2(FileSystem file,bool CreateSuspended)
	: TThread(CreateSuspended)
{
	File = file;
}

//---------------------------------------------------------------------------

void __fastcall Thread2::Execute()
{
	Form1->OpenDiskButton->Enabled=false;  //Отключение кнопки поиска на время выполнения
	count = 0;
	DWORD clusterScan = 512;
	char const * db_name = "Database.db";

	sqlite3 *DataBase;

	int openResult = sqlite3_open(db_name,&DataBase);

		if(openResult != 0)    //Обработка ошибки
		{
			Application->MessageBox(L"Ошибка чтения. Не удалось открыть базу данных.",L"Ошибка!", MB_OK);
			sqlite3_close(DataBase);
			return;
		}

	clusterScan = (Form1->Edit2->Text).ToInt();
	static_cast<long long>(clusterScan);
	if(clusterScan > 1000000)    //Обработка ошибки
		{
			Application->MessageBox(L"Время выполнение запроса будет достаточно большим."
			" Пожалуйста, укажите меньшее количество обрабатываемых кластеров.",L"Ошибка!", MB_OK);
			sqlite3_close(DataBase);
			return;
		}

	Iterator iterator = Iterator(File);

	if(File.countCluster != 0)
	{
		iterator.First();
		iterator.SetDone(clusterScan);
		byte *dataBuffer = new byte[File.clusterSize];
		CheckSign check;

		for(;!iterator.IsDone();iterator.Next())
		{
			if(iterator.GetCurrent(dataBuffer))
			{
				UnicodeString type = check.CheckSigns(dataBuffer);    //Передача на проверку
				count++;
				if(count%clusterScan==0)
					Synchronize(&UpdateTable);  //Обновление счётчика кластеров
				if(type!="NON")
				{
					AnsiString sql="INSERT INTO FILE (ID, NAME) VALUES ("+(AnsiString)iterator.GetPosition()+", \""+ type +"\" );";
					sqlite3_exec(DataBase, sql.c_str(), NULL, 0, NULL);     //Запись строки в базу данных
				}

			 }
		}
		delete[] dataBuffer;
	}
	sqlite3_close(DataBase);
	Synchronize(&End);
}

//---------------------------------------------------------------------------

void __fastcall Thread2::UpdateTable()     //Обновление формы для записи результатов
{
  Form1->ReloadViewDB();
  Form1->Label2->Caption="Кластеров считано: ";
  Form1->Label2->Caption += count;

}

//---------------------------------------------------------------------------

void __fastcall Thread2::End()          //Финальное обновление формы
{
  Form1->OpenDiskButton->Enabled=true;
  Form1->ReloadViewDB();
}
