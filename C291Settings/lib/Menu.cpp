#include <iostream>
#include "Menu.h"
#include "StringHelper.h"
#include "Console.h"

MenuItem::MenuItem() {
	Id = 0;
	Caption = StringHelper::New(CaptionLength);
	Next = NULL;
}

MenuItem::~MenuItem() {
	free(Caption);
	if (NULL != Next) {
		delete Next;
	}
}

MenuItem* MenuItem::Last() {
	if (NULL == Next) {
		return this;
	}
	else {
		return Next->Last();
	}
};

Menu::Menu() {
	X = 0;
	Y = 0;
	FItems = NULL;
	BgColor         = Console::ConsoleColors::clLightCyan;
	Color           = Console::ConsoleColors::clBlack;
	BgColorSelected = Console::ConsoleColors::clLightBlue;
	ColorSelected   = Console::ConsoleColors::clWhite;
}

Menu::~Menu() {
	Clear();
}

int Menu::GetCount() {
	MenuItem* LItem = FItems;
	int Result = 0;
	while (NULL != LItem) {
		Result++;
		LItem = LItem->Next;
	}
	return Result;
}

int Menu::AddItem(const char* caption) {
	MenuItem* LItem = NULL;
	if (NULL == FItems) {
		FItems = new MenuItem();
		LItem = FItems;
	}
	else {
		LItem = FItems->Last();
		LItem->Next = new MenuItem();
		LItem = LItem->Next;
	}
	LItem->Id = GetCount() - 1;
	strcpy_s(LItem->Caption, MenuItem::CaptionLength, caption);
	return LItem->Id;
};

void Menu::Clear() {
	delete FItems;
}

int Menu::MaxCaptionLen() {
	int Result = 0;
	MenuItem* LItem = FItems;
	while (NULL != LItem) {
		if ((int)strlen(LItem->Caption) > Result) {
			Result = strlen(LItem->Caption);
		}
		LItem = LItem->Next;
	}
	return Result;
}

void Menu::Draw() {
	MenuItem* LItem = FItems;
	int i = 0;
	while (NULL != LItem) {
		Console::GotoXY(X, (Y + (i*2)));
		if (i == Selected) {
			Console::SetColor(ColorSelected, BgColorSelected);
		} else {
			Console::SetColor(Color, BgColor);
		}
		for (int j = 0; j < MaxCaptionLen(); j++) {
			if (j >= strlen(LItem->Caption)) {
				printf(" ");
			}
			else {
				printf("%c", LItem->Caption[j]);
			}
		}
		LItem = LItem->Next;
		i++;
	}
}

void MenuMain::Draw() {
	int LX = X;
	int LY = Y;
	int LCounter = 0;
	// 1. рисуем фон Главного меню программы
	int LScreenWidth = Console::Width();
	/*
		TConsole::GotoXY(LX, LY);
		TConsole::SetColors(Color, BgColor);
		for (int LXBg = LX; LXBg < LScreenWidth;  LXBg++) {
			printf(" ");
		}
	*/
	// 2. отрисовываем пункты Главного меню
	MenuItem* LItem = FItems;
	while (NULL != LItem) {
		Console::GotoXY(LX, LY);
		if (LCounter == Selected) {
			Console::SetColor(ColorSelected, BgColorSelected);
		}else {
			Console::SetColor(Color, BgColor);
		}
		printf("%s", LItem->Caption);
		// вывод разделителя межд пунктами меню
		Console::SetColor(Color, BgColor);
		printf(" ");

		LX += strlen(LItem->Caption) + 1;
		LItem = LItem->Next;
		LCounter++;
	}
	// 3. Вариант2: отрисовка до конца экрана пустого пространства
	Console::GotoXY(LX, LY);
	Console::SetColor(Color, BgColor);
	for (int LXBg = LX; LXBg < LScreenWidth; LXBg++) {
		printf(" ");
	}

}