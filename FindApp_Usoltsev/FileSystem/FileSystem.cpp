#include "FileSystem.h"

long FileSystem::GetDec(byte vBootRecord[],int size)    //������� ������ � �������������� ����������������� ����
	{
	long sum = 0;
	for (int i = 0; i < size; i++)
		{
			sum+=vBootRecord[i]*std::pow(16,i*2);
		}
	return sum;
	}

bool FileSystem::ReadBootRecord(wchar_t* path,BYTE *dataBuffer)   //��������� ����������� ������
	{
	 if(fileHander!=NULL)
		CloseHandle(fileHander);

	 if(ReadFileHander(path))
		if(ReadCluster(0,dataBuffer))
			return true;

     return false;
	}

bool FileSystem::ReadFileHander(wchar_t* path)   //�������� �����
	{
	fileHander=CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(fileHander == INVALID_HANDLE_VALUE)   //��������� ������
		{
			Application->MessageBox(L"������ ������. �� ������� ������� ����.",L"������!", MB_OK);
			CloseHandle(fileHander);
			return false;
		}
	 return true;
	}

bool FileSystem::ReadCluster(unsigned long long number, BYTE *dataBuffer)  //��������� �������
	{
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart=clusterSize*number;  //������� ����������������

	//������� �� ����������������
	unsigned long long currentPosition = SetFilePointer(fileHander,sectorOffset.LowPart,&sectorOffset.HighPart ,FILE_BEGIN);

	 if(currentPosition != sectorOffset.LowPart)   //��������� ������
		{
			Application->MessageBox(L"������ ������. ������ ����������������.",L"������!", MB_OK);
			return false;
		}

	 DWORD bytesToRead = clusterSize;   //������� ������ ����� �������
	 DWORD bytesRead;                   //������� ������ ������� �������

	 bool readResult = ReadFile(fileHander,dataBuffer,bytesToRead,&bytesRead,NULL);   //������ ������

	 if(readResult == false || bytesRead != bytesToRead)  //��������� ������
		{
			Application->MessageBox(L"������ ������. �� ������� ������� ������.",L"������!", MB_OK);
			return false;
		}
	 return true;
	}

void FileSystem::ViewInfo(TLabel *Label)    //����� �������� �������� �������
	{

		Label->Caption = "�������� �������: ";
		Label->Caption += name;
	}

