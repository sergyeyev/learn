#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObject.h"
#include "TGeoObjectShop.h"

TGeoObjectShop::TGeoObjectShop(){
	Color   = Console::clWhite;
	BgColor = Console::clLightRed;
	Symbol  = 'S';
	Square = 0;
}

void TGeoObjectShop::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "АТБ\0"
		,"Сильпо\0"
		,"Таврия V\0"
		,"БУМ\0"
		,"Чудо-маркет\0"
	};

	TGeoObject::GenTest();

	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	Square = rand() % 100 + (rand() % 100 / 100.);
}

void TGeoObjectShop::Print() {
	Console::SetColor(Color);
	printf("%4d [%2d:%2d] %-20s %-20s -%3d square = %5.2f \n", Id, getX(), getY(), Name, Address, AddressHouse, Square);
}

void TGeoObjectShop::Save(FILE* FileHandle) {
	fprintf(FileHandle, "TGEOOBJECTSHOP|%d|%d|%d|%s|%s|%d|%f\n", Id, getX(), getY(), Name, Address, AddressHouse, Square);
}