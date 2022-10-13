#include "FAT16.h"

FAT16::FAT16(wchar_t* path)
{
	byte *dataBuffer = new byte[512];

	if(ReadBootRecord(path,dataBuffer))
	{
		FAT16_BootRecord* pFAT16_BootRecord = (FAT16_BootRecord*)dataBuffer;

		int BPS = GetDec(pFAT16_BootRecord->BPS, sizeof(pFAT16_BootRecord->BPS));   //Получение количества байт в секторе
		int SPC = GetDec(&pFAT16_BootRecord->SPC, sizeof(pFAT16_BootRecord->SPC));  //Получение количества секторов в кластере
		unsigned long long TotalSector = GetDec(pFAT16_BootRecord->TotalSector, sizeof(pFAT16_BootRecord->TotalSector));   //Получение общего количества секторов

		int Rezerv = GetDec(pFAT16_BootRecord->Rezerv, sizeof(pFAT16_BootRecord->Rezerv));  //Получение размера зарезервированной области
		int FAT = GetDec(&pFAT16_BootRecord->FAT, sizeof(pFAT16_BootRecord->FAT));   //Получение количества копий таблицы FAT
		unsigned long long FATSize = GetDec(pFAT16_BootRecord->FATSize, sizeof(pFAT16_BootRecord->FATSize));    //Получение размера таблицы FAT

		name = "FAT16";                                       //Имя файловой системы
		clusterSize = BPS*SPC;                                //Размер кластера
		countCluster = (TotalSector-Rezerv-FAT*FATSize)/SPC;  //Колличество кластеров
		size = countCluster*clusterSize;                      //Общий размер
	}

	delete[] dataBuffer;
}




