#include <iostream>
#include <Windows.h>
// служебные библиотеки
#include "lib/Console.h"
#include "lib/Directory.h"
#include "lib/Environment.h"
#include "lib/Path.h"
#include "lib/StringHelper.h"
#include "lib/Application.h"
// классы модели данных
#include "data/DataModelTMC.h"
// константы программы
#include "lib/ApplicationConsts.h"
#include "lib/ApplicationGlobals.h"


// инициализация глобальных переменных
char* ApplicationPathFolder  = NULL;
char* ApplicationPathFileTMC = NULL;

int main() {
	// 1. установка локализации для приложения
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// 2. получение специальных путей Windows
	// 2.1. получить путь к каталогу "Мои документы"
	ApplicationPathFolder  = Environment::GetFolderPath(Environment::MyDocuments);
	ApplicationPathFileTMC = StringHelper::New();
	// 2.3. устанавливаем текущим путь к папке "Мои Документы"
	Environment::SetCurrentDir(ApplicationPathFolder);
    // 2.4. проверяем существование каталога 
	if (!Directory::Exists(ApplicationFolder)) {
		Directory::Create(ApplicationFolder);
	}
	// 2.5. устанавливаем текущим путь "Мои Документы" \ "Каталог Нашего Приложения" 
	Path::Combine(ApplicationPathFolder, ApplicationFolder);
	Environment::SetCurrentDir(ApplicationPathFolder);
	// 2.6. полоучаем путь к файлу с товарам
	strcpy_s(ApplicationPathFileTMC, StringHelper::DefaultSize, ApplicationPathFolder);
	Path::Combine(ApplicationPathFileTMC, ApplicationFileTMC);


	TMC* Goods = NULL;
	for (int i = 0; i < 200; i++) {
		TMC* LItem = new TMC();
		LItem->Id = i + 1;
		LItem->GenTest();
		if (NULL == Goods) {
			Goods = LItem; // для самого первого элемента
		} else {
			Goods = Goods->ListAdd(LItem);
		}
	}

	Goods->ListPrint();
	Goods->ListSave(ApplicationPathFileTMC);



	free(ApplicationPathFileTMC);
	free(ApplicationPathFolder);
	return 0;
}