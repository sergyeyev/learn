#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")
#include "StringHelper.h"
#include "Directory.h"

bool Directory::Exists(const char* Path) {
	return (PathFileExistsA(Path) != 0);
}


bool  Directory::Create(const char* Path) {
	return (CreateDirectoryA(Path, NULL) != 0);
}

bool  Directory::Delete(const char* Path) {
	return (RemoveDirectoryA(Path) != 0);
}
