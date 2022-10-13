#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#include "FileSystem.h"

class FAT16 : public FileSystem
{
public:
	FAT16(wchar_t* path);
};

#pragma pack(push,1)

typedef struct
{
	byte Text[0x0B];
	byte BPS[2];
	byte SPC;
	byte Rezerv[2];
	byte FAT;
	byte Skip[5];
	byte FATSize[2];
	byte skip[8];
	byte TotalSector[4];
} FAT16_BootRecord;

#pragma pack(pop)

#endif
