#include <iostream>
#include "../lib/StringHelper.h"
#include "DataItem.h"

Item::Item() {
	Id   = 0;
	Name = StringHelper::New();
	// поля объекта, как элемента двусвязного линейного списка
	ListNext = NULL;
	ListPred = NULL;
}

Item::~Item() {
	// не порвать двусвязный список
	if (NULL != ListPred) { // если удляемый элемент не был первым в ДЛС
		ListPred->ListNext = ListNext;
	}
	if (NULL != ListNext) { // если удляемый элемент не был последним в ДЛС
		ListNext->ListPred = ListNext;
	}
	free(Name);
}

void Item::Print(const short X, const short Y, const Console::ConsoleColors Foreground, const Console::ConsoleColors Background) {
	Console::SetColor(Foreground, Background);
	Console::GotoXY(X, Y);
	PrintInternal();
}

void Item::PrintInternal() {
	printf("%3d|%-20s |\n", Id, Name);
}

void Item::GenTest() {

}

Item* Item::ListFirst() {
	Item* LResult = this;
	while (NULL != LResult->ListPred) {
		LResult = LResult->ListPred;
	}
	return LResult;
}

Item* Item::ListLast() {
	Item* LResult = this;
	while (NULL != LResult->ListNext) {
		LResult = LResult->ListNext;
	}
	return LResult;
}

int Item::ListCount() {
	int LResult = 0;
	Item* LItem = ListFirst();
	while (NULL != LItem->ListNext) {
		LResult++;
		LItem = LItem->ListNext;
	}
	return LResult;
}

Item* Item::ListAdd(Item* ExistingItem) {
	Item* LResult = ExistingItem;
	LResult->ListPred = this;
	LResult->ListNext = this->ListNext;
	if (NULL != this->ListNext) {
		this->ListNext->ListPred = LResult;
	}
	this->ListNext = LResult;
	return LResult;
}

void Item::ListSaveToFile(const char* FileName) {
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "w+");
	if (0 == LFileOpenError) {
		Item* LItem = ListFirst();
		while (NULL != LItem) {
			LItem->ListSaveToFileItem(LFileHandle);
			LItem = LItem->ListNext;
		}
		fclose(LFileHandle);
	} else {
//		Console::GotoXY(20, 20);
//		Console::SetColor(Console::clWhite, Console::clLightRed);
//		printf(" I cannot to save data into file %s !\n ", FileName);
	}
}

void Item::ListSaveToFileItem(FILE* FileHandle){
	fprintf(FileHandle, "%d|%s\n", Id, Name);
}

char* Item::LoadFromString(char* Text) {
	char* LParser = Text;

	char* LTempId = StringHelper::New();
	char* LTempName = StringHelper::New();
	LParser = StringHelper::Parse(LParser, '|', LTempId);
	LParser = StringHelper::Parse(LParser, '|', LTempName);

	Id = atoi(LTempId);
	StringHelper::Null(Name);
	strcpy_s(Name, StringHelper::DefaultSize, LTempName);

	free(LTempName);
	free(LTempId);

	return LParser;
}

Item * Item::ListLoadFromFile(const char* FileName) {
	Item* LResult = NULL;
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "r+");
	if (0 == LFileOpenError) {
		char* LBuffer = StringHelper::New(StringHelper::DefaultBufferSize);
		char* LWork = LBuffer;
		while (!feof(LFileHandle)) {
			*LWork = fgetc(LFileHandle);
			if ('\n' == *LWork) {
				*LWork = '|';
				Item* LItem = new Item();
				LItem->LoadFromString(LBuffer);
				if (NULL == LResult) {
					LResult = LItem;
				} else {
					LResult = LResult->ListAdd(LItem);
				}
				StringHelper::Null(LBuffer, StringHelper::DefaultBufferSize);
				LWork = LBuffer;
			} else {
				LWork++;
			}
		}
		free(LBuffer);
		fclose(LFileHandle);
	} else {
		//		Console::GotoXY(20, 20);
		//		Console::SetColor(Console::clWhite, Console::clLightRed);
		//		printf(" I cannot to load data from file %s !\n ", FileName);
	}
	return LResult;
}

int Item::ListGenId() {
	int LResult = 0;
	Item* LItem = ListFirst();
	while (NULL  != LItem) {
		if (LResult < LItem->Id) {
			LResult = LItem->Id;
		}
		LItem = LItem->ListNext;
	}
	LResult++;
	return LResult;
}