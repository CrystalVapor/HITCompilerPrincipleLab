//
// Created by Crystal on 2024/3/17.
//

#include <stdlib.h>
#include <string.h>
#include "SimpleArray.h"

SimpleArray_t SimpleArray_newArray(int typeSize){
    SimpleArray_t array = (SimpleArray_t)malloc(sizeof(SimpleArray));
    array->data = (char*)malloc(DEFAULT_CAPACITY * typeSize);
    array->num = 0;
    array->typeSize = typeSize;
    array->capacity = DEFAULT_CAPACITY;
    return array;
}

int SimpleArray_addElement(SimpleArray_t array, void* element){
    if(array->num >= array->capacity / 2){
        SimpleArray_reserveSimpleArray(array, array->capacity * 2);
    }
    memcpy(array->data + array->num * array->typeSize, element, array->typeSize);
    array->num++;
    return array->num - 1;
}

void* SimpleArray_getElement(SimpleArray_t array, int index){
    if(index < 0 || index >= array->num){
        return NULL;
    }
    return array->data + index * array->typeSize;
}

void SimpleArray_freeSimpleArray(SimpleArray_t array){
    free(array->data);
    free(array);
}

void SimpleArray_reserveSimpleArray(SimpleArray_t array, int capacity){
    char* newData = (char*)malloc(capacity * array->typeSize);
    memcpy(newData, array->data, array->num * array->typeSize);
    free(array->data);
    array->data = newData;
    array->capacity = capacity;
}