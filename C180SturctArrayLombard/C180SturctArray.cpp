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

char* StrParse(char* FromChar, char Delimiter, char* BufferForValue, int LenBufferForValue = StrDefaultSize) {
	StrNull(BufferForValue, LenBufferForValue);
	char* LResult = NULL;
	if (NULL != FromChar) {
		LResult = strchr(FromChar, Delimiter);
		if (NULL != LResult) {
			for (int i = 0; i < (LResult - FromChar); i++) {
				*(BufferForValue + i) = *(FromChar + i);
			}
			LResult++;
		}
	}
	return LResult;
}

void StrToUpper(char* str, const int length = StrDefaultSize) {
	for (int i = 0; i < length; i++) {
		*(str + i) = toupper(*(str + i));
	}
};

struct Creditor {
	int Id;        // код
	char* Name;    // Фамилия Имя Отчество
	char* Filial;  // филиал
	char* Address; // Адрес
	char* TMC;     // Товарно-материальнеые ценности
};

int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i;
	// количество кредиторов
	int CreditorCountDefault = 1000;
	int CreditorCount = 0;
	// Массив структур
	struct Creditor* Creditors = NULL;
	// Имя файла
	char* FileName = StrNew();
	strcpy_s(FileName, StrDefaultSize, "d:\\dz-data-tree.txt");
	FILE* FileHandle;
	int FileOpenError = fopen_s(&FileHandle, FileName, "r");
	if (0 == FileOpenError) {
		char* LTempId      = StrNew();
		char* LTempName    = StrNew();
		char* LTempFilial  = StrNew();
		char* LTempAddress = StrNew();
		char* LTempTMC     = StrNew(1024);

		char* Buffer = StrNew(4096);
		char* Wrk = Buffer;

		while (!feof(FileHandle)) {
			*Wrk = fgetc(FileHandle);
			if ('\n' == *Wrk) {
				*Wrk = '|';
				char* Parser = Buffer;
				Parser = StrParse(Parser, '|', LTempId);
				Parser = StrParse(Parser, '|', LTempName);
				Parser = StrParse(Parser, '|', LTempFilial);
				Parser = StrParse(Parser, '|', LTempAddress);
				Parser = StrParse(Parser, '|', LTempTMC, 1024);
				// увеличиваем количество кредиторов
				CreditorCount++;
				if (NULL == Creditors) {
					Creditors = (struct Creditor*)malloc(CreditorCountDefault * sizeof(struct Creditor));
				} else {
					if (CreditorCount > CreditorCountDefault) {
						CreditorCountDefault += 1000;
						Creditors = (struct Creditor*)realloc(Creditors, CreditorCountDefault * sizeof(struct Creditor));
					}
				}
				// инициализщация полей структуры добавленного элемента массива
				(Creditors + CreditorCount - 1)->Id = atoi(LTempId);
				(Creditors + CreditorCount - 1)->Name = StrNew();
				strcpy_s((Creditors + CreditorCount - 1)->Name, StrDefaultSize, LTempName);
				(Creditors + CreditorCount - 1)->Filial = StrNew();
				strcpy_s((Creditors + CreditorCount - 1)->Filial, StrDefaultSize, LTempFilial);
				(Creditors + CreditorCount - 1)->Address = StrNew();
				strcpy_s((Creditors + CreditorCount - 1)->Address, StrDefaultSize, LTempAddress);
				(Creditors + CreditorCount - 1)->TMC = StrNew(1024);
				strcpy_s((Creditors + CreditorCount - 1)->TMC, 1024, LTempTMC);
				StrNull(Buffer, 4096);
				Wrk = Buffer;
			} else {
				Wrk++;
			}
		}
		free(LTempId);
		free(LTempName);
		free(LTempFilial);
		free(LTempAddress);
		free(LTempTMC);
		fclose(FileHandle);
	} else {
		printf("Не удалось открыть файл \"%s\" для чтения, код ошибки = %d !", FileName, FileOpenError);
	}

	// контрольный вывод массива структур
	//if (NULL != Creditors) {
	//	for (i = 0; i < CreditorCount; i++) {
	//		printf("%8d %-40s %-14s %-60s  %s\n", (Creditors + i)->Id, (Creditors + i)->Name, (Creditors + i)->Filial, 
	//			(Creditors + i)->Address, (Creditors + i)->TMC);
	//	}
	//}

	// поиск в базе
	if (NULL != Creditors) {
		int LSearchCount = 0;
		char* LSearchName = StrNew(1024);
		printf("Введите искомое имя:");
		StrInput(LSearchName);
		StrToUpper(LSearchName);
		char* LSearchTempName = StrNew(1024);
		for (i = 0; i < CreditorCount; i++) {
			StrNull(LSearchTempName, 1024);
			strcpy_s(LSearchTempName, 1024, (Creditors + i)->TMC);
			StrToUpper(LSearchTempName);
			if (strstr(LSearchTempName, LSearchName) != NULL) {
				LSearchCount++;
				printf("%8d   %-40s   %-14s   %-60s  %s\n", (Creditors + i)->Id, (Creditors + i)->Name, (Creditors + i)->Filial,
					(Creditors + i)->Address, (Creditors + i)->TMC);
			}
		}
		if (0 == LSearchCount) {
			printf("Ничего не найдено в базе с подстрокой \"%s\" \n", LSearchName);
		} else {
			printf("Найдено %d записей\n", LSearchCount);
		
		}
		// свобождаем временные букферы памяти под искомую строку
		free(LSearchTempName);
		free(LSearchName);
	}
    // высвобождение памяти
	if (NULL != Creditors) {
		for (int i = 0; i < CreditorCount; i++) {
			free((Creditors + i)->Name);
			free((Creditors + i)->Filial);
			free((Creditors + i)->Address);
			free((Creditors + i)->TMC);
		}
		free(Creditors);
	}
	return 0;
}
