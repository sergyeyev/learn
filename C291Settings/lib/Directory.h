#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <Windows.h>

typedef void (*FuncOnFileFound)(const char *FilePath, const char *FileName);

class Directory {
public: 
	static bool Exists(const char *Path);
	static bool Create(const char *Path);
	static bool Delete(const char* Path);
	static void PrintFileAttr(DWORD FileAttributes);
	static void FindFiles(const char *InitPath, const char *Mask, FuncOnFileFound Func);
	static void FindFilesRecursive(const char* InitPath, const char* Mask, FuncOnFileFound Func);
};

#endif