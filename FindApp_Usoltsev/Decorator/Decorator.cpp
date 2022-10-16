#include <iostream>
#include "Decorator.h"

Iterator decorator;

Decorator::Decorator(Iterator iterator)
	{
		decorator=iterator;
		File=iterator.File;
		end=File.countCluster;
		First();
		End();
	}


bool Decorator::GetCurrent(byte *dataBuffer)  //ѕроверка, что кластер €вл€етс€ пустым/непустым
	{
	if(decorator.GetCurrent(dataBuffer))
		{
		for(int i=0; i<512; i++)
			{
				if(dataBuffer[i]!=0)
				return true;
			}
		return false;
		}
	}
