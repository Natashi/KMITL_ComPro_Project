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

	int ret = 0;
	FILE* file = NULL;

	size_t iLocation = 0;
	if ((file = fopen(pathLocationData, "r")) != NULL) {	//Open the file for reading
		char line[1024];
		char* tmp[3];

		while (fgets(line, sizeof(line), file) != NULL) {	//Get the next line of the file
			size_t cMatch = 0;

			char* strSplit = strtok(line, ",");
			while (strSplit && cMatch < 3) {
				tmp[cMatch++] = strSplit;
				strSplit = strtok(NULL, ",");
			}

			//The line must be split in exactly 3 strings
			if (cMatch == 3) {
				Location* location = PTR_NEW(Location);

				location->province = TrimString(tmp[0]);	//Province
				location->type = TrimString(tmp[1]);		//Type
				location->name = TrimString(tmp[2]);		//Name

				LocationMap_AddLocation(pMap, location);
			}
			else {
				ret = -1;
				goto lab_return;
			}
#undef CHK_END
#undef SKIP_SPACE
		}
	}
	else {
		ret = -1;
		goto lab_return;
	}

lab_return:
	if (file) fclose(file);
	return ret;
}

void LocationMap_AddLocation(LocationMap* pMap, Location* pLocation) {
	pMap->data[(pMap->count)++] = pLocation;
}
size_t LocationMap_GetSize(LocationMap* pMap) {
	return pMap->count;
}

//---------------------------------------------------------------------------------------

static const char* _FuncGetProvince(Location* pLoc) {
	return pLoc->province;
}
static const char* _FuncGetType(Location* pLoc) {
	return pLoc->type;
}
typedef const char* (*GET_FUNC)(Location*);

void _GetListSub(LocationMap* pMap, DynamicList* pList, GET_FUNC getFunc) {
	size_t count = 0;
	for (size_t iMap = 0; iMap < pMap->count; ++iMap) {
		int bDuplicate = 0;

		Location* pLoc1 = pMap->data[iMap];

		if (!DynamicList_Empty(pList)) {
			for (DynamicListNode* iNode = pList->head;; iNode = iNode->next) {
				Location* pLoc2 = (Location*)(iNode->data);

				bDuplicate = strcmp(getFunc(pLoc1), getFunc(pLoc2)) == 0;

				if (bDuplicate) break;
				if (iNode->next == NULL) break;
			}
		}
		if (bDuplicate) continue;

		DynamicListNode* node = PTR_NEW(DynamicListNode);
		DynamicList_InitNode(node, pLoc1);
		DynamicList_PushBack(pList, node);
		++count;
	}
}
void LocationMap_GetListProvince(LocationMap* pMap, DynamicList* pList) {
	_GetListSub(pMap, pList, _FuncGetProvince);
}
void LocationMap_GetListType(LocationMap* pMap, DynamicList* pList) {
	_GetListSub(pMap, pList, _FuncGetType);
}

//---------------------------------------------------------------------------------------

int GetMatchScore(const char* searchTerm, const char* str) {
	int score = 0;
	for (int i = 0;; ++i) {
		char c1 = searchTerm[i];
		char c2 = str[i];

		if (c1 == '\0' || c2 == '\0')
			break;

		if (c1 == c2)
			++score;
		else {
			score = 0;
			break;
		}
	}
	return score;
}
void _SearchSub(LocationMap* pMap, const char* search, DynamicList* pList, GET_FUNC getFunc) {
	for (size_t iMap = 0; iMap < pMap->count; ++iMap) {
		int bDup = 0;
		Location* pLoc = pMap->data[iMap];

		int score = GetMatchScore(search, getFunc(pLoc));
		if (*search == '\0' || score > 0) {
			DynamicListNode* node = PTR_NEW(DynamicListNode);
			DynamicList_InitNode(node, pLoc);
			DynamicList_PushBack(pList, node);
		}
	}
}
void LocationMap_SearchByProvince(LocationMap* pMap, const char* province, DynamicList* pList) {
	_SearchSub(pMap, province, pList, _FuncGetProvince);
}
void LocationMap_SearchByType(LocationMap* pMap, const char* type, DynamicList* pList) {
	_SearchSub(pMap, type, pList, _FuncGetType);
}

void Location_Free(Location* pLoc) {
	if (!pLoc) return;
	PTR_DELETE(pLoc->province);
	PTR_DELETE(pLoc->type);
	PTR_DELETE(pLoc->name);
}