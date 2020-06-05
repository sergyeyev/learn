#include <iostream>
// базовые библиотеки
#include "lib/ApplicationConsts.h"
#include "lib/ApplicationGlobals.h"
#include "lib/Application.h"
#include "lib/Console.h"
#include "lib/Directory.h"
#include "lib/Environment.h"
#include "lib/Path.h"
#include "lib/StringHelper.h"
// библиотеки модели данных приложения
#include "data/DataItem.h"
#include "data/DataGoods.h"
#include "data/DataWarrior.h"


void App_OnEscape(Application* Sender) {
	Sender->Running = false;
}

char* GAppDefaultDocPath     = NULL;
char* GAppDefaultFileWarrior = NULL;
char* GAppDefaultFileGoods   = NULL;

Warrior* GWarriors;
Good* GGoods;

int main() {
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
	// 1.5. запоминаем этот путь в глобальной переменной GAppDefaultDocPath
	GAppDefaultDocPath = StringHelper::New();
	strcpy_s(GAppDefaultDocPath, StringHelper::DefaultSize, LMyDocuments);
	Path::Combine(GAppDefaultDocPath, ApplicationFolder);
	// 1.6. буфер LMyDocuments больше не нужен
	free(LMyDocuments);
	// 2. Создаём буферы, хранящие имена файлов с данными
	// 2.1 для солдат
	GAppDefaultFileWarrior = StringHelper::New();
	strcpy_s(GAppDefaultFileWarrior, StringHelper::DefaultSize, GAppDefaultDocPath);
	Path::Combine(GAppDefaultFileWarrior, DefaultFileNameWarriors);
	// 2.2 для видов довольствия
	GAppDefaultFileGoods = StringHelper::New();
	strcpy_s(GAppDefaultFileGoods, StringHelper::DefaultSize, GAppDefaultDocPath);
	Path::Combine(GAppDefaultFileGoods, DefaultFileNameGoods);
	// 3. Создание глобальных объектов - списков данных
	GWarriors = (Warrior*)Warrior::ListLoadFromFile(GAppDefaultFileWarrior);
	GGoods    = (Good   *)Good::ListLoadFromFile(GAppDefaultFileGoods);
	// 3.1 только для откладки:
	//     если нет загруженных списков, генерируем тестовые данные
	if (NULL == GWarriors) {
		for (int i = 0; i < 20; i++) {
			Warrior *LItem = new Warrior();
			LItem->Id = (i + 1);
			LItem->GenTest();
			if (NULL == GWarriors) {
				GWarriors = LItem;
			} else {
				GWarriors = (Warrior*)GWarriors->ListAdd(LItem);
			}
		}
	}
	if (NULL == GGoods) {
		for (int i = 0; i < 200; i++) {
			Good* LItem = new Good();
			LItem->Id = (i + 1);
			LItem->GenTest();
			if (NULL == GGoods) {
				GGoods = LItem;
			} else {
				GGoods = (Good*)GGoods->ListAdd(LItem);
			}
		}
	}
	// 4. Основная работа приложения
	Application* App = new Application();
	App->OnEscape = &App_OnEscape;
	//1. Отладочная информация
	//printf("%s\n", GAppDefaultDocPath);
	//printf("%s\n", GAppDefaultFileWarrior);
	//printf("%s\n", GAppDefaultFileGoods);
	App->Run();
	delete App;



	// 98. Сохранить данные в файлы
	GWarriors->ListSaveToFile(GAppDefaultFileWarrior);
	GGoods->ListSaveToFile(GAppDefaultFileGoods);
	// 99. Освобождение памяти
	free(GAppDefaultFileGoods);
	free(GAppDefaultFileWarrior);
	free(GAppDefaultDocPath);
	return 0;
}