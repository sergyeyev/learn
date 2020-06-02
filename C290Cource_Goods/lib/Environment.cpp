#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include "StringHelper.h"
#include "Environment.h"

void Environment::GetCurrentDir(char* Directory, const int Length) {
	StringHelper::Null(Directory, Length);
	GetCurrentDirectoryA(Length, Directory);
}

void Environment::SetCurrentDir(const char* Directory) {
	SetCurrentDirectoryA(Directory);
}

char* Environment::GetFolderPath(SpecialFolder Folder) {
	char* LResult = StringHelper::New();
	int LCSID = 0;
	switch (Folder) {
	    case MyComputer   : {LCSID = CSIDL_DRIVES; break; }
		case MyDocuments  : {LCSID = CSIDL_MYDOCUMENTS; break; }
		case MyMusic      : {LCSID = CSIDL_MYMUSIC; break; }
		case MyPictures   : {LCSID = CSIDL_MYPICTURES; break; }
		case ProgramFiles : {LCSID = CSIDL_PROGRAM_FILES; break; }
	}
	SHGetFolderPathA(0, LCSID, NULL, SHGFP_TYPE_CURRENT, LResult);
	return LResult;
}
