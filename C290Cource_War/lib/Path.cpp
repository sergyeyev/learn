#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include "StringHelper.h"
#include "Path.h"

void Path::Combine(char* Path, const char* AddPath) {
	PathAppendA(Path, AddPath);
}