#ifndef TGEOM_H
#define TGEOM_H

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "consoleroutine.h"

class TGeom {
private:
public:
	int    id;
	char   *name;
	char   *nameupper;
	TGeom();
	virtual ~TGeom();
	virtual int getX();
	virtual void setX(const int X);
	virtual int getY();
	virtual void setY(const int Y);
	virtual char getSymb();
	virtual void setSymb(const char SYMB);
	virtual ConsoleColors getColor();
	virtual void setColor(const ConsoleColors COLOR);
	virtual ConsoleColors getBgColor();
	virtual void setBgColor(const ConsoleColors BGCOLOR);
	virtual int Contains(const short X, const short Y);
	virtual void InitTest();
	virtual void Print();
	virtual void PrintText();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
protected:
	char   symb;
	short  x;
	short  y;
	ConsoleColors color;
	ConsoleColors bgcolor;
};

#endif
