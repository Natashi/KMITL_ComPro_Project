#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#define PTR_DELETE(x) if (x) free(x);