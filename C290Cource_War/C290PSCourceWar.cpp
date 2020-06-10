#include <iostream>
#include <conio.h>
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


void AppGoods_OnCommand(ApplicationConsole* Sender, int Command) {
	switch (Command) {
	   case 0: {
		   Console::GotoXY(0, 0);
		   Console::SetColor(Console::clLightGreen);
		   Console::FillRect(' ', 0 ,0, Console::Height(), Console::Width());
		   if (NULL != GGoods) {
			   int lX = 0, lY = 0;
			   Good *LGood = (Good*)GGoods->ListFirst();
			   while(NULL != LGood) {
				   LGood->Print(lX, lY, Console::clLightGreen);
				   LGood = (Good*)LGood->ListNext;
				   lY++;
			   }
		   } else {
			   printf("\n\n\n   Список довольсствия пуст. Пожалуйсята, добавьте хоть один элемент в список\n\n\n");
		   }
		   int i = _getch();
		   break;
	   }
	   case 1: {
		   // очищаем экран
		   Console::GotoXY(0, 0);
		   Console::SetColor(Console::clLightGreen);
		   Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
		   // выводим приглашение пользователю
		   printf("Добавить элемент довольствия:\n\n");
		   // временные буферы под ввод пользователем данных
		   char* LStrName     = StringHelper::New();
		   char* LStrPosition = StringHelper::New();
		   char* LStrFoot     = StringHelper::New();
		   char* LStrHeight   = StringHelper::New();
		   char* LStrMassa    = StringHelper::New();
		   char* LStrQuant    = StringHelper::New();
		   // процедура ввода данных
		   printf("Введите имя:");
		   StringHelper::Input(LStrName);
		   printf("Введите должность, для которой предназначен элемент довольствия или нажмите Enter, если предназначен для всех:");
		   StringHelper::Input(LStrPosition);
		   printf("Введите размер ноги или (-1) если довольствие подходит для всех:");
		   StringHelper::Input(LStrFoot);
		   printf("Введите размер рост или (-1) если довольствие подходит для всех:");
		   StringHelper::Input(LStrHeight);
		   printf("Введите массу одной единицы довольствия:");
		   StringHelper::Input(LStrMassa);
		   printf("Введите количество единиц довольствия на складе:");
		   StringHelper::Input(LStrQuant);
		   // создаём новый элемент довольствия
		   Good* LItem = new Good();
		   if (NULL != GGoods) {// если в списке довольствия есть хоть один элемент
			   LItem->Id = GGoods->ListGenId();
		   } else {
			   LItem->Id = 1;
		   }
		   strcpy_s(LItem->Name    , StringHelper::DefaultSize, LStrName);
		   strcpy_s(LItem->Position, StringHelper::DefaultSize, LStrPosition);
		   LItem->Foot   = atoi(LStrFoot);
		   LItem->Height = atoi(LStrHeight);
		   LItem->Massa  = atof(LStrMassa);
		   LItem->Quant  = atof(LStrQuant);
		   // добавляем этот элемент в глобальный список довольствия
		   if (NULL != GGoods) { // если в списке довольствия есть хоть один элемент
			   GGoods->ListAdd(LItem); // тогда добавляем созданный пользователем элемент довольствия
		   } else {
			   GGoods = LItem; // иначе - список довольствия состоит из одного, вновь созданного элемента
		   }
		   // осовобождаем память под временные буферы для ввода пользоваталем данных
		   free(LStrQuant);
		   free(LStrMassa);
		   free(LStrHeight);
		   free(LStrFoot);
		   free(LStrPosition);
		   free(LStrName);
		   // команда "Добавить элемент довольствия" отработана
		   break;
	   }
	   case 2: {
		   Sender->Running = false;
		   break;
	   }
	}
}

void AppWarriors_OnCommand(ApplicationConsole* Sender, int Command) {
	switch (Command) {
	case 0: {
		Console::GotoXY(0, 0);
		Console::SetColor(Console::clLightGreen);
		Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
		if (NULL != GWarriors) {
			int lX = 0, lY = 0;
			Warrior* LWarrior = (Warrior*)GWarriors->ListFirst();
			while (NULL != LWarrior) {
				LWarrior->Print(lX, lY, Console::clLightRed);
				LWarrior = (Warrior*)LWarrior->ListNext;
				lY++;
			}
		}
		int i = _getch();
		break;
	}
	case 1: {
		break;
	}
	case 2: {
		Sender->Running = false;
		break;
	}
	}
}

void App_OnEscape(Application* Sender) {
	Sender->Running = false;
}

void App_OnCommand(ApplicationConsole* Sender, int Command) {
	switch (Command) {
	    case 0: {
			ApplicationConsole* LAppGoods = new ApplicationConsole();
			LAppGoods->MenuMain->AddItem("1. Отобразить список довольствия ");
			LAppGoods->MenuMain->AddItem("2. Добавить элемент довольствия ");
			LAppGoods->MenuMain->AddItem("3. [Esc] Выход в главное меню ");
			LAppGoods->MenuMain->Selected = 0;
			LAppGoods->OnCommand = &AppGoods_OnCommand;
			LAppGoods->OnEscape = &App_OnEscape;
			LAppGoods->Run();
			delete LAppGoods;
			break; 
		}
		case 1: {
			ApplicationConsole* LAppWarriors = new ApplicationConsole();
			LAppWarriors->MenuMain->AddItem("1. Отобразить список сотрудников ");
			LAppWarriors->MenuMain->AddItem("2. Добавить нового сотрудника ");
			LAppWarriors->MenuMain->AddItem("3. [Esc] Выход в главное меню ");
			LAppWarriors->MenuMain->Selected = 0;
			LAppWarriors->OnCommand = &AppWarriors_OnCommand;
			LAppWarriors->OnEscape = &App_OnEscape;
			LAppWarriors->Run();
			delete LAppWarriors;
			break;
	    }
		case 2: { 
			Sender->Running = false;
			break; 
		}
	}
}

char* GAppDefaultDocPath     = NULL;
char* GAppDefaultFileWarrior = NULL;
char* GAppDefaultFileGoods   = NULL;

Warrior* GWarriors = NULL;
Good* GGoods = NULL;

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
	/* тестовое покрытие закомментировано, т.к. есть функция ввода элемента довольствия
	if (NULL == GGoods) {
		for (int i = 0; i < 20; i++) {
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
	*/
	Console::SetScreen(120, 80);
	// 4. Основная работа приложения
	ApplicationConsole* App = new ApplicationConsole();
	App->MenuMain->AddItem("1. Довольствие ");
	App->MenuMain->AddItem("2. Сотрудники ");
	App->MenuMain->AddItem("3. [Esc] Выход из программы ");
	App->MenuMain->Selected = 0;
	App->OnCommand = &App_OnCommand;
	App->OnEscape  = &App_OnEscape;
	//1. Отладочная информация
	//printf("%s\n", GAppDefaultDocPath);
	//printf("%s\n", GAppDefaultFileWarrior);
	//printf("%s\n", GAppDefaultFileGoods);
	App->Run();
	delete App;
	// очистим консоль перед выходом из программы
	Console::SetColor(Console::clWhite, Console::clBlack);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());



	// 98. Сохранить данные в файлы
	if (NULL != GWarriors) { GWarriors->ListSaveToFile(GAppDefaultFileWarrior);}
	if (NULL != GGoods   ) { GGoods->ListSaveToFile(GAppDefaultFileGoods);     }
	// 99. Освобождение памяти
	free(GAppDefaultFileGoods);
	free(GAppDefaultFileWarrior);
	free(GAppDefaultDocPath);
	return 0;
}