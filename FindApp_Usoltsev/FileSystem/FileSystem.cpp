#include "FileSystem.h"

long FileSystem::GetDec(byte vBootRecord[],int size)    //Функция чтения и преобразования шестнадцатиричных байт
	{
	long sum = 0;
	for (int i = 0; i < size; i++)
		{
			sum+=vBootRecord[i]*std::pow(16,i*2);
		}
	return sum;
	}

bool FileSystem::ReadBootRecord(wchar_t* path,BYTE *dataBuffer)   //Прочитать загрузочную запись
	{
	 if(fileHander!=NULL)
		CloseHandle(fileHander);

	 if(ReadFileHander(path))
		if(ReadCluster(0,dataBuffer))
			return true;

     return false;
	}

bool FileSystem::ReadFileHander(wchar_t* path)   //Открытие диска
	{
	fileHander=CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(fileHander == INVALID_HANDLE_VALUE)   //Обработка ошибки
		{
			Application->MessageBox(L"Ошибка чтения. Не удалось открыть диск.",L"Ошибка!", MB_OK);
			CloseHandle(fileHander);
			return false;
		}
	 return true;
	}

bool FileSystem::ReadCluster(unsigned long long number, BYTE *dataBuffer)  //Прочитать кластер
	{
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart=clusterSize*number;  //Задание позиционирования

	//Команда на позиционирование
	unsigned long long currentPosition = SetFilePointer(fileHander,sectorOffset.LowPart,&sectorOffset.HighPart ,FILE_BEGIN);

	 if(currentPosition != sectorOffset.LowPart)   //Обработка ошибки
		{
			Application->MessageBox(L"Ошибка чтения. Ошибка позиционирования.",L"Ошибка!", MB_OK);
			return false;
		}

	 DWORD bytesToRead = clusterSize;   //Сколько байтов будет считано
	 DWORD bytesRead;                   //Сколько байтов удалось считать

	 bool readResult = ReadFile(fileHander,dataBuffer,bytesToRead,&bytesRead,NULL);   //Чтение данных

	 if(readResult == false || bytesRead != bytesToRead)  //Обработка ошибки
		{
			Application->MessageBox(L"Ошибка чтения. Не удалось считать данные.",L"Ошибка!", MB_OK);
			return false;
		}
	 return true;
	}

void FileSystem::ViewInfo(TLabel *Label)    //Вывод названия файловой системы
	{

		Label->Caption = "Файловая система: ";
		Label->Caption += name;
	}

