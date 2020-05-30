#ifndef TGEOOBJECT_H
#define TGEOOBJECT_H

#include "Console.h"

class TGeoObject; // опережающее описание класса

typedef void (*funcOnCoordChange)(TGeoObject *Obj);

class TGeoObject {
private:
	short FX;
	short FY;
public:
	int Id;
	char* Name;
	char* Address;
	int AddressHouse;
	char Symbol;
	Console::ConsoleColors Color;
	Console::ConsoleColors BgColor;
	funcOnCoordChange BeforeCoordChanged;
	funcOnCoordChange AfterCoordChanged;
	TGeoObject();
	~TGeoObject();
	virtual void GenTest();
	virtual void Print();
	virtual void Save(FILE* FileHandle);
	virtual void Draw();
	virtual void Hide();
	virtual short getX();
	virtual void setX(const short aX);
	virtual short getY();
	virtual void setY(const short aY);
	virtual void setXY(const short aX, const short aY);
	virtual char* LoadFromString(char* Text);
public: // поля и методы для работы с гео.объектом как с элементом двусвязного списка
	TGeoObject* ListNext;
	TGeoObject* ListPred;
	virtual TGeoObject* ListFirst();
	virtual TGeoObject* ListLast();
	virtual int ListCount();
	virtual TGeoObject* ListAdd(TGeoObject* ExistingItem);
	virtual void ListDraw();
	void ListSave(const char *FileName);
	virtual bool ListContains(const short aX, const short aY);
	virtual TGeoObject* FindXY(const short aX, const short aY);

};

#endif