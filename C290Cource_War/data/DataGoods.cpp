#include <iostream>
#include "../lib/StringHelper.h"
#include "DataItem.h"
#include "DataGoods.h"

Good::Good() {
	Position = StringHelper::New();
	Foot     = -1;
	Height   = -1;
	Massa    = 0.;
	Quant    = 0.;
}

Good::~Good() {
	free(Position);
}

void  Good::PrintInternal() {
	printf("| %3d | %-20s| %-20s | %2d | %2d | %8.3f | %8.3f |\n", Id, Name, Position, Foot, Height, Massa, Quant);
}

void Good::GenTest() {
	const int LCNamesCount = 5;
	const char* LCNames[LCNamesCount] = {
		  "Форма\0"
		, "Сапоги\0"
		, "Берцы\0"
		, "Каска\0"
		, "Ампулы\0"
	};
	const int LCPositionsCount = 5;
	const char* LCPositions[LCPositionsCount] = {
		  "Пулемётчик\0"
		, "Автоматчик\0"
		, "Наводчик\0"
		, "Миномётчик\0"
		, "Медик\0"
	};

	int r;
	r = rand() % LCNamesCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCNames[r]);
	if (0 == r) {
		Height = 1 + (rand() % 4);
	}
	if( (1 == r) || (2 == r)  ){
		Foot = 38 + (rand() % 8);
	}
	r = rand() % LCPositionsCount;
	strcpy_s(Position, StringHelper::DefaultSize, LCPositions[r]);
	
	Massa = 0.001 + (rand() % 1000) / 1000.;
	Quant = 1 + rand() % 5;
}

void Good::ListSaveToFileItem(FILE* FileHandle) {
	fprintf(FileHandle, "%d|%s|%s|%d|%d|%f|%f\n", Id, Name, Position, Foot, Height, Massa, Quant);
}

char* Good::LoadFromString(char* Text) {
	char* LParser = Item::LoadFromString(Text);

	char* LTempPosition = StringHelper::New();
	char* LTempFoot     = StringHelper::New();
	char* LTempHeight   = StringHelper::New();
	char* LTempMassa    = StringHelper::New();
	char* LTempQuant    = StringHelper::New();

	LParser = StringHelper::Parse(LParser, '|', LTempPosition);
	LParser = StringHelper::Parse(LParser, '|', LTempFoot);
	LParser = StringHelper::Parse(LParser, '|', LTempHeight);
	LParser = StringHelper::Parse(LParser, '|', LTempMassa);
	LParser = StringHelper::Parse(LParser, '|', LTempQuant);

	strcpy_s(Position, StringHelper::DefaultSize, LTempPosition);
	Foot   = atoi(LTempFoot);
	Height = atoi(LTempHeight);
	Massa  = atof(LTempMassa);
	Quant  = atof(LTempQuant);

	free(LTempQuant);
	free(LTempMassa);
	free(LTempHeight);
	free(LTempFoot);
	free(LTempPosition);

	return LParser;
}


Good* Good::ListLoadFromFile(const char* FileName) {
	Good* LResult = NULL;
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "r+");
	if (0 == LFileOpenError) {
		char* LBuffer = StringHelper::New(StringHelper::DefaultBufferSize);
		char* LWork = LBuffer;
		while (!feof(LFileHandle)) {
			*LWork = fgetc(LFileHandle);
			if ('\n' == *LWork) {
				*LWork = '|';
				Good* LItem = new Good();
				LItem->LoadFromString(LBuffer);
				if (NULL == LResult) {
					LResult = LItem;
				} else {
					LResult = (Good*)LResult->ListAdd(LItem);
				}
				StringHelper::Null(LBuffer, StringHelper::DefaultBufferSize);
				LWork = LBuffer;
			}
			else {
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
