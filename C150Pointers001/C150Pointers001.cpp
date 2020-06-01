#include <iostream>
#include <Windows.h>
#include "Console.h"
#include "StringHelper.h"



int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Console::SetColor(Console::clYellow);
	
	Console::SetColor(Console::clGreen);
	int i;
	char* MyString = StringHelper::New();
	for (i = 0; i < StringHelper::DefaultSize-1; i++) {
		*(MyString + i) = 32 + rand() % 40;
		printf("  [%d] MyString[%2d] = %c\n", (MyString + i), i, *(MyString + i));
	}
	printf("%s\n", MyString);
	free(MyString);


	Console::SetColor(Console::clWhite);
	return 0;
}