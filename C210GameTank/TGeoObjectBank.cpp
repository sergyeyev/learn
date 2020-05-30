#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObject.h"
#include "TGeoObjectBank.h"

TGeoObjectBank::TGeoObjectBank() {
	Color     = Console::clBlack;
	BgColor   = Console::clLightGreen;
	Symbol    = 'B';
	BankCount = 0;
	TermCount = 0;
}

void TGeoObjectBank::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "Приватбанк\0"
		,"УкрГазБанк\0"
		,"ПУМБ\0"
		,"Альфа-Банк\0"
		,"Нац.банк\0"
	};

	TGeoObject::GenTest();

	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	BankCount = rand() % 4;
	TermCount = rand() % 4;
}

void TGeoObjectBank::Print() {
	Console::SetColor(Color);
	printf("%4d [%2d:%2d] %-20s %-20s -%3d b=%3d  t=%3d \n", Id, getX(), getY(), Name, Address, AddressHouse, BankCount, TermCount);
}

void TGeoObjectBank::Save(FILE* FileHandle) {
	fprintf(FileHandle, "TGEOOBJECTBANK|%d|%d|%d|%s|%s|%d|%d|%d\n", Id, getX(), getY(), Name, Address, AddressHouse, BankCount, TermCount);
}

char* TGeoObjectBank::LoadFromString(char* Text) {
	char* LBankParser    = TGeoObject::LoadFromString(Text);

	char* LTempBankCount = StringHelper::New();
	char* LTempTermCount = StringHelper::New();
	LBankParser = StringHelper::Parse(LBankParser, '|', LTempBankCount);
	LBankParser = StringHelper::Parse(LBankParser, '|', LTempTermCount);
	BankCount = atoi(LTempBankCount);
	TermCount = atoi(LTempTermCount);
	free(LTempTermCount);
	free(LTempBankCount);
	return LBankParser;
}