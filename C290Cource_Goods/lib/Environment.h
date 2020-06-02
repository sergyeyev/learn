#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "StringHelper.h"

class Environment {
public:
	static enum SpecialFolder {
		 MyComputer
	   , MyDocuments
       , MyMusic
	   , MyPictures
       , ProgramFiles
	};

	static void GetCurrentDir(char *Directory, const int Length = StringHelper::DefaultSize);
	static void SetCurrentDir(const char* Directory);
	static char* GetFolderPath(SpecialFolder Folder);
};


#endif