#include <iostream>
#include <Windows.h>
#include "lib/ApplicationConsts.h"
#include "lib/Environment.h"
#include "lib/Directory.h"
#include "lib/Path.h"
#include "lib/Console.h"
#include "lib/StringHelper.h"

int main() {
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	// 1. Подготовка путей в файловой системе для работы приложения
	// 1.1. получаем путь к папке "Мои Документы"
	char* LMyDocuments = Environment::GetFolderPath(Environment::MyDocuments);
	// 1.2 устанавливаем путь к папке "Мои Документы" - текущим для программы
	Environment::SetCurrentDir(LMyDocuments);
	// 1.3. проверяем, существует ли каталог "Мои Документы" \ ApplicationFolder
	if (!Directory::Exists(ApplicationFolder)) { // если каталог не существует
		Directory::Create(ApplicationFolder); // создаём его
	}
	// 1.4. устанавливаем текущим каталог  "Мои Документы" \ ApplicationFolder
	Environment::SetCurrentDir(ApplicationFolder);
	// 1.5. запоминаем этот путь в глобальной переменной  LDefaultFileSettingsPath

	char* LDefaultFileSettingsPath = StringHelper::New();
	strcpy_s(LDefaultFileSettingsPath, StringHelper::DefaultSize, LMyDocuments);
	Path::Combine(LDefaultFileSettingsPath, ApplicationFolder);
	Path::Combine(LDefaultFileSettingsPath, DefaultFileNameSettings);
	// 1.6. буфер LMyDocuments больше не нужен
	free(LMyDocuments);
	// отладка: выведем в консоль путь к файлу настроек
	//printf("%s\n", LDefaultFileSettingsPath);
	Console::ConsoleColors ColorBgr = Console::clBlack;
	Console::ConsoleColors ColorFrg = Console::clCyan;
	// загрузка настроек из файла
	if (Directory::Exists(LDefaultFileSettingsPath)) {
		FILE *FileSettings;
		int FileSettingsOpenError = fopen_s(&FileSettings, LDefaultFileSettingsPath, "r");
		if (0 == FileSettingsOpenError) {
			fscanf_s(FileSettings, "%d\n", &ColorBgr);
			fscanf_s(FileSettings, "%d\n", &ColorFrg);
			fclose(FileSettings);
		}
	}
	Console::SetColor(ColorFrg, ColorBgr);
	// что делает наша программа
	for (int i = 0; i < 40; i++) {
		printf("| %8d | %8d | %8d | %8d |\n", i, i*2, i*3, i*4);
	}
    // сохраняем настройки в файл
	FILE* LFileSettings;
	int LFileSettingsOpenError = fopen_s(&LFileSettings, LDefaultFileSettingsPath, "w+");
	if (0 == LFileSettingsOpenError) {
		fprintf(LFileSettings, "%d\n", (int)ColorBgr);
		fprintf(LFileSettings, "%d\n", (int)ColorFrg);
		fclose(LFileSettings);
	}


	free(LDefaultFileSettingsPath);
    return 0;
}