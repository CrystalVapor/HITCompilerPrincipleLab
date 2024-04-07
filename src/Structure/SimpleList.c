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
    return newList;
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

SimpleList_t SimpleList_append(SimpleList_t list1, SimpleList_t list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    if(list1->size == 0)
    {
        free(list1);
        return list2;
    }
    if(list2->size == 0)
    {
        free(list2);
        return list1;
    }
    list1->tail->next = list2->head;
    list2->head->prev = list1->tail;
    list1->tail = list2->tail;
    list1->size += list2->size;
    free(list2);
    return list1;
}

SimpleList_t SimpleList_destroy(SimpleList_t list, void (*destroyData)(void *)) {
    SimpleListNode_t node = list->head;
    while (node != NULL) {
        SimpleListNode_t next = node->next;
        if (destroyData != NULL) {
            destroyData(node->data);
        }
        free(node);
        node = next;
    }
    free(list);
    return NULL;
}
