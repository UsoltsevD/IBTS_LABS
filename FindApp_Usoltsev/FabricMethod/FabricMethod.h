#include <tchar.h>
#include <windows.h>
#include "NTFS.h"
#include "FAT32.h"
#include "FAT16.h"

enum FS {Entfs , Efat32, Efat16};

class Factory
{
public:
	Factory();
	FileSystem CreateFS(wchar_t* path);
private:
	FS DefinitionFS(byte *dataBuffer);
};


