#ifndef APPLICATION_H
#define APPLICATION_H

#include "Menu.h"

class Application;

typedef void(*FuncOnKey)(Application *Sender);

class Application {
public:
	int PressedKey;
	bool Running;
	Application();
	virtual void Run();
	virtual void DoProcessKey(const int AKeyPressed);
	FuncOnKey OnEnter;
	FuncOnKey OnEscape;
	FuncOnKey OnTab;
	FuncOnKey OnSpace;
	FuncOnKey OnBackspace;
	FuncOnKey OnInsert;
	FuncOnKey OnDelete;
	FuncOnKey OnUp;
	FuncOnKey OnDown;
	FuncOnKey OnLeft;
	FuncOnKey OnRight;
	FuncOnKey OnPageUp;
	FuncOnKey OnPageDown;
	FuncOnKey OnHome;
	FuncOnKey OnEnd;
	FuncOnKey OnCenter;
	FuncOnKey OnF1;
	FuncOnKey OnF2;
	FuncOnKey OnF3;
	FuncOnKey OnF4;
	FuncOnKey OnF5;
	FuncOnKey OnF6;
	FuncOnKey OnF7;
	FuncOnKey OnF8;
	FuncOnKey OnF9;
	FuncOnKey OnF10;
	FuncOnKey OnF11;
	FuncOnKey OnF12;
protected:
	virtual void DoOnKeyEnter();
	virtual void DoOnKeyEscape();
	virtual void DoOnKeyTab();
	virtual void DoOnKeySpace();
	virtual void DoOnKeyBackspace();
	virtual void DoOnKeyInsert();
	virtual void DoOnKeyDelete();
	virtual void DoOnKeyLeft();
	virtual void DoOnKeyRight();
	virtual void DoOnKeyUp();
	virtual void DoOnKeyDown();
	virtual void DoOnKeyPageUp();
	virtual void DoOnKeyPageDown();
	virtual void DoOnKeyHome();
	virtual void DoOnKeyEnd();
	virtual void DoOnKeyCenter();
	virtual void DoOnKeyF1();
	virtual void DoOnKeyF2();
	virtual void DoOnKeyF3();
	virtual void DoOnKeyF4();
	virtual void DoOnKeyF5();
	virtual void DoOnKeyF6();
	virtual void DoOnKeyF7();
	virtual void DoOnKeyF8();
	virtual void DoOnKeyF9();
	virtual void DoOnKeyF10();
	virtual void DoOnKeyF11();
	virtual void DoOnKeyF12();
};

class ApplicationConsole;

typedef void(*funcOnCommand)(ApplicationConsole* Sender, int Command);

class ApplicationConsole : public Application {
protected:
	virtual void DoOnKeyUp();
	virtual void DoOnKeyDown();
	virtual void DoOnKeyEnter();
	virtual void DoOnCommand(int Command);
public:
	Menu* MenuMain;
	funcOnCommand OnCommand;
	ApplicationConsole();
	~ApplicationConsole();
	virtual void Run();
};

#endif