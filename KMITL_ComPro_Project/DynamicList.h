#include "pch.h"

#ifndef _H_GUARD_DYNAMICLIST
#define _H_GUARD_DYNAMICLIST

#include "Util.h"

typedef struct DynamicListNode {
	void* data;
	struct DynamicListNode* prev;
	struct DynamicListNode* next;
} DynamicListNode;

typedef struct DynamicList {
	DynamicListNode* head;
	DynamicListNode* tail;
	size_t size;
} DynamicList;

void DynamicList_InitNode(DynamicListNode* node, void* data);

void DynamicList_Init(DynamicList* list);

void DynamicList_PushBack(DynamicList* list, DynamicListNode* node);
void DynamicList_PushFront(DynamicList* list, DynamicListNode* node);

DynamicListNode* DynamicList_PopBack(DynamicList* list);
DynamicListNode* DynamicList_PopFront(DynamicList* list);

size_t DynamicList_GetSize(DynamicList* list);
int DynamicList_Empty(DynamicList* list);

void DynamicList_FreeAll(DynamicList* list);

#endif