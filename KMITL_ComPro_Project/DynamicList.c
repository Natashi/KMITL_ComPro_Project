#include "pch.h"

#include "DynamicList.h"

void DynamicList_InitNode(DynamicListNode* node, void* data) {
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
}

void DynamicList_Init(DynamicList* list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void DynamicList_PushBack(DynamicList* list, DynamicListNode* node) {
	if (list->tail) {		//Insert new element at tail
		node->prev = list->tail;
		list->tail->next = node;
	}
	list->tail = node;
	if (list->head == NULL)
		list->head = node;

	++(list->size);
}
void DynamicList_PushFront(DynamicList* list, DynamicListNode* node) {
	if (list->head) {		//Insert new element at head
		node->next = list->head;
		list->head->prev = node;
	}
	list->head = node;
	if (list->tail == NULL)
		list->tail = node;

	++(list->size);
}

DynamicListNode* DynamicList_PopBack(DynamicList* list) {
	if (list->size == 0) return NULL;
	DynamicListNode* res = list->tail;
	res->prev->next = NULL;
	return res;
}
DynamicListNode* DynamicList_PopFront(DynamicList* list) {
	if (list->size == 0) return NULL;
	DynamicListNode* res = list->head;
	res->next->prev = NULL;
	return res;
}

size_t DynamicList_GetSize(DynamicList* list) {
	return list ? list->size : 0;
}
int DynamicList_Empty(DynamicList* list) {
	return DynamicList_GetSize(list) == 0;
}

void DynamicList_FreeAll(DynamicList* list) {
	for (DynamicListNode* itr = list->head;;) {
		DynamicListNode* next = itr->next;
		free(itr);

		if (next == list->tail) break;
		itr = next;
	}
	DynamicList_Init(list);
}