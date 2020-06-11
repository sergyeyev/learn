#include <iostream>
#include "../lib/StringHelper.h"
#include "DataItem.h"
#include "DataWarrior.h"

Warrior::Warrior() {
	Position = StringHelper::New();
	Foot = 40;
	Height = 3;
}

Warrior::~Warrior() {
	free(Position);
}

void Warrior::PrintHeader(const short X, const short Y, const Console::ConsoleColors Foreground, const Console::ConsoleColors Background) {
	Console::SetColor(Foreground, Background);
	Console::GotoXY(X, Y);
	printf("| Код |         Фамилия Имя Отчество             |      Должность       |нога|рост|\n");
}

void Warrior::PrintInternal() {
	printf("| %3d | %-40s | %-20s | %2d | %2d |\n", Id, Name, Position, Foot, Height);
}

void Warrior::GenTest() {
	const int LCNamesCount = 5;
	const char* LCNames[LCNamesCount] = {
		  "Иванов Иван Иванович\0"
		, "Петров Пётр петрович\0"
		, "Сидоров Сергей Сергеевич\0"
		, "Кравченко Юрий Дмитриевич\0"
		, "Панченко Степан Игнатьевич\0"
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
	r = rand() % LCPositionsCount;
	strcpy_s(Position, StringHelper::DefaultSize, LCPositions[r]);
	Foot   = 38 + (rand() % 8);
	Height = 1 + (rand() % 4);
}


void Warrior::ListSaveToFileItem(FILE* FileHandle) {
	fprintf(FileHandle, "%d|%s|%s|%d|%d\n", Id, Name, Position, Foot, Height);
}

char* Warrior::LoadFromString(char* Text) {
	char* LParser = Item::LoadFromString(Text);

	char* LTempPosition = StringHelper::New();
	char* LTempFoot     = StringHelper::New();
	char* LTempHeight   = StringHelper::New();
	LParser = StringHelper::Parse(LParser, '|', LTempPosition);
	LParser = StringHelper::Parse(LParser, '|', LTempFoot);
	LParser = StringHelper::Parse(LParser, '|', LTempHeight);

	strcpy_s(Position, StringHelper::DefaultSize, LTempPosition);
	Foot   = atoi(LTempFoot);
	Height = atoi(LTempHeight);

	free(LTempHeight);
	free(LTempFoot);
	free(LTempPosition);

	return LParser;
}


Warrior* Warrior::ListLoadFromFile(const char* FileName) {
	Warrior* LResult = NULL;
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "r+");
	if (0 == LFileOpenError) {
		char* LBuffer = StringHelper::New(StringHelper::DefaultBufferSize);
		char* LWork = LBuffer;
		while (!feof(LFileHandle)) {
			*LWork = fgetc(LFileHandle);
			if ('\n' == *LWork) {
				*LWork = '|';
				Warrior* LItem = new Warrior();
				LItem->LoadFromString(LBuffer);
				if (NULL == LResult) {
					LResult = LItem;
				} else {
					LResult = (Warrior*)LResult->ListAdd(LItem);
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
