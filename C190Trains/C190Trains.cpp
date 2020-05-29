#include <iostream>
#include <Windows.h>

const int StrDefaultSize = 255;

void StrNull(char* str, const int length = StrDefaultSize) {
	for (int i = 0; i < length; i++) {
		*(str + i) = 0;
	}
};

void StrInput(char* str, const int length = StrDefaultSize) {
	char* s = str;
	int i = 0;
	*s = getchar();
	while ((i < (length - 2)) && (*s != '\n')) {
		s++;
		i++;
		*s = getchar();
	}
	*s = 0;
};

char* StrNew(const int length = StrDefaultSize) {
	char* LStr = (char*)malloc(length * sizeof(char));
	StrNull(LStr, length);
	return LStr;
};

void StrToUpper(char* str, const int length = StrDefaultSize) {
	for (int i = 0; i < length; i++) {
		*(str + i) = toupper(*(str + i));
	}
};

const int CTownsCount = 21;

const char* CTowns[CTownsCount] = {
	 "Киев\0"
	,"Запорожье\0"
	,"Днепр\0"
	,"Донецк\0"
	,"Харьков\0"
	,"Полтава\0"
	,"Кривой Рог\0"
	,"Краматорск\0"
	,"Тор\0"
	,"Одесса\0"
	,"Херсон\0"
	,"Измаил\0"
	,"Рени\0"
	,"Николаев\0"
	,"Кировоград\0"
	,"Павлоград\0"
	,"Сумы\0"
	,"Чернигов\0"
	,"Житомир\0"
	,"Львов\0"
	,"Ужгород\0"
};

struct Train {
	int Id;          // номер поезда 91 из города1 в город2, то есть и 92 из города2 в город1
	char* TownFrom;  // из города
	char* TownTo;    // в город
};


int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	///
	int i;
	const int LCTraintCount = 6;
	struct Train* Trains = (Train*)malloc(LCTraintCount * sizeof(struct Train));
	// 1.ввод данных
	char* LBufferId    = StrNew();
	char* LBufferTown1 = StrNew();
	char* LBufferTown2 = StrNew();
	for (i = 0; i < LCTraintCount; i = i + 2) {
        // зануляем области памяти
		StrNull(LBufferId);
		StrNull(LBufferTown1);
		StrNull(LBufferTown2);
		// поезд "туда"
		printf("Ввод поезда %d :\n", i);
		printf("   -- введите номер поезда:");
		StrInput(LBufferId);
		printf("   -- введите город откуда:");
		StrInput(LBufferTown1);
		printf("   -- введите город куда:");
		StrInput(LBufferTown2);

		(Trains + i)->Id = atoi(LBufferId);  // присваивам текущему поезду номер
		(Trains + i)->TownFrom = StrNew();
		strcpy_s((Trains + i)->TownFrom, StrDefaultSize, LBufferTown1);
		(Trains + i)->TownTo   = StrNew();
		strcpy_s((Trains + i)->TownTo, StrDefaultSize, LBufferTown2);

		// поезд "обратно"
		(Trains + i + 1)->Id = atoi(LBufferId) + 1; // номер поезда "обратно" равен номеру поезда "туда" + 1
		(Trains + i + 1)->TownFrom = StrNew();
		strcpy_s((Trains + i + 1)->TownFrom, StrDefaultSize, LBufferTown2);
		(Trains + i + 1)->TownTo = StrNew();
		strcpy_s((Trains + i + 1)->TownTo, StrDefaultSize, LBufferTown1);
	}
	free(LBufferTown2);
	free(LBufferTown1);
	free(LBufferId);

	// 2. Контрольный вывод массива - расписание поездов
	printf("=====================================================\n");
	printf("|                 Расписание поездов                |\n");
	printf("-----------------------------------------------------\n");
	printf("|  №  |        Откуда        |         Куда         |\n");
	printf("=====================================================\n");
	for (i = 0; i < LCTraintCount; i++) {
		printf("| %3d | %-20s | %-20s |\n", (Trains+i)->Id, (Trains+i)->TownFrom, (Trains+i)->TownTo);
	}
	printf("=====================================================\n");
	// 3. Поиск поездов, проходящих через определённую станцию
	char* TownName = StrNew();
	printf("\n");
	printf("Введите подстроку и чать имени города:");
	StrInput(TownName);
	printf("=====================================================\n");
	printf("| Поезда идущие через город %s         |\n", TownName);
	printf("-----------------------------------------------------\n");
	printf("|  №  |        Откуда        |         Куда         |\n");
	printf("=====================================================\n");

	StrToUpper(TownName);
	char* BufferTownFrom = StrNew();
	char* BufferTownTo = StrNew();

	int TrainsCount = 0;
	for (i = 0; i < LCTraintCount; i++) {
		StrNull(BufferTownFrom); 
		strcpy_s(BufferTownFrom, StrDefaultSize, (Trains + i)->TownFrom);
		StrToUpper(BufferTownFrom);
		
		StrNull(BufferTownTo  ); 
		strcpy_s(BufferTownTo  , StrDefaultSize, (Trains + i)->TownTo);
		StrToUpper(BufferTownTo);

		if (strstr(BufferTownFrom, TownName) != NULL) {
			printf("| %3d | %-20s | %-20s |\n", (Trains + i)->Id, (Trains + i)->TownFrom, (Trains + i)->TownTo);
			TrainsCount++;
		}
		if (strstr(BufferTownTo, TownName) != NULL) {
			printf("| %3d | %-20s | %-20s |\n", (Trains + i)->Id, (Trains + i)->TownFrom, (Trains + i)->TownTo);
			TrainsCount++;
		}
	}
	if (0 == TrainsCount) {
		printf("|           поездов в этом городе нет               |\n");
	}
	printf("=====================================================\n");

	// Освобождение памяти
	free(BufferTownFrom);
	free(BufferTownTo);
	free(TownName);
	for (i = 0; i < LCTraintCount; i++) {
		free((Trains + i)->TownFrom);
		free((Trains + i)->TownTo);
	}
	free(Trains);
	return 0;

}