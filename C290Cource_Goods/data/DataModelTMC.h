#ifndef DATAMODELTMC_H
#define DATAMODELTMC_H

class TMC {
public: // поля класса
	int Id;        // код товара
	char* Name;    // Наименование
	char* Article; // артикул товара
	char* Measure; // единица измерения
	double Price;  // цена
	double Quant;  // кол-во на складе
	double Limit;  // предельное кол-во на складе
public: // методы класса
	TMC();
	~TMC();
	virtual void Print();
	virtual void Save(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
	virtual void GenTest(); // генератор тестовых данных для отладки
public: // поля и методы для работы с гео.объектом как с элементом двусвязного списка
	TMC* ListNext;
	TMC* ListPred;
	virtual TMC* ListFirst();
	virtual TMC* ListLast();
	virtual int ListCount();
	virtual TMC* ListAdd(TMC* ExistingItem);
	virtual void ListPrint();
	void ListSave(const char* FileName);
};

#endif