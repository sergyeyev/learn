#include <iostream>
#include "StringHelper.h"

void StringHelper::Null(char* str, const int length) {
	for (int i = 0; i < length; i++) {
		*(str + i) = 0;
	}
}

void StringHelper::Input(char* str, const int length) {
	char* s = str;
	int i = 0;
	*s = getchar();
	while( (i < (length-2)) && (*s != '\n') ) {
		s++;
		i++;
		*s = getchar();
	}
	*s = 0;
}

char* StringHelper::New(const int length) {
	char* LStr = (char*)malloc(length * sizeof(char));
	Null(LStr, length);
	return LStr;
}

char* StringHelper::Parse(char* FromChar, const char Delimiter, char* BufferForValue, const int LengthBufferForValue) {
	Null(BufferForValue, LengthBufferForValue);
	char* LResult = NULL;
	if (NULL != FromChar) {
		LResult = strchr(FromChar, Delimiter);
		if (NULL != LResult) {
			for (int i = 0; i < (LResult - FromChar); i++) {
				*(BufferForValue + i) = *(FromChar + i);
			}
			LResult++;
		}
	}
	return LResult;
}