#ifndef APPLICATION_H
#define APPLICATION_H

class Application;

typedef void(*FuncOnKeyDown )(Application *Sender);

class Application {
public: // обработчики событий
	FuncOnKeyDown OnRunBefore;
	FuncOnKeyDown OnRunAfter;
	FuncOnKeyDown OnKeyEscape;
	FuncOnKeyDown OnKeyF1;
	FuncOnKeyDown OnKeyF2;
	FuncOnKeyDown OnKeyF3;
	FuncOnKeyDown OnKeyF4;
	FuncOnKeyDown OnKeyF5;
	FuncOnKeyDown OnKeyF6;
	FuncOnKeyDown OnKeyF7;
	FuncOnKeyDown OnKeyF8;
	FuncOnKeyDown OnKeyF9;
	FuncOnKeyDown OnKeyF10;
	FuncOnKeyDown OnKeyF11;
	FuncOnKeyDown OnKeyF12;
public:
	int PressedLast;
	bool Running;
	Application();
	~Application();
	virtual void Init();
	virtual void Run();
protected:
	virtual void DoOnRunBefore();
	virtual void DoOnRunAfter();
	virtual void DoProcessKey(const int PressedKey = 0);
	virtual void DoOnKeyEscape();
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
