#ifndef STRINGHELPER_H
#define STRINGHELPER_H

class StringHelper {
public:
	static const int DefaultBufferSize = 2048;
	static const int DefaultSize      = 255;
	static const int DefaultSizeSmall =  20;
	static char* New(const int length = DefaultSize);
	static void Null(char* str, const int length = DefaultSize);
	static void Input(char* str, const int length = DefaultSize);
	static char* Parse(char* FromChar, char Delimiter, char* BufferForValue, int LenBufferForValue = DefaultSize);
};

#endif