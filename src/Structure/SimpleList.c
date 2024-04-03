//
// Created by Crystal on 2024/4/3.
//

#include <stdlib.h>

#include "Structure/SimpleList.h"

SimpleList_t SimpleList_create() {
    SimpleList_t newList = malloc(sizeof(SimpleList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return NULL;
}

SimpleListNode_t SimpleList_push_back(SimpleList_t list, void *data) {
    SimpleListNode_t newNode = malloc(sizeof(SimpleListNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    if (list->head == NULL) {
        list->head = newNode;
    }
    list->size++;
    return newNode;
}

SimpleListNode_t SimpleList_push_front(SimpleList_t list, void *data) {
    SimpleListNode_t newNode = malloc(sizeof(SimpleListNode));
    newNode->data = data;
    newNode->next = list->head;
    newNode->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = newNode;
    }
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
    list->size++;
    return newNode;
}

void *SimpleList_pop_back(SimpleList_t list) {
    SimpleListNode_t lastNode = list->tail;
    if (lastNode == NULL) {
        return NULL;
    }
    void *data = lastNode->data;
    list->tail = lastNode->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(lastNode);
    list->size--;
    return data;
}

void *SimpleList_pop_front(SimpleList_t list) {
    SimpleListNode_t firstNode = list->head;
    if (firstNode == NULL) {
        return NULL;
    }
    void *data = firstNode->data;
    list->head = firstNode->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    free(firstNode);
    list->size--;
    return data;
}

void SimpleList_insertBefore(SimpleList_t list, SimpleListNode_t pos, void *data) {
    if (pos == NULL) {
        SimpleList_push_back(list, data);
        return;
    }
    SimpleListNode_t newNode = malloc(sizeof(SimpleListNode));
    newNode->data = data;
    newNode->next = pos;
    newNode->prev = pos->prev;
    if (pos->prev != NULL) {
        pos->prev->next = newNode;
    } else {
        list->head = newNode;
    }
    pos->prev = newNode;
    list->size++;
}

void SimpleList_insertAfter(SimpleList_t list, SimpleListNode_t pos, void *data) {
    if (pos == NULL) {
        SimpleList_push_front(list, data);
        return;
    }
    SimpleListNode_t newNode = malloc(sizeof(SimpleListNode));
    newNode->data = data;
    newNode->next = pos->next;
    newNode->prev = pos;
    if (pos->next != NULL) {
        pos->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    pos->next = newNode;
    list->size++;
}
