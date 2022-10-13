#pragma once
#include "Thread_1.h"
#include <iostream>

class FileSystem {
protected:

	HANDLE fileHander;
	long GetDec(byte vBootRecord[], int size);

public:
	unsigned long long size = 512;
	unsigned long long countCluster = 1;
	int clusterSize = 512;
    String name;

	bool ReadBootRecord(wchar_t* path, BYTE *dataBuffer);
    bool ReadFileHander(wchar_t* path);
	bool ReadCluster(unsigned long long number, BYTE *dataBuffer);
	void ViewInfo(TLabel *Label);
};



