#include <iostream>
#include "FabricMethod.h"

//Определение файловой системы на читаемом диске

Factory::Factory(){}

FileSystem Factory::CreateFS(wchar_t* path)
{
	FileSystem File;
	FS fs;
	byte *dataBuffer = new byte[512];

	if(File.ReadBootRecord(path, dataBuffer))  //Чтение загрузочной записи и получение от неё данных
	{
		fs = DefinitionFS(dataBuffer);
	}
	delete[]  dataBuffer;

	switch (fs){                       //Определение использующейся файловой системы

		case(Entfs):
			File = NTFS(path);
		break;

		case(Efat32):
			File = FAT32(path);
		break;

		case(Efat16):
			File = FAT16(path);
		break;
	}
	return  File;
}

FS Factory::DefinitionFS(byte *dataBuffer)     //Определение файловой системы
{
	  byte ntfs[7]={235, 82, 144, 78, 84, 70, 83};          //Первые байты для NTFS
	  byte fat32[7]={235, 88, 144, 77, 83, 68, 79}; 		//Первые байты для FAT32
	  byte fat16[7]={235, 60, 144, 77, 83, 68, 79}; 		//Первые байты для FAT16

	   for( int i=0; i<sizeof(ntfs); i++ )     //Определение NTFS
	   {
		if( ntfs[i]!=dataBuffer[i] )
			break;

		if( i == sizeof(ntfs)-1 )
			return Entfs;
	   }

	   for(int i=0;i<sizeof(fat32);i++)       //Определение FAT32
	   {
		if( fat32[i]!=dataBuffer[i] )
			break;

		if( i == sizeof(fat32)-1)
			return Efat32;
	   }

	   for(int i=0;i<sizeof(fat16);i++)       //Определение FAT32
	   {
		if( fat16[i]!=dataBuffer[i] )
			break;

		if( i == sizeof(fat16)-1)
			return Efat16;
	   }
		throw ERROR;
}
