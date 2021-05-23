#include "pch.h"

#include "Location.h"

void LocationMap_Init(LocationMap* pMap) {
	for (int i = 0; i < sizeof(pMap->data) / sizeof(Location*); ++i)
		(pMap->data)[i] = NULL;
	pMap->count = 0;
}
void LocationMap_Free(LocationMap* pMap) {
	Location** locArray = pMap->data;
	for (size_t i = 0; i < sizeof(pMap->data) / sizeof(Location*); ++i) {
		if (locArray[i] == NULL) break;
		Location_Free(locArray[i]);
		locArray[i] = NULL;
	}
}

int LocationMap_LoadFromFile(LocationMap* pMap, const char* pathLocationData) {
	Location** locArray = pMap->data;

	FILE* file = NULL;

	size_t iLocation = 0;
	if ((file = fopen(pathLocationData, "r")) != NULL) {	//Open the file for reading
		char line[1024];
		char tmp[2048];

		while (fgets(line, sizeof(line), file) != NULL) {	//Get the next line of the file
			int bEnd = 0;
			size_t bMatch = 0;
			char* pLine = line;

#define CHK_END if (*pLine == '\0' || *pLine == '\n') { bEnd = 1; }
#define SKIP_SPACE while (isspace(*pLine)) { ++pLine; } CHK_END;

			//Split the line text with the delimiter being commas (max=3)
			for (int i = 0; i < 3 && !bEnd; ++i) {
				char* pBuf = tmp + i * 512;
				int j = 0;

				SKIP_SPACE;		//Skip whitespaces
				for (; *pLine != ',' && !bEnd; ++j) {
					*(pBuf + j) = *(pLine++);
					if (*pLine == '\0' || *pLine == '\n')
						bEnd = 1;
				}
				SKIP_SPACE;		//Skip whitespaces

				*(pBuf + j) = '\0';
				if (j > 0) ++bMatch;

				++pLine;
			}

			//The line must be split in exactly 3 strings
			if (bMatch == 3) {
				Location* location = PTR_NEW(Location);

				location->province = _strdup(tmp + 0 * 512);	//Province
				location->type = _strdup(tmp + 1 * 512);		//Type
				location->name = _strdup(tmp + 2 * 512);		//Name

				LocationMap_AddLocation(pMap, location);
			}
			else goto lab_return_error;
#undef CHK_END
#undef SKIP_SPACE
		}
	}
	else goto lab_return_error;

	if (file) fclose(file);
	return 0;

lab_return_error:
	if (file) fclose(file);
	return -1;
}

void LocationMap_AddLocation(LocationMap* pMap, Location* pLocation) {
	pMap->data[(pMap->count)++] = pLocation;
}
size_t LocationMap_GetSize(LocationMap* pMap) {
	return pMap->count;
}

void LocationMap_GetListProvince(LocationMap* pMap, const char* province, DynamicList* pRes) {

}
void LocationMap_GetListType(LocationMap* pMap, const char* type, DynamicList* pRes) {

}
void LocationMap_SearchByProvince(LocationMap* pMap, const char* province, DynamicList* pRes) {

}
void LocationMap_SearchByType(LocationMap* pMap, const char* type, DynamicList* pRes) {

}

void Location_Free(Location* pLoc) {
	if (!pLoc) return;
	PTR_DELETE(pLoc->province);
	PTR_DELETE(pLoc->type);
	PTR_DELETE(pLoc->name);
}