#ifndef DATAGOODS_H
#define DATAGOODS_H

#include "DataItem.h"

class Good :public Item {
public:
	// поля класса Довольствие
	char* Position;
	int Foot;
	int Height;
	double Massa;
	double Quant;
	// конструктор
	Good();
	~Good();
	// методы класса
	virtual void GenTest();
	virtual void PrintInternal();
public:	// методы класса для работы с классом, как с двусвязным списком
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
	static Good* ListLoadFromFile(const char* FileName);
};

#endif