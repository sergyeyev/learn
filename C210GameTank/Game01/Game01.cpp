#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include "../ApplicationConsts.h"
#include "../Console.h"
#include "../StringHelper.h"
#include "../TGeoObject.h"
#include "../TGeoObjectBank.h"
#include "../TGeoObjectHouse.h"
#include "../TGeoObjectShop.h"
#include "../TGeoObjectTank.h"
#include "../TGeoObject_Utils.h"
#include "../Environment.h"
#include "../Directory.h"
#include "../Path.h"

void Tank_BeforeCoordChanged(TGeoObject* Obj) {
	Obj->Hide();
}

void Tank_AfterCoordChanged(TGeoObject* Obj) {
	Obj->Draw();
}

int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// 0. подготовка и проверка путей
	char* AppMapFileName = Environment::GetFolderPath(Environment::MyDocuments);
	Environment::SetCurrentDir(AppMapFileName);
	if (!Directory::Exists(ApplicationFolder)) {
		Directory::Create(ApplicationFolder);
	}
	Path::Combine(AppMapFileName, ApplicationFolder);
	Path::Combine(AppMapFileName, DefaultMapFile);
	// очистить поле консоли перед работой 
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(0, 0, Console::Width(), Console::Height());
	// вывод подсказки польтзователю
	// 1. формируем текст подсказки
	char* HelpString = StringHelper::New();
	strcpy_s(HelpString, StringHelper::DefaultSize, "Esc Выход |");
	// 2. выводим текст подсказки
	Console::SetColor(Console::clBlack, Console::clLightCyan);
	Console::FillRect(0, 0, Console::Width(), 1);
	Console::GotoXY(0, 0);
	printf("%s", HelpString);
	free(HelpString);


	// массив географических объектов
	TGeoObject* Objects = LoadFromFile(AppMapFileName);

	TGeoObjectTank* Tank = new TGeoObjectTank();
	Tank->setXY( Console::Width() / 2, Console::Height() / 2);
	Tank->BeforeCoordChanged = &Tank_BeforeCoordChanged;
	Tank->AfterCoordChanged  = &Tank_AfterCoordChanged;
	
	if (NULL != Objects) {
		Objects->ListDraw();
	}
	Tank->Draw();
	int key = _getch();
	while (key != Console::keyEscape) {
		short LX = Tank->getX();
		short LY = Tank->getY();
		switch (key) {
		    case Console::keyLeft : { LX--; break; };
		    case Console::keyRight: { LX++; break; };
			case Console::keyUp   : { LY--; break; };
		    case Console::keyDown : { LY++; break; };
		}
		if (!(LX >= 0)) { LX = 0;}
		if (!(LX < Console::Width())) { LX = Console::Width()-1;}
		if (!(LY > 0)) { LY = 1; }
		if (!(LY < Console::Height())) { LY = Console::Height()-1; }
		if (NULL != Objects) {
			if (!Objects->ListContains(LX, LY)) {
				Tank->setXY(LX, LY);
			}
		}
		key = _getch();
	}


	if (NULL != Objects) {
		Objects = Objects->ListLast();
		while (NULL != Objects) {
			TGeoObject* LItemToDelete = Objects;
			Objects = Objects->ListPred;
			delete LItemToDelete;
		}
	}
	delete Tank;
	free(AppMapFileName);

	// воcстанавливаем консоль
	Console::GotoXY(0, 28);
	Console::SetColor(Console::DefaultColor, Console::DefaultBgColor);
	return 0;
}