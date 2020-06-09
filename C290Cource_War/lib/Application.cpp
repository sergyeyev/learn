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
	Console::FillRect(' ', 0, 0, Console::Height()-1, Console::Width()-1 );
	// 
	OnEnter = NULL;
	OnEscape = NULL;
	OnTab = NULL;
	OnSpace = NULL;
	OnBackspace = NULL;
	OnInsert = NULL;
	OnDelete = NULL;
	OnUp = NULL;
	OnDown = NULL;
	OnLeft = NULL;
	OnRight = NULL;
	OnPageUp = NULL;
	OnPageDown = NULL;
	OnHome = NULL;
	OnEnd = NULL;
	OnCenter = NULL;
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
	    case Console::keyBackspace: { DoOnKeyBackspace(); break; };
	    case Console::keySpace: { DoOnKeySpace();     break; };
	    case Console::keyTab: { DoOnKeyTab();       break; };
	    case Console::keyEnter: { DoOnKeyEnter();     break; };
	    case Console::keyInsert: { DoOnKeyInsert();    break; };
	    case Console::keyDelete: { DoOnKeyDelete();    break; };
	    case Console::keyLeft: { DoOnKeyLeft();      break; };
	    case Console::keyRight: { DoOnKeyRight();     break; };
	    case Console::keyUp: { DoOnKeyUp();        break; };
	    case Console::keyDown: { DoOnKeyDown();      break; };
	    case Console::keyPageDown: { DoOnKeyPageDown();  break; };
	    case Console::keyPageUp: { DoOnKeyPageUp();    break; };
	    case Console::keyCenter: { DoOnKeyCenter();    break; };
	    case Console::keyHome: { DoOnKeyHome();      break; };
	    case Console::keyEnd: { DoOnKeyEnd();       break; };
	    case Console::keyEscape: { DoOnKeyEscape(); break; }
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
	}
}

void Application::DoOnKeyEnter()     { if (NULL != OnEnter) { OnEnter(this); } }
void Application::DoOnKeyEscape()    { if (NULL != OnEscape) { OnEscape(this); } }
void Application::DoOnKeyTab()       { if (NULL != OnTab) { OnTab(this); } }
void Application::DoOnKeySpace()     { if (NULL != OnSpace) { OnSpace(this); } }
void Application::DoOnKeyBackspace() { if (NULL != OnBackspace) { OnBackspace(this); } }
void Application::DoOnKeyInsert()    { if (NULL != OnInsert) { OnInsert(this); } }
void Application::DoOnKeyDelete()    { if (NULL != OnDelete) { OnDelete(this); } }
void Application::DoOnKeyLeft()      { if (NULL != OnLeft) { OnLeft(this); } }
void Application::DoOnKeyRight()     { if (NULL != OnRight) { OnRight(this); } }
void Application::DoOnKeyUp()        { if (NULL != OnUp) { OnUp(this); } }
void Application::DoOnKeyDown()      { if (NULL != OnDown) { OnDown(this); } }
void Application::DoOnKeyPageUp()    { if (NULL != OnPageUp) { OnPageUp(this); } }
void Application::DoOnKeyPageDown()  { if (NULL != OnPageDown) { OnPageDown(this); } }
void Application::DoOnKeyHome()      { if (NULL != OnHome) { OnHome(this); } }
void Application::DoOnKeyEnd()       { if (NULL != OnEnd) { OnEnd(this); } }
void Application::DoOnKeyCenter()    { if (NULL != OnCenter) { OnCenter(this); } }
void Application::DoOnKeyF1()        { if (NULL != OnF1    ) OnF1    (this); }
void Application::DoOnKeyF2()        { if (NULL != OnF2    ) OnF2    (this); }
void Application::DoOnKeyF3()        { if (NULL != OnF3    ) OnF3    (this); }
void Application::DoOnKeyF4()        { if (NULL != OnF4    ) OnF4    (this); }
void Application::DoOnKeyF5()        { if (NULL != OnF5    ) OnF5    (this); }
void Application::DoOnKeyF6()        { if (NULL != OnF6    ) OnF6    (this); }
void Application::DoOnKeyF7()        { if (NULL != OnF7    ) OnF7    (this); }
void Application::DoOnKeyF8()        { if (NULL != OnF8    ) OnF8    (this); }
void Application::DoOnKeyF9()        { if (NULL != OnF9    ) OnF9    (this); }
void Application::DoOnKeyF10()       { if (NULL != OnF10   ) OnF10   (this); }
void Application::DoOnKeyF11()       { if (NULL != OnF11   ) OnF11   (this); }
void Application::DoOnKeyF12()       { if (NULL != OnF12   ) OnF12   (this); }


ApplicationConsole::ApplicationConsole() {
	OnCommand = NULL;
	MenuMain = new Menu();
	MenuMain->X = 4;
	MenuMain->Y = 4;
	MenuMain->BgColor         = Console::clBlack;
	MenuMain->Color           = Console::clLightBlue;
	MenuMain->BgColorSelected = Console::clLightBlue;
	MenuMain->ColorSelected   = Console::clBlack;
}

ApplicationConsole::~ApplicationConsole() {
	delete MenuMain;
}

void ApplicationConsole::Run() {
	MenuMain->Draw();
	Application::Run();
}

void ApplicationConsole::DoOnKeyUp() {
	MenuMain->Selected--;
	if (MenuMain->Selected < 0) {
		MenuMain->Selected = MenuMain->GetCount() - 1;
	}
	MenuMain->Draw();
	Application::DoOnKeyUp();
}

void ApplicationConsole::DoOnKeyDown() {
	MenuMain->Selected++;
	if (MenuMain->Selected > (MenuMain->GetCount() - 1)) {
		MenuMain->Selected = 0;
	}
	MenuMain->Draw();
	Application::DoOnKeyDown();
}

void ApplicationConsole::DoOnKeyEnter() {
	DoOnCommand(MenuMain->Selected);
}

void ApplicationConsole::DoOnCommand(int Command) {
	if (NULL != OnCommand) {
		OnCommand(this, Command);
		Console::SetColor(Console::clBlack, Console::clBlack);
		Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
		MenuMain->Draw();
	}
}
