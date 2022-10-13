#include "FAT16.h"

FAT16::FAT16(wchar_t* path)
{
	byte *dataBuffer = new byte[512];

	if(ReadBootRecord(path,dataBuffer))
	{
		FAT16_BootRecord* pFAT16_BootRecord = (FAT16_BootRecord*)dataBuffer;

		int BPS = GetDec(pFAT16_BootRecord->BPS, sizeof(pFAT16_BootRecord->BPS));   //��������� ���������� ���� � �������
		int SPC = GetDec(&pFAT16_BootRecord->SPC, sizeof(pFAT16_BootRecord->SPC));  //��������� ���������� �������� � ��������
		unsigned long long TotalSector = GetDec(pFAT16_BootRecord->TotalSector, sizeof(pFAT16_BootRecord->TotalSector));   //��������� ������ ���������� ��������

		int Rezerv = GetDec(pFAT16_BootRecord->Rezerv, sizeof(pFAT16_BootRecord->Rezerv));  //��������� ������� ����������������� �������
		int FAT = GetDec(&pFAT16_BootRecord->FAT, sizeof(pFAT16_BootRecord->FAT));   //��������� ���������� ����� ������� FAT
		unsigned long long FATSize = GetDec(pFAT16_BootRecord->FATSize, sizeof(pFAT16_BootRecord->FATSize));    //��������� ������� ������� FAT

		name = "FAT16";                                       //��� �������� �������
		clusterSize = BPS*SPC;                                //������ ��������
		countCluster = (TotalSector-Rezerv-FAT*FATSize)/SPC;  //����������� ���������
		size = countCluster*clusterSize;                      //����� ������
	}

	delete[] dataBuffer;
}




