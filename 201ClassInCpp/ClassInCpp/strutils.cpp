#include "pch.h"
#include <iostream>
#include "consts.h"
#include "strutils.h"

void nullStr(char *str, int count) {
	char *wrk = str;
	for (int i = 0; i < count; i++) {
		*wrk = 0;
		wrk++;
	}
}

void strtoupper(char *str) {
	char *s = str;
	for (int i = 0; i < strlen(str); i++) {
		*s = toupper(*s);
		s++;
	}
}

char *parseItem(char *fromChar, const char delimiter, char *parsedItem) {
	nullStr(parsedItem, defaultNameLength);
	char *result = NULL;
	if (NULL != fromChar) {
		result = strchr(fromChar, delimiter); // именила strstr ,у меня она не хотела работать никак
		if (NULL != result) {
			for (int i = 0; i < (result - fromChar); i++) {
				*(parsedItem + i) = *(fromChar + i);
			}
			result++;
		}
	}
	return result;
}