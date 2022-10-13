#include "NTFS.h"

NTFS::NTFS(wchar_t* path)
	{
	byte *dataBuffer = new byte[512];

	if(ReadBootRecord(path,dataBuffer))
		{
			NTFS_BootRecord* pNTFS_BootRecord = (NTFS_BootRecord*)dataBuffer;

			int BPS = GetDec(pNTFS_BootRecord->BPS, sizeof(pNTFS_BootRecord->BPS));   //Получение количества байт в секторе
			int SPC = GetDec(&pNTFS_BootRecord->SPC, sizeof(pNTFS_BootRecord->SPC));      //Получение количества секторов в кластере
			unsigned long long TotalSector = GetDec(pNTFS_BootRecord->TotalSector, sizeof(pNTFS_BootRecord->TotalSector));  //Получение общего количества секторов

			name = "NTFS";                     //Имя файловой системы
			clusterSize = BPS*SPC;             //Размер кластера
			countCluster = TotalSector/SPC;    //Колличество кластеров
			size = countCluster*clusterSize;   //Общий размер
		}

	delete[] dataBuffer;
	}


