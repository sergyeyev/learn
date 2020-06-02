#ifndef STRINGHELPER_H
#define STRINGHELPER_H

class StringHelper {
public:
	static const int DefaultBufferSize = 2048;
	static const int DefaultSize       =  255;
	static const int DefaultSizeSmall  =   20;
	static const int DefaultSizeEd     =    5;
	static void Null(char *str, const int length = DefaultSize);
	static void Input(char* str, const int length = DefaultSize);
	static char* New(const int length = DefaultSize);
	static char* Parse(char *FromChar, const char Delimiter, char* BufferForValue, const int LengthBufferForValue = DefaultSize);
};

#endif
