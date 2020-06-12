#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include "Directory.h"
#include "Path.h"
#include "StringHelper.h"

bool Directory::Exists(const char* Path) {
	return (PathFileExistsA(Path) != 0);
}

bool Directory::Create(const char* Path) {
	return (CreateDirectoryA(Path, NULL) != 0);
}

bool Directory::Delete(const char* Path) {
	return (RemoveDirectoryA(Path) != 0);
}

void Directory::PrintFileAttr(DWORD FileAttributes) {
	if ((FileAttributes & FILE_ATTRIBUTE_READONLY  ) == FILE_ATTRIBUTE_READONLY) { printf("  - File is FILE_ATTRIBUTE_READONLY\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_HIDDEN    ) == FILE_ATTRIBUTE_HIDDEN) { printf("  - File is FILE_ATTRIBUTE_HIDDEN\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_SYSTEM    ) == FILE_ATTRIBUTE_SYSTEM) { printf("  - File is FILE_ATTRIBUTE_SYSTEM\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY) { printf("  - File is FILE_ATTRIBUTE_DIRECTORY\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_ARCHIVE   ) == FILE_ATTRIBUTE_ARCHIVE) { printf("  - File is FILE_ATTRIBUTE_ARCHIVE\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_DEVICE    ) == FILE_ATTRIBUTE_DEVICE) { printf("  - File is FILE_ATTRIBUTE_DEVICE\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_NORMAL    ) == FILE_ATTRIBUTE_NORMAL   ) { printf("  - File is FILE_ATTRIBUTE_NORMAL\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_TEMPORARY ) == FILE_ATTRIBUTE_TEMPORARY) { printf("  - File is FILE_ATTRIBUTE_TEMPORARY\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_COMPRESSED) == FILE_ATTRIBUTE_COMPRESSED) { printf("  - File is FILE_ATTRIBUTE_COMPRESSED\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_ENCRYPTED ) == FILE_ATTRIBUTE_ENCRYPTED ) { printf("  - File is FILE_ATTRIBUTE_ENCRYPTED\n"); }
	if ((FileAttributes & FILE_ATTRIBUTE_OFFLINE   ) == FILE_ATTRIBUTE_OFFLINE   ) { printf("  - File is FILE_ATTRIBUTE_OFFLINE\n"); }
}

void Directory::FindFiles(const char* InitPath, const char* Mask, FuncOnFileFound Func) {
	char* LSearchPath = StringHelper::New();
	strcpy_s(LSearchPath, StringHelper::DefaultSize, InitPath);
	Path::Combine(LSearchPath, Mask);
	WIN32_FIND_DATAA* LFounded = (WIN32_FIND_DATAA*)malloc(1 * sizeof(WIN32_FIND_DATAA));
	HANDLE LSearchHandle = FindFirstFileA(LSearchPath, LFounded);
	if (INVALID_HANDLE_VALUE != LSearchHandle) {
		do {
			/*
			if ((LFounded->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
				Console::SetColor(Console::clLightBlue);
			}else if ((LFounded->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) == FILE_ATTRIBUTE_SYSTEM) {
				Console::SetColor(Console::clLightRed);
			} else {
				Console::SetColor(Console::clWhite);
			}
			*/

			if (NULL != Func) {
				Func(InitPath, LFounded->cFileName);
			}
		} while (FindNextFileA(LSearchHandle, LFounded));
		FindClose(LSearchHandle);
	}
	free(LFounded);
	free(LSearchPath);
}

void Directory::FindFilesRecursive(const char* InitPath, const char* Mask, FuncOnFileFound Func) {
	// 1. Обрабатываем поиск в текущем каталоге
	FindFiles(InitPath, Mask, Func);
	// 2. Обработка вложенных каталогов
	char* LSearchPath = StringHelper::New();
	strcpy_s(LSearchPath, StringHelper::DefaultSize, InitPath);
	Path::Combine(LSearchPath, "*");
	WIN32_FIND_DATAA* LFounded = (WIN32_FIND_DATAA*)malloc(1 * sizeof(WIN32_FIND_DATAA));
	HANDLE LSearchHandle = FindFirstFileA(LSearchPath, LFounded);
	if (INVALID_HANDLE_VALUE != LSearchHandle) {
		do {
			if( ( (LFounded->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) 
				&& (strcmp(LFounded->cFileName, ".") != 0)   // 1. ссылка на самого себя
				&& (strcmp(LFounded->cFileName, "..") != 0)  // 2. ссылка на родительский каталог
				){
				char *LNewSearchPath = StringHelper::New();
				strcpy_s(LNewSearchPath, StringHelper::DefaultSize, InitPath);
				Path::Combine(LNewSearchPath, LFounded->cFileName);

				FindFilesRecursive(LNewSearchPath, Mask, Func);

				free(LNewSearchPath);
			}
		
		} while (FindNextFileA(LSearchHandle, LFounded));
		FindClose(LSearchHandle);
	}
	free(LFounded);
	free(LSearchPath);
}