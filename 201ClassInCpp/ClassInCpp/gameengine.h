#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "tcircle.h"
#include "list2link.h"




class GameEngine {

	typedef void(*funcOnKeyDown)(GameEngine *Sender);
	typedef void(*funcOnKeyUp)(GameEngine *Sender);
	typedef void(*funcOnKeyRight)(GameEngine *Sender);
	typedef void(*funcOnKeyLeft)(GameEngine *Sender);
	typedef void(*funcOnKeyF1)(GameEngine *Sender);

	typedef void(*funcOnKeyEscape)(GameEngine *Sender, int _Running);
	typedef void(*funcOnKeyDelete)(GameEngine *Sender);
	typedef void(*funcOnKeyF1)(GameEngine *Sender);
	typedef void(*funcOnKeyF2)(GameEngine *Sender);
	typedef void(*funcOnKeyF3)(GameEngine *Sender);
	typedef void(*funcOnKeyF4)(GameEngine *Sender);
	typedef void(*funcOnKeyF5)(GameEngine *Sender);
	typedef void(*funcOnKeyF6)(GameEngine *Sender);
	
private:
	int Running;


public:
	TGeom *boom;
	TRect *Console;
	TPoint *Tank;
	list2 *Map;
	GameEngine();
	~GameEngine();
	void Run();
	int  getRunning();
	void setRunning(const int value);
	list2 *Map_add_TPoint(list2 *Map, short x, short y, TPointType t,
		ConsoleColors color, ConsoleColors bgcolor);

 	funcOnKeyLeft onKeyLeft;
	funcOnKeyRight onKeyRight;
	funcOnKeyUp onKeyUp	;
	funcOnKeyDown onKeyDown;
	funcOnKeyDelete onKeyDelete;
	funcOnKeyEscape onKeyEscape;
	funcOnKeyF1 onKeyF1;
	funcOnKeyF2 onKeyF2;
	funcOnKeyF3 onKeyF3;
	funcOnKeyF4 onKeyF4;
	funcOnKeyF5 onKeyF5;
	funcOnKeyF6 onKeyF6;
	

protected:
	virtual void doRunBefore();
	virtual void doRunAfter();
	virtual void doProcessKeyBefore();
	virtual void doProcessKeyAfter();
	virtual void doProcessKey(int pressedKey);
	virtual void doKeyEscape();
	virtual void doKeyLeft();
	virtual void doKeyRight();
	virtual void doKeyUp();
	virtual void doKeyDown();
	virtual void doKeyF1();
	virtual void doKeyF2();
	virtual void doKeyF3();
	virtual void doKeyF4();
	virtual void doKeyF5();
	virtual void doKeyF6();
	virtual void doKeyF7();
	virtual void doKeyF8();
	virtual void doKeyF9();
	virtual void doKeyF10();
	virtual void doKeyF11();
	virtual void doKeyF12();
};

#endif