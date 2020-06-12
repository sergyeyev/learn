#ifndef MENU_H
#define MENU_H
#include "Console.h"

class MenuItem {
public:
	static const int CaptionLength = 40;
	int Id;
	char* Caption;
	MenuItem* Next;
	MenuItem();
	~MenuItem();
	virtual MenuItem* Last();
};

class Menu {
protected:
	MenuItem* FItems;
public:
	short X;
	short Y;
	int Selected;
	Console::ConsoleColors BgColor;
	Console::ConsoleColors Color;
	Console::ConsoleColors BgColorSelected;
	Console::ConsoleColors ColorSelected;
	Menu();
	~Menu();
	int GetCount();
	int AddItem(const char* caption);
	void Clear();
	int MaxCaptionLen();
	virtual void Draw();
};

class MenuMain :public Menu {
public:
	virtual void Draw();
};

#endif