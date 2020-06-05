#ifndef DATAWARRIOR_H
#define DATAWARRIOR_H

#include "DataItem.h"

class Warrior :public Item {
public:
	// поля класса Воин
	char* Position;
	int Foot;
	int Height;
	// конструктор
	Warrior();
	~Warrior();
	// методы класса
	virtual void GenTest();
public:	// методы класса для работы с классом, как с двусвязным списком
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
};

#endif