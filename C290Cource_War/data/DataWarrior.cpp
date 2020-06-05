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