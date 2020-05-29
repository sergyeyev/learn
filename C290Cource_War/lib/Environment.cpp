#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include "Environment.h"
#include "StringHelper.h"

void Environment::GetCurrentDir(char* CurrentDir, const int Length) {
	GetCurrentDirectoryA(Length, CurrentDir);
}

void Environment::SetCurrentDir(const char* Path) {
	SetCurrentDirectoryA(Path);
}

char* Environment::GetFolderPath(Environment::SpecialFolder Folder) {
	char* LResult = StringHelper::New();
	int CLSIDL = 0;
	switch (Folder) {
	    case MyComputer  : {CLSIDL = CSIDL_DRIVES; break; }
		case MyDocuments : {CLSIDL = CSIDL_MYDOCUMENTS; break; }
		case MyMusic     : {CLSIDL = CSIDL_MYMUSIC; break; }
		case MyPictures  : {CLSIDL = CSIDL_MYPICTURES; break; }
		case MyVideos    : {CLSIDL = CSIDL_MYVIDEO; break; }
		case ProgramFiles: {CLSIDL = CSIDL_PROGRAM_FILES; break; }
	}
	SHGetFolderPathA(0, CLSIDL, NULL, SHGFP_TYPE_CURRENT, LResult);
	return LResult;
}