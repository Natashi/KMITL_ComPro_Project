#include "pch.h"

#include "Location.h"

int main() {
	int res = 0;
	printf(
		"Welcome to the tourist destination finder!\n\n"

		"Command:\n"
		"    list\n"
		"        list all the available locations\n"
		"    listp\n"
		"        list all the available provinces\n"
		"    listt\n"
		"        list all the available location types\n"
		"    findp [name]\n"
		"        search location by province\n"
		"    findt [name]\n"
		"        search location by type\n"
		"    exit\n"
		"        exit program\n\n"
	);

	LocationMap* locationMap = PTR_NEW(LocationMap);
	LocationMap_Init(locationMap);

	if (!LocationMap_LoadFromFile(locationMap, "locations.txt")) {
		const char* S_INVALID = "\nInvalid command.\n\n";

		int bLoop = 1;
		char line[1024];

		DynamicList tmpList;
		DynamicList_Init(&tmpList);

		while (bLoop) {
			printf("Input command: ");
			if (fgets(line, sizeof(line), stdin) != NULL) {
				size_t lineLength = strlen(line);
				if (lineLength > 1) {
					line[lineLength - 1] = '\0';		//Turns '\n' into a null

					char* cmd = strtok(line, " ");
					char* arg = line + strlen(cmd) + 1;
					while (isspace(*arg) && *arg != '\0') ++arg;

					if (strcmp(cmd, "list") == 0) {
						printf("\n%u locations available\n", locationMap->count);

						printf("----%s %-20s  %-18s    %s\n", " # ", "Province", "Type", "Name");
						for (size_t i = 0; i < locationMap->count; ++i) {
							printf("   -%2u. %-20s; %-18s -> %s\n", i + 1, locationMap->data[i]->province,
								locationMap->data[i]->type, locationMap->data[i]->name);
						}

						printf("\n");
					}
					else if (strcmp(cmd, "listp") == 0) {
						LocationMap_GetListProvince(locationMap, &tmpList);

						size_t count = DynamicList_GetSize(&tmpList);
						printf("\n%u provinces available\n", count);

						if (count > 0) {
							printf("----%s %-20s\n", " # ", "Province");
							size_t i = 0;
							for (DynamicListNode* iNode = tmpList.head;; iNode = iNode->next, ++i) {
								Location* pLoc = (Location*)(iNode->data);
								printf("   -%2u. %-20s\n", i + 1, pLoc->province);
								if (iNode->next == NULL) break;
							}
						}

						DynamicList_FreeAll(&tmpList);
						printf("\n");
					}
					else if (strcmp(cmd, "listt") == 0) {
						LocationMap_GetListType(locationMap, &tmpList);

						size_t count = DynamicList_GetSize(&tmpList);
						printf("\n%u types available\n", count);

						if (count > 0) {
							printf("----%s %-20s\n", " # ", "Type");
							size_t i = 0;
							for (DynamicListNode* iNode = tmpList.head;; iNode = iNode->next, ++i) {
								Location* pLoc = (Location*)(iNode->data);
								printf("   -%2u. %-20s\n", i + 1, pLoc->type);
								if (iNode->next == NULL) break;
							}
						}

						DynamicList_FreeAll(&tmpList);
						printf("\n");
					}
					else if (strcmp(cmd, "findp") == 0) {
						if (*arg == '\0') goto lab_invalid;

						LocationMap_SearchByProvince(locationMap, arg, &tmpList);

						size_t count = DynamicList_GetSize(&tmpList);
						printf("\nSearch-by-province result: %u locations\n", count);

						if (count > 0) {
							printf("----%s %-20s  %-18s    %s\n", " # ", "Province", "Type", "Name");
							size_t i = 0;
							for (DynamicListNode* iNode = tmpList.head;; iNode = iNode->next, ++i) {
								Location* pLoc = (Location*)(iNode->data);
								printf("   -%2u. %-20s; %-18s -> %s\n", i + 1, pLoc->province,
									pLoc->type, pLoc->name);
								if (iNode->next == NULL) break;
							}
						}

						DynamicList_FreeAll(&tmpList);
						printf("\n");
					}
					else if (strcmp(cmd, "findt") == 0) {
						if (*arg == '\0') goto lab_invalid;

						LocationMap_SearchByType(locationMap, arg, &tmpList);

						size_t count = DynamicList_GetSize(&tmpList);
						printf("\nSearch-by-type result: %u locations\n", count);

						if (count > 0) {
							printf("----%s %-20s  %-18s    %s\n", " # ", "Province", "Type", "Name");
							size_t i = 0;
							for (DynamicListNode* iNode = tmpList.head;; iNode = iNode->next, ++i) {
								Location* pLoc = (Location*)(iNode->data);
								printf("   -%2u. %-20s; %-18s -> %s\n", i + 1, pLoc->province,
									pLoc->type, pLoc->name);
								if (iNode->next == NULL) break;
							}
						}

						DynamicList_FreeAll(&tmpList);
						printf("\n");
					}
					else if (strcmp(cmd, "exit") == 0) {
						bLoop = 0;
						printf("\nThank you for using this program!");

						//Wait 3 seconds
						{
							time_t time1 = time(NULL);
							while (time(NULL) - time1 < 3);
						}
					}
					else printf(S_INVALID);
				}
				else {
lab_invalid:
					printf(S_INVALID);
				}

				fflush(stdin);
			}
			else printf(S_INVALID);
		}
	}
	else {
		printf("CRITICAL ERROR: \"location.txt\" not found or inaccessible!");
		res = -1;

		//Wait 3 seconds
		{
			time_t time1 = time(NULL);
			while (time(NULL) - time1 < 3);
		}
	}

	LocationMap_Free(locationMap);
	PTR_DELETE(locationMap);

	return res;
}