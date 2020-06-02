#include <iostream>
#include "../lib/StringHelper.h"
#include "DataModelTMC.h"

TMC::TMC() {
	// 1. инициализация полей класса
	Id      = 0;
	Name    = StringHelper::New();
	Article = StringHelper::New();
	Measure = StringHelper::New(StringHelper::DefaultSizeEd);
	Price   = 0.;
	Quant   = 0.;
	Limit   = 0.;
	// 2. поля и методы для работы с двусвязным линейным списком (ДЛС)
	ListNext = NULL;
	ListPred = NULL;
}

TMC::~TMC() {
	// -2. обработка указателей ДЛС
	if (NULL != ListPred) {
		ListPred->ListNext = ListNext;
	}
	if (NULL != ListNext) {
		ListNext->ListPred = ListPred;
	}
	// -1. высвобождение памяти
	free(Name);
	free(Article);
	free(Measure);
}


TMC* TMC::ListFirst() {
	TMC* LResult = this;
	while (NULL != LResult->ListPred) {
		LResult = LResult->ListPred;
	}
	return LResult;
}

TMC* TMC::ListLast() {
	TMC* LResult = this;
	while (NULL != LResult->ListNext) {
		LResult = LResult->ListNext;
	}
	return LResult;
}

int TMC::ListCount() {
	int LResult = 0;
	TMC* LItem = ListFirst();
	while (NULL != LItem->ListNext) {
		LResult++;
		LItem = LItem->ListNext;
	}
	return LResult;
}

TMC* TMC::ListAdd(TMC* ExistingItem) {
	TMC* LResult = ExistingItem;
	LResult->ListPred = this;
	LResult->ListNext = this->ListNext;
	if (NULL != this->ListNext) {
		this->ListNext->ListPred = LResult;
	}
	this->ListNext = LResult;
	return LResult;
}

void TMC::ListPrint() {
	TMC* LItem = ListFirst();
	while (NULL != LItem) {
		LItem->Print();
		LItem = LItem->ListNext;
	}
}

void TMC::ListSave(const char* FileName) {
	FILE* LFile;
	int LFileOpneError = fopen_s(&LFile, FileName, "w+");
	if (0 == LFileOpneError) {
		TMC* LItem = ListFirst();
		while (NULL != LItem) {
			LItem->Save(LFile);
			LItem = LItem->ListNext;
		}
		fclose(LFile);
	} else {
		///.....
	}

}

void TMC::Print() {
	printf("%5d|%-40s|%-14s|%5s|%8.2f|%8.2f|%8.2f\n", Id, Name, Article, Measure, Price, Quant, Limit);
}

void TMC::Save(FILE* FileHandle) {
	fprintf(FileHandle, "%d|%s|%s|%s|%f|%f|%f\n", Id, Name, Article, Measure, Price, Quant, Limit);
}

char* TMC::LoadFromString(char* Text) {
	// временные буферы для парсингра полей объекта из строки
	char* LTempId = StringHelper::New();
	char* LTempName = StringHelper::New();
	char* LTempArticle = StringHelper::New();
	char* LTempMeasure = StringHelper::New();
	char* LTempPrice = StringHelper::New();
	char* LTempQuant = StringHelper::New();
	char* LTempLimit = StringHelper::New();
	// парсим поля объекта из стироки
	char* LParser = Text;
	LParser = StringHelper::Parse(LParser, '|', LTempId);
	LParser = StringHelper::Parse(LParser, '|', LTempName);
	LParser = StringHelper::Parse(LParser, '|', LTempArticle);
	LParser = StringHelper::Parse(LParser, '|', LTempMeasure);
	LParser = StringHelper::Parse(LParser, '|', LTempPrice);
	LParser = StringHelper::Parse(LParser, '|', LTempQuant);
	LParser = StringHelper::Parse(LParser, '|', LTempLimit);
	// присваиваем полям объекта распарсенные значения
	Id = atoi(LTempId);
	StringHelper::Null(Name   ); strcpy_s(Name   , StringHelper::DefaultSize  , LTempName   );
	StringHelper::Null(Article); strcpy_s(Article, StringHelper::DefaultSize  , LTempArticle);
	StringHelper::Null(Measure); strcpy_s(Measure, StringHelper::DefaultSizeEd, LTempMeasure);
	Price = atof(LTempPrice);
	Quant = atof(LTempQuant);
	Limit = atof(LTempLimit);
    // осовобождение памяти, израсходованной под парсинг строки
	free(LTempLimit);
	free(LTempQuant);
	free(LTempPrice);
	free(LTempMeasure);
	free(LTempArticle);
	free(LTempName);
	free(LTempId);
	return LParser;
}

void TMC::GenTest() {
	const int LCNameCount = 10;
	const char* LCName[LCNameCount] = {
		 "Хлеб\0"
		,"Сигареты\0"
		,"Водка\0"
		,"Макароны\0"
		,"Халва\0"
		,"Пиво\0"
		,"Чипсы\0"
		,"Орешки\0"
		,"Картофель\0"
		,"Помидоры\0"
	};
	const int LCArticleCount = 12;
	const int LCMeasureCount = 5;
	const char* LCMeasure[LCMeasureCount] = {
		 "м\0"
		,"кг\0"
		,"шт\0"
		,"0,5\0"
		,"порц\0"
	};
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	for (int i = 0; i < LCArticleCount; i++) { // случайные цифры
		*(Article + i) = 48 + (rand() % 10); 
	}
	r = rand() % LCMeasureCount;
	strcpy_s(Measure, StringHelper::DefaultSizeEd, LCMeasure[r]);
	Price = (rand() % 100) + (rand() % 100) / 100.;
	Quant = (rand() % 50);
	Limit = (rand() % 10);
}
