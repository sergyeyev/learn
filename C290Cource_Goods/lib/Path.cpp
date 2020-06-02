#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")
#include "Path.h"

void Path::Combine(char* Path, const char *AddPath) {
	PathAppendA(Path, AddPath);
}