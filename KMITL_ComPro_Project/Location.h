#pragma once
#include "pch.h"

typedef struct {
	const char* name;
} Province;

typedef struct {
	Province* province;
	const char* name;
	double coordX;
	double coordY;
} Location;