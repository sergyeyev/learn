#ifndef DATAITEM_H
#define DATAITEM_H

class Item {
public:
	// поля класса
	int Id;     // внутренний код
	char* Name; // название элемента
	Item();  // конструктор класса
	~Item(); // деструктор класса
	// методы класса


public:	// методы класса для работы с классом, как с двусвязным списком
	Item* ListNext;
	Item* ListPred;
	virtual Item* ListFirst();
	virtual Item* ListLast();
	virtual int ListCount();
	virtual Item* ListAdd(Item* ExistingItem);
	virtual void ListSaveToFile(const char* FileName);
	virtual void ListSaveToFileItem(FILE *FileHandle);
	virtual char* LoadFromString(char* Text);
	static Item* ListLoadFromFile(const char* FileName);
};

#endif