#ifndef DIRECTORY_H
#define DIRECTORY_H

class Directory {
public:
	static bool Exists(const char *Path);
	static bool Create(const char* Path);
	static bool Delete(const char* Path);

};

#endif