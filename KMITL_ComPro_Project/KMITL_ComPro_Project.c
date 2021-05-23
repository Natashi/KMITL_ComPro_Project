#include "pch.h"

#include "Location.h"

int main() {
	printf(
		"Welcome to the tourist destination finder.\n\n"
		"Bottom Text\n"
		"Die.\n"
	);

	LocationMap* locationMap = PTR_NEW(LocationMap);
	LocationMap_Init(locationMap);

	if (!LocationMap_LoadFromFile(locationMap, "locations.txt")) {

	}

	LocationMap_Free(locationMap);
	PTR_DELETE(locationMap);

	return 0;
}