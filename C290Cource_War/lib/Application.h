#ifndef APPLICATION_H
#define APPLICATION_H

class Application;

typedef void(*FuncOnKey)(Application *Sender);

class Application {
public:
	int PressedKey;
	bool Running;
	Application();
	virtual void Run();
	virtual void DoProcessKey(const int AKeyPressed);
	FuncOnKey OnEscape;
	FuncOnKey OnLeft;
	FuncOnKey OnRight;
	FuncOnKey OnUp;
	FuncOnKey OnDown;
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
	virtual void DoOnKeyEscape();
	virtual void DoOnKeyLeft();
	virtual void DoOnKeyRight();
	virtual void DoOnKeyUp();
	virtual void DoOnKeyDown();
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

#endif