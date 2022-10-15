#include <iostream>
#include "Decorator.h"

Iterator decorator;

Decorator::Decorator(Iterator iterator)
	{
		decorator=iterator;       //Присвоение данных в перемнной iterator во внутренню перменную декоратора
		File=iterator.File;
		end=File.countCluster;
		First();
		End();
	}


bool Decorator::GetCurrent(byte *dataBuffer)  //Проверка, что кластер является пустым/непустым
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
