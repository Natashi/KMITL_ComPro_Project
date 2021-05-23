#include "pch.h"

#ifndef _H_GUARD_UTIL
#define _H_GUARD_UTIL

static char* TrimString(char* str) {
	size_t size = strlen(str) + 1;	//Include the null

	char* beg = str;
	char* end = str + size - 2;
	if (size > 0) {
		while (*beg != '\0' && isspace(*beg))
			++beg;
		while (*end != '\0' && isspace(*end))
			--end;
	}

	char* newStr = NULL;
	if (beg >= end) {
		newStr = malloc(1);
		newStr[0] = '\0';
	}
	else {
		size_t size2 = end - beg + 1;
		newStr = malloc(size2 + 1);
		memcpy(newStr, beg, size2);
		newStr[size2] = '\0';
	}
	return newStr;
}

#endif