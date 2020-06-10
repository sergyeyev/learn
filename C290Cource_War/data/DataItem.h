#ifndef DATAITEM_H
#define DATAITEM_H
#include "../lib/Console.h"

class Item {
public:
	// поля класса
	int Id;     // внутренний код
	char* Name; // название элемента
	Item();  // конструктор класса
	~Item(); // деструктор класса
	// методы класса
	virtual void GenTest();
	virtual char* LoadFromString(char* Text);
	virtual void Print(const short X, const short Y, const Console::ConsoleColors Foreground, const Console::ConsoleColors Background = Console::clBlack);
	virtual void PrintInternal();
public:	// методы класса для работы с классом, как с двусвязным списком
	Item* ListNext;
	Item* ListPred;
	virtual int ListGenId();
	virtual Item* ListFirst();
	virtual Item* ListLast();
	virtual int ListCount();
	virtual Item* ListAdd(Item* ExistingItem);
	virtual void ListSaveToFile(const char* FileName);
	virtual void ListSaveToFileItem(FILE *FileHandle);
	static Item* ListLoadFromFile(const char* FileName);
};

#endif