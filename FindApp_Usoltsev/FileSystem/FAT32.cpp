#include "FAT32.h"

FAT32::FAT32(wchar_t* path)
{
	byte *dataBuffer = new byte[512];

	if(ReadBootRecord(path,dataBuffer))
	{
		FAT32_BootRecord* pFAT32_BootRecord = (FAT32_BootRecord*)dataBuffer;

		int BPS = GetDec(pFAT32_BootRecord->BPS, sizeof(pFAT32_BootRecord->BPS));   //Получение количества байт в секторе
		int SPC = GetDec(&pFAT32_BootRecord->SPC, sizeof(pFAT32_BootRecord->SPC));  //Получение количества секторов в кластере
		unsigned long long TotalSector = GetDec(pFAT32_BootRecord->TotalSector, sizeof(pFAT32_BootRecord->TotalSector));   //Получение общего количества секторов

		int Rezerv = GetDec(pFAT32_BootRecord->Rezerv, sizeof(pFAT32_BootRecord->Rezerv));  //Получение размера зарезервированной области
		int FAT = GetDec(&pFAT32_BootRecord->FAT, sizeof(pFAT32_BootRecord->FAT));   //Получение количества копий таблицы FAT
		unsigned long long FATSize = GetDec(pFAT32_BootRecord->FATSize, sizeof(pFAT32_BootRecord->FATSize));    //Получение размера таблицы FAT

		name = "FAT32";                                       //Имя файловой системы
		clusterSize = BPS*SPC;                                //Размер кластера
		countCluster = (TotalSector-Rezerv-FAT*FATSize)/SPC;  //Колличество кластеров
		size = countCluster*clusterSize;                      //Общий размер
	}

	delete[] dataBuffer;
}




