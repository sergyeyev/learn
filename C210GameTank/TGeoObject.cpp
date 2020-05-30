#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObject.h"

TGeoObject::TGeoObject() {
	Id           = 0;
	Name         = StringHelper::New();
	Address      = StringHelper::New();
	AddressHouse = 0;
	FX           = 0;
	FY           = 0;
	Symbol       = 'X';
	Color        = Console::DefaultColor;
	BgColor      = Console::DefaultBgColor;
	BeforeCoordChanged = NULL;
	AfterCoordChanged  = NULL;
	// поля и методы ДЛС
	ListNext = NULL;
	ListPred = NULL;
}

TGeoObject::~TGeoObject() {
	// обработка указателей ДЛС
	if (NULL != ListPred) {
		ListPred->ListNext = ListNext;
	}
	if (NULL != ListNext) {
		ListNext->ListPred = ListPred;
	}
	free(Address);
	free(Name);
}

short TGeoObject::getX() {
	return FX;
}

void TGeoObject::setX(const short aX) {
	setXY(aX, getY());
}

short TGeoObject::getY() {
	return FY;
}

void TGeoObject::setY(const short aY) {
	setXY(getX(), aY);
}

void TGeoObject::setXY(const short aX, const short aY) {
	if (NULL != BeforeCoordChanged) {
		BeforeCoordChanged( this );
	}
	FX = aX;
	FY = aY;
	if (NULL != AfterCoordChanged) {
		AfterCoordChanged( this );
	}
}

void TGeoObject::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "цех\0"
		,"пост\0"
		,"ларёк\0"
		,"сторожка\0"
		,"палатка\0"
	};
	const int LCAddressCount = 10;
	const char* LCAddress[LCAddressCount] = {
		 "Дворцовая\0"
		,"Парковая\0"
		,"Ленина\0"
		,"Горького\0"
		,"Орджоникидзе\0"
		,"Сергея Лазо\0"
		,"Социалистическая\0"
		,"Юбилейная\0"
		,"Краматорский\0"
		,"Нади Курченко\0"
	};
	FX = rand() % 80 + 1;
	FY = rand() % 25 + 1;
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	r = rand() % LCAddressCount;
	strcpy_s(Address, StringHelper::DefaultSize, LCAddress[r]);
	AddressHouse = rand() % 100;
}

void TGeoObject::Print() {
	Console::SetColor(Color);
	printf("%4d [%2d:%2d] %-20s %-20s -%3d \n", Id, FX, FY, Name, Address, AddressHouse);
}

void TGeoObject::Save(FILE* FileHandle) {
	fprintf(FileHandle, "TGEOOBJECT|%d|%d|%d|%s|%s|%d\n", Id, FX, FY, Name, Address, AddressHouse);
}

char* TGeoObject::LoadFromString(char* Text) {
	char* LParser = Text;
	char* LTempClassname = StringHelper::New();
	char* LTempId = StringHelper::New();
	char* LTempX = StringHelper::New();
	char* LTempY = StringHelper::New();
	char* LTempName = StringHelper::New();
	char* LTempAddress = StringHelper::New();
	char* LTempAddressHouse = StringHelper::New();

	LParser = StringHelper::Parse(LParser, '|', LTempClassname);
	LParser = StringHelper::Parse(LParser, '|', LTempId);
	LParser = StringHelper::Parse(LParser, '|', LTempX);
	LParser = StringHelper::Parse(LParser, '|', LTempY);
	LParser = StringHelper::Parse(LParser, '|', LTempName);
	LParser = StringHelper::Parse(LParser, '|', LTempAddress);
	LParser = StringHelper::Parse(LParser, '|', LTempAddressHouse);

	Id = atoi(LTempId);
	FX = atoi(LTempX);
	FY = atoi(LTempY);
	StringHelper::Null(Name); strcpy_s(Name, StringHelper::DefaultSize, LTempName);
	StringHelper::Null(Address); strcpy_s(Address, StringHelper::DefaultSize, LTempAddress);
	AddressHouse = atoi(LTempAddressHouse);

	free(LTempAddressHouse);
	free(LTempAddress);
	free(LTempName);
	free(LTempY);
	free(LTempX);
	free(LTempId);
	free(LTempClassname);
	return LParser;
}

void TGeoObject::Draw() {
	Console::SetColor(Color, BgColor);
	Console::GotoXY(FX, FY);
	printf("%c", Symbol);
}

void TGeoObject::Hide() {
	Console::SetColor(Console::DefaultColor, Console::DefaultBgColor);
	Console::GotoXY(FX, FY);
	printf(" ");
}

TGeoObject* TGeoObject::ListFirst() {
	TGeoObject* LResult = this;
	while (NULL != LResult->ListPred) {
		LResult = LResult->ListPred;
	}
	return LResult;
}

TGeoObject* TGeoObject::ListLast() {
	TGeoObject* LResult = this;
	while (NULL != LResult->ListNext) {
		LResult = LResult->ListNext;
	}
	return LResult;
}

int TGeoObject::ListCount() {
	int LResult = 0;
	TGeoObject* LItem = ListFirst();
	while (NULL != LItem->ListNext) {
		LResult++;
		LItem = LItem->ListNext;
	}
	return LResult;
}

TGeoObject* TGeoObject::ListAdd(TGeoObject* ExistingItem) {
	TGeoObject* LResult = ExistingItem;
	LResult->ListPred = this;
	LResult->ListNext = this->ListNext;
	if (NULL != this->ListNext) {
		this->ListNext->ListPred = LResult;
	}
	this->ListNext = LResult;
	return LResult;
}

void TGeoObject::ListDraw() {
	TGeoObject* LItem = ListFirst();
	while (NULL != LItem) {
		LItem->Draw();
		LItem = LItem->ListNext;
	}
}

void TGeoObject::ListSave(const char* FileName) {
	FILE* LFile;
	int LFileOpneError = fopen_s(&LFile, FileName, "w+");
	if (0 == LFileOpneError) {
		TGeoObject* LItem = ListFirst();
		while (NULL != LItem) {
			LItem->Save(LFile);
			LItem = LItem->ListNext;
		}
		fclose(LFile);
	} else {
		///.....
	}

}

bool TGeoObject::ListContains(const short aX, const short aY) {
	bool LResult = false;
	TGeoObject* LItem = ListFirst();
	while (NULL != LItem) {
		if ( (LItem->getX() == aX) && (LItem->getY() == aY) ) {
			LResult = true;
			break;
		}
		LItem = LItem->ListNext;
	}
	return LResult;
}

TGeoObject* TGeoObject::FindXY(const short aX, const short aY) {
	TGeoObject* LResult = NULL;
	TGeoObject* LItem = ListFirst();
	while (NULL != LItem) {
		if ( (LItem->getX() == aX) && (LItem->getY() == aY)) {
			LResult = LItem;
			break;
		}
		LItem = LItem->ListNext;
	}
	return LResult;
}