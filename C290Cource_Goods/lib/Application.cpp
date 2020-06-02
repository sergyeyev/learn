#include <iostream>
#include <conio.h>
#include "Console.h"
#include "Application.h"

Application::Application() {
	PressedLast = 0;
	Running     = false;
	OnRunBefore = NULL;
	OnRunAfter  = NULL;
	OnKeyEscape = NULL;
	OnKeyF1     = NULL;
	OnKeyF2     = NULL;
	OnKeyF3     = NULL;
	OnKeyF4     = NULL;
	OnKeyF5     = NULL;
	OnKeyF6     = NULL;
	OnKeyF7     = NULL;
	OnKeyF8     = NULL;
	OnKeyF9     = NULL;
	OnKeyF10    = NULL;
	OnKeyF11    = NULL;
	OnKeyF12    = NULL;
}

Application::~Application() {

}

void Application::Init() {

}

void Application::Run() {
	Running = true;
	DoOnRunBefore();
	while (Running) {
		DoProcessKey( _getch() );
	}
	DoOnRunAfter();
}

void  Application::DoProcessKey(const int PressedKey) {
	PressedLast = PressedKey;
	switch (PressedKey) { 
	    case Console::keyEscape : {DoOnKeyEscape(); break; }
		case Console::keyF1     : {DoOnKeyF1()    ; break; }
		case Console::keyF2     : {DoOnKeyF2()    ; break; }
		case Console::keyF3     : {DoOnKeyF3()    ; break; }
		case Console::keyF4     : {DoOnKeyF4()    ; break; }
		case Console::keyF5     : {DoOnKeyF5()    ; break; }
		case Console::keyF6     : {DoOnKeyF6()    ; break; }
		case Console::keyF7     : {DoOnKeyF7()    ; break; }
		case Console::keyF8     : {DoOnKeyF8()    ; break; }
		case Console::keyF9     : {DoOnKeyF9()    ; break; }
		case Console::keyF10    : {DoOnKeyF10()   ; break; }
		case Console::keyF11    : {DoOnKeyF11()   ; break; }
		case Console::keyF12    : {DoOnKeyF12()   ; break; }
		default: {
			printf("key pressed = %d \n", PressedKey);
		}
	}
	PressedLast = 0;
}

void Application::DoOnRunBefore() {
	if (NULL != OnRunBefore) {
		OnRunBefore(this);
	}
}

void Application::DoOnRunAfter() {
	if (NULL != OnRunAfter) {
		OnRunAfter(this);
	}
}

// обработка нажатия клавиш
void Application::DoOnKeyEscape() {
	if (NULL != OnKeyEscape) {
		OnKeyEscape(this);
	}
}
void Application::DoOnKeyF1() {	if (NULL != OnKeyF1) { OnKeyF1(this); } }
void Application::DoOnKeyF2() { if (NULL != OnKeyF2) { OnKeyF2(this); } }
void Application::DoOnKeyF3() { if (NULL != OnKeyF3) { OnKeyF3(this); } }
void Application::DoOnKeyF4() { if (NULL != OnKeyF4) { OnKeyF4(this); } }
void Application::DoOnKeyF5() { if (NULL != OnKeyF5) { OnKeyF5(this); } }
void Application::DoOnKeyF6() { if (NULL != OnKeyF6) { OnKeyF6(this); } }
void Application::DoOnKeyF7() { if (NULL != OnKeyF7) { OnKeyF7(this); } }
void Application::DoOnKeyF8() { if (NULL != OnKeyF8) { OnKeyF8(this); } }
void Application::DoOnKeyF9() { if (NULL != OnKeyF9) { OnKeyF9(this); } }
void Application::DoOnKeyF10() { if (NULL != OnKeyF10) { OnKeyF10(this); } }
void Application::DoOnKeyF11() { if (NULL != OnKeyF11) { OnKeyF11(this); } }
void Application::DoOnKeyF12() { if (NULL != OnKeyF12) { OnKeyF12(this); } }


