#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObject.h"
#include "TGeoObjectHouse.h"

TGeoObjectHouse::TGeoObjectHouse() {
	Color    = Console::clYellow;
	BgColor  = Console::clBrown;
	Symbol   = 'H';
	CabCount = 0;
}

void TGeoObjectHouse::GenTest() {
	const int LCNameCount = 4;
	const char* LCNames[LCNameCount] = {
		 " 2-х  этажка\0"
		," 5-ти этажка\0"
		," 9-ти этажка\0"
		,"14-ти этажка\0"
	};

	TGeoObject::GenTest();
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCNames[r]);
	CabCount = rand() % 60;
}

void TGeoObjectHouse::Print() {
	Console::SetColor(Color);
	printf("%4d [%2d:%2d] %-20s %-20s -%3d cabcount = %d \n", Id, getX(), getY(), Name, Address, AddressHouse, CabCount);
}

void TGeoObjectHouse::Save(FILE* FileHandle) {
	fprintf(FileHandle, "TGEOOBJECTHOUSE|%d|%d|%d|%s|%s|%d|%d\n", Id, getX(), getY(), Name, Address, AddressHouse, CabCount);
}