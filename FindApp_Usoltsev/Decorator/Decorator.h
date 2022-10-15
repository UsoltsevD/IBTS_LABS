#include <tchar.h>
#include <windows.h>

#include "Iterator.h"

class Decorator : public Iterator
{
public:
	Decorator(Iterator iterator);
	bool GetCurrent(byte *dataBuffer) override;
};



