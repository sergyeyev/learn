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

TGeoObject* AddBank(TGeoObject *Obj, const int x, const int y) {
	TGeoObject* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjectBank();
		LResult->GenTest();
		LResult->setXY(x, y);
	} else {
		if (!Obj->ListContains(x, y)) {
			LResult = Obj->ListAdd(new TGeoObjectBank());
			LResult->GenTest();
			LResult->setXY(x, y);
		} else {
			LResult = Obj;
		}
	}
	return LResult;
}

TGeoObject* AddShop(TGeoObject* Obj, const int x, const int y) {
	TGeoObject* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjectShop();
		LResult->GenTest();
		LResult->setXY(x, y);
	} else {
		if (!Obj->ListContains(x, y)) {
			LResult = Obj->ListAdd(new TGeoObjectShop());
			LResult->GenTest();
			LResult->setXY(x, y);
		} else {
			LResult = Obj;
		}
	}
	return LResult;
}

TGeoObject* AddHouse(TGeoObject* Obj, const int x, const int y) {
	TGeoObject* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjectHouse();
		LResult->GenTest();
		LResult->setXY(x, y);
	} else {
		if (!Obj->ListContains(x, y)) {
			LResult = Obj->ListAdd(new TGeoObjectHouse());
			LResult->GenTest();
			LResult->setXY(x, y);
		} else {
			LResult = Obj;
		}
	}
	return LResult;
}

TGeoObject* DeleteObject(TGeoObject* Obj, const int x, const int y) {
	TGeoObject* LResult = Obj;

	return LResult;
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

	// очистить поле консоли перед работой редактора карт
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(0, 0, Console::Width(), Console::Height());
	// вывод подсказки польтзователю
    // 1. формируем текст подсказки
	char* HelpString = StringHelper::New();
	strcpy_s(HelpString, StringHelper::DefaultSize, "Esc Выход | F4 Дом | F5 Банк | F6 Магазин |");
	// 2. выводим текст подсказки
	Console::SetColor(Console::clBlack, Console::clLightCyan);
	Console::FillRect(0, 0, Console::Width(), 1);
	Console::GotoXY(0, 0);
	printf("%s", HelpString);
	free(HelpString);

	// массив географических объектов
	TGeoObject* Objects = LoadFromFile(AppMapFileName);
	// Ручка для рисования на консоли
	TGeoObjectTank* Pen = new TGeoObjectTank();
	Pen->setXY(Console::Width() / 2, Console::Height() / 2);
	Pen->Symbol  = '@';
	Pen->BgColor = Console::clLightRed;
	Pen->Color   = Console::clBlack;
	
	// вывод географических объектов на консоль
	if (NULL != Objects) {
		Objects->ListDraw();
	}
	Pen->Draw();
	// основной цикл обработки нажатых клавиш
	int key = _getch();
	while (key != Console::keyEscape) {
		short LX = Pen->getX();
		short LY = Pen->getY();
		TGeoObject* WasOnObject = NULL;
		if (NULL != Objects) {
			WasOnObject = Objects->FindXY(LX, LY);
		}
		Pen->Hide();
		switch (key) {
		case Console::keyLeft  : { LX--; break; }
		case Console::keyRight : { LX++; break; }
		case Console::keyUp    : { LY--; break; }
		case Console::keyDown  : { LY++; break; }
		case Console::keyF4    : { Objects = AddHouse(Objects, Pen->getX(), Pen->getY()); Objects->Draw(); break; }
		case Console::keyF5    : { Objects = AddBank(Objects, Pen->getX(), Pen->getY()); Objects->Draw(); break; }
		case Console::keyF6    : { Objects = AddShop(Objects, Pen->getX(), Pen->getY()); Objects->Draw(); break; }
		case Console::keyDelete: { Objects = DeleteObject(Objects, Pen->getX(), Pen->getY()); break; }
		}
		if (!(LX >= 0)) { LX = 0; }
		if (!(LX < Console::Width())) { LX = Console::Width() - 1; }
		if (!(LY > 0)) { LY = 1; }
		if (!(LY < Console::Height())) { LY = Console::Height() - 1; }
		Pen->setXY(LX, LY);
		if (NULL != Objects) {
			if (NULL != WasOnObject) {
				WasOnObject->Draw();
			}
			//Objects->ListDraw();
		}
		Pen->Draw();

		key = _getch();
	}
	// очистка памяти
	if (NULL != Objects) {
		Objects->ListSave(AppMapFileName);
		Objects = Objects->ListLast();
		while (NULL != Objects) {
			TGeoObject* LItemToDelete = Objects;
			Objects = Objects->ListPred;
			delete LItemToDelete;
		}
	}
	delete Pen;
	free(AppMapFileName);
	// воcстанавливаем консоль
	Console::GotoXY(0, 28);
	Console::SetColor(Console::DefaultColor, Console::DefaultBgColor);
	return 0;
}