#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Console.h"
#include "Application.h"

Application::Application() {
	// установка локализации по-умолчанию
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// установка параметров экрана по-умолчанию
	Console::SetScreen();
	// очистим экран
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width() );
	// 
	OnLeft     = NULL;
	OnRight    = NULL;
	OnUp       = NULL;
	OnDown     = NULL;
	Running    = false;
	PressedKey = 0;
}

void Application::Run() {
	Running = true;
	while (Running) {
		PressedKey = _getch();
		if ( (0xE0!= PressedKey) && (0 != PressedKey) ) {
			DoProcessKey(PressedKey);
		}
	}
}

void Application::DoProcessKey(const int AKeyPressed) {
	switch (AKeyPressed) {
	    case Console::keyEscape: { DoOnKeyEscape(); break; }
		case Console::keyLeft  : { DoOnKeyLeft  (); break; }
		case Console::keyRight : { DoOnKeyRight (); break; }
		case Console::keyUp    : { DoOnKeyUp    (); break; }
		case Console::keyDown  : { DoOnKeyDown  (); break; }
		case Console::keyF1    : { DoOnKeyF1(); break; }
		case Console::keyF2    : { DoOnKeyF2(); break; }
		case Console::keyF3    : { DoOnKeyF3(); break; }
		case Console::keyF4    : { DoOnKeyF4(); break; }
		case Console::keyF5    : { DoOnKeyF5(); break; }
		case Console::keyF6    : { DoOnKeyF6(); break; }
		case Console::keyF7    : { DoOnKeyF7(); break; }
		case Console::keyF8    : { DoOnKeyF8(); break; }
		case Console::keyF9    : { DoOnKeyF9(); break; }
		case Console::keyF10   : { DoOnKeyF10(); break; }
		case Console::keyF11   : { DoOnKeyF11(); break; }
		case Console::keyF12   : { DoOnKeyF12(); break; }
	    // дл€ вы€снени€ нажатой клавиши, из реального проекта - исключить!!!
		/*
		default: {
			printf("pressed key \"%d\" \n", APressedKey);
			break;
		}
		*/
	}
}

void Application::DoOnKeyEscape() { if (NULL != OnEscape) OnEscape(this); }
void Application::DoOnKeyLeft()   { if (NULL != OnLeft  ) OnLeft  (this); }
void Application::DoOnKeyRight()  { if (NULL != OnRight ) OnRight (this); }
void Application::DoOnKeyUp()     { if (NULL != OnUp    ) OnUp    (this); }
void Application::DoOnKeyDown()   { if (NULL != OnDown  ) OnDown  (this); }
void Application::DoOnKeyF1()     { if (NULL != OnF1    ) OnF1    (this); }
void Application::DoOnKeyF2()     { if (NULL != OnF2    ) OnF2    (this); }
void Application::DoOnKeyF3()     { if (NULL != OnF3    ) OnF3    (this); }
void Application::DoOnKeyF4()     { if (NULL != OnF4    ) OnF4    (this); }
void Application::DoOnKeyF5()     { if (NULL != OnF5    ) OnF5    (this); }
void Application::DoOnKeyF6()     { if (NULL != OnF6    ) OnF6    (this); }
void Application::DoOnKeyF7()     { if (NULL != OnF7    ) OnF7    (this); }
void Application::DoOnKeyF8()     { if (NULL != OnF8    ) OnF8    (this); }
void Application::DoOnKeyF9()     { if (NULL != OnF9    ) OnF9    (this); }
void Application::DoOnKeyF10()    { if (NULL != OnF10   ) OnF10   (this); }
void Application::DoOnKeyF11()    { if (NULL != OnF11   ) OnF11   (this); }
void Application::DoOnKeyF12()    { if (NULL != OnF12   ) OnF12   (this); }
