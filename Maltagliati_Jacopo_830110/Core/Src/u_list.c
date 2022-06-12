/*
 * u_list.c
 * Tipo custom: buffer/lista circolare
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 */

#include "u_list.h"

list_t* L_New(unsigned int maxsize) {
	list_t *ret = (list_t*) malloc(sizeof(list_t));
	assert(ret != NULL);
	ret->maxsize = maxsize;
	ret->first = NULL;
	ret->last = ret->first;
	ret->size = 0;
	ret->mean = 0;
	return ret;
}

void L_Insert(list_t *list, float content) {
	lnode_t *newnode = (lnode_t*) pvPortMalloc(sizeof(lnode_t));
	assert(newnode != NULL);
	newnode->content = content;
	newnode->next = NULL;
	if (list->size == list->maxsize) {
		lnode_t *dednode;
		dednode = list->first;
		list->first = dednode->next;
		assert(list->first != NULL);
		list->size--;
		vPortFree(dednode);
		dednode = NULL;
	}
	if (list->last != NULL) {
		assert(list->first != NULL);
		list->last->next = newnode;
		list->last = newnode;
	} else {
		list->first = newnode;
		list->last = newnode;
	}
	list->size++;
	return;
}

void L_UpdateMean(list_t *list) {
	list->mean = 0;
	if (list->first == NULL)
		return;
	lnode_t *curnode = list->first;
	unsigned int asize = 0;
	do {
		asize++;
		list->mean += curnode->content;
		curnode = curnode->next;
	} while (curnode != NULL);
	assert(asize == list->size);
	list->mean /= list->size;
	return;
}
