//
// Created by Crystal on 2024/3/17.
//

#include <stdlib.h>
#include <string.h>
#include "Structure/SimpleArray.h"

// Free the simple array, will free the memory of the array and the elements, used private
void SimpleArray_internalDestroyArray(SimpleArray_t array);

// Remove the element at the index, will move the elements after the index, used private
void SimpleArray_internalRemoveElement(SimpleArray_t array, int index);

SimpleArray_t SimpleArray_create(int typeSize){
    SimpleArray_t array = (SimpleArray_t)malloc(sizeof(SimpleArray));
    array->data = (char*)malloc(DEFAULT_CAPACITY * typeSize);
    array->num = 0;
    array->typeSize = typeSize;
    array->capacity = DEFAULT_CAPACITY;
    return array;
}

int SimpleArray_addElement(SimpleArray_t array, const void* element){
    if(array->num >= array->capacity / 2){
        SimpleArray_reserve(array, array->capacity * 2);
    }
    memcpy(array->data + array->num * array->typeSize, element, array->typeSize);
    array->num++;
    return array->num - 1;
}

void* SimpleArray_at(SimpleArray_t array, int index){
    if(index < 0 || index >= array->num){
        return NULL;
    }
    return array->data + index * array->typeSize;
}

void SimpleArray_internalDestroyArray(SimpleArray_t array){
    free(array->data);
    free(array);
}

void SimpleArray_reserve(SimpleArray_t array, int capacity){
    char* newData = (char*)malloc(capacity * array->typeSize);
    memcpy(newData, array->data, array->num * array->typeSize);
    free(array->data);
    array->data = newData;
    array->capacity = capacity;
}

void SimpleArray_insertElement(SimpleArray_t array, int index, void *element) {
    if(array->num >= array->capacity / 2){
        SimpleArray_reserve(array, array->capacity * 2);
    }
    memmove(array->data + (index + 1) * array->typeSize, array->data + index * array->typeSize, (array->num - index) * array->typeSize);
    memcpy(array->data + index * array->typeSize, element, array->typeSize);
    array->num++;
}

void SimpleArray_internalRemoveElement(SimpleArray_t array, int index) {
    memmove(array->data + index * array->typeSize, array->data + (index + 1) * array->typeSize, (array->num - index - 1) * array->typeSize);
    array->num--;
}

void SimpleArray_clear(SimpleArray_t array) {
    array->num = 0;
}

SimpleArray_t SimpleArray_newArrayWithCapacity(int typeSize, int capacity) {
    SimpleArray_t array = (SimpleArray_t)malloc(sizeof(SimpleArray));
    array->data = (char*)malloc(capacity * typeSize);
    array->num = 0;
    array->typeSize = typeSize;
    array->capacity = capacity;
    return array;
}

void SimpleArray_resize(SimpleArray_t array, int newSize) {
    if(newSize * 2 > array->capacity) {
        SimpleArray_reserve(array, newSize * 2);
    }
    array->num = newSize;
}

void SimpleArray_zeroFilled(SimpleArray_t array) {
    memset(array->data, 0, array->num * array->typeSize);
}

void SimpleArray_popBack(SimpleArray_t array, Destructor elementDestructor) {
    SimpleArray_removeElement(array, array->num - 1, elementDestructor);
}

int SimpleArray_pushBack(SimpleArray_t array, void *element) {
    return SimpleArray_addElement(array, element);
}

void * SimpleArray_back(SimpleArray_t array) {
    return SimpleArray_at(array, array->num - 1);
}

int SimpleArray_size(SimpleArray_t array) {
    return array->num;
}

void SimpleArray_destroy(SimpleArray_t array, Destructor elementDestructor) {
    if(array == NULL)
        return;
    if(elementDestructor != NULL)
    {
        for (int i = 0; i < array->num; i++) {
            elementDestructor(array->data + i * array->typeSize);
        }
    }
    SimpleArray_internalDestroyArray(array);
}

void SimpleArray_removeElement(SimpleArray_t array, int index, Destructor elementDestructor) {
    if(elementDestructor != NULL)
    {
        elementDestructor(array->data + index * array->typeSize);
    }
    SimpleArray_internalRemoveElement(array, index);
}

void SimpleArray_setElement(SimpleArray_t array, int index, const  void *element) {
    memcpy(array->data + index * array->typeSize, element, array->typeSize);
}
