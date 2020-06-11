#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "StringHelper.h"

class Environment {
public:
	static enum SpecialFolder {
		 MyComputer
		,MyDocuments
		,MyMusic
		,MyPictures
		,MyVideos
		,ProgramFiles
	};
	static void GetCurrentDir(char* CurrentDir, const int Length = StringHelper::DefaultBufferSize);
	static void SetCurrentDir(const char* Path);
	static char* GetFolderPath(SpecialFolder Folder);
};


#endif