#include "pch.h"

#ifndef _H_GUARD_LOCATION
#define _H_GUARD_LOCATION

#include "DynamicList.h"

typedef struct Location {
	const char* province;
	const char* type;
	const char* name;
} Location;

typedef struct LocationMap {
	Location* data[256];
	size_t count;
} LocationMap;

void LocationMap_Init(LocationMap* pMap);
void LocationMap_Free(LocationMap* pMap);

int LocationMap_LoadFromFile(LocationMap* pMap, const char* pathLocationData);

void LocationMap_AddLocation(LocationMap* pMap, Location* pLocation);
size_t LocationMap_GetSize(LocationMap* pMap);

void LocationMap_GetListProvince(LocationMap* pMap, DynamicList* pList);
void LocationMap_GetListType(LocationMap* pMap, DynamicList* pList);
void LocationMap_SearchByProvince(LocationMap* pMap, const char* province, DynamicList* pList);
void LocationMap_SearchByType(LocationMap* pMap, const char* type, DynamicList* pList);

void Location_Free(Location* pLoc);

#endif