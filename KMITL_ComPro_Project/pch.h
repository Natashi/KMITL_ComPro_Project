#ifndef _H_GUARD_PCH
#define _H_GUARD_PCH

#define _CRT_SECURE_NO_WARNINGS

#pragma warning (disable : 6011)	//NULL dereference
#pragma warning (disable : 6387)	//'x' could be null, function specification blah blah blah

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define PTR_NEW(x) malloc(sizeof(x))
#define PTR_DELETE(x) if (x) free(x);

#endif