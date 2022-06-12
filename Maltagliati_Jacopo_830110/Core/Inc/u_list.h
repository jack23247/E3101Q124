/*
 * u_list.h
 * Tipo custom: buffer/lista circolare
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 */

#ifndef INC_U_LIST_H_
#define INC_U_LIST_H_

#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include "FreeRTOS.h"
#include "u_types.h"

typedef struct lnode_t lnode_t;
typedef struct list_t list_t;

// Nodo della lista
struct lnode_t {
	float content;
	lnode_t *next;
};

// Lista
typedef struct list_t {
	unsigned int maxsize;
	lnode_t *first;
	lnode_t *last;
	unsigned int size;
	float mean;
} list_t;

list_t* L_New(unsigned int maxsize);
void L_Insert(list_t *list, float content);
void L_UpdateMean(list_t *list);

#endif // INC_U_LIST_H_
