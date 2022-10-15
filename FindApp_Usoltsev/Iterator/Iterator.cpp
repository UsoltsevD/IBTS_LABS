#include <iostream>
#include "Iterator.h"

Iterator::Iterator(){}
	Iterator::Iterator(FileSystem file){
	 File = file;
	 end = File.countCluster;
	 First();
	 End();
	}

	void Iterator::SetPosition(unsigned long position)       //Задать позицию
	{
		if (position < end)
			Position = position;
	}

	unsigned int Iterator::GetPosition()          //Получить позицию
	{
	  return Position;
	}


	void Iterator::SetDone(unsigned long count)    //Задать пременную Done
	{
		if(Position+count <= end && count > 0)
			Done = Position + count - 1;
	}

	void Iterator::First()                //Задать позицию на начале
	{
	   Position = 0;
	}

	void Iterator::End()                //Задать позицию в конце
	{
	  Done = end;
	}

	void Iterator::Next()               //Задать следующую позицию
	{
	  Position++;
	}

	bool Iterator::IsDone()
	{                                 //Вернуть значение true, если текущая позиция
	return( Position > Done);         // больше, чем позиция, записанная в Done
	}

	bool Iterator::GetCurrent(byte *dataBuffer){       //Считать текущую позицию
		return File.ReadCluster(Position, dataBuffer);
	}





