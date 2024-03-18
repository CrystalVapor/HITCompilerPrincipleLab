//
// Created by Crystal on 2024/3/17.
//

#ifndef LAB1_SIMPLEARRAY_H
#define LAB1_SIMPLEARRAY_H

#define DEFAULT_CAPACITY 100

struct SimpleArray_s{
    char* data;
    int num;
    int typeSize;
    int capacity;
};
typedef struct SimpleArray_s* SimpleArray_t;
typedef struct SimpleArray_s SimpleArray;

// Create a new simple array, the typeSize is the size of the type of the element
SimpleArray_t SimpleArray_newArray(int typeSize);
// Add an element to the simple array's tail, will copy the content of the element to the array
// remember to free the memory of the element if it's a pointer
int SimpleArray_addElement(SimpleArray_t array, void* element);
// Get the element at the index, will check if the index is valid
void* SimpleArray_getElement(SimpleArray_t array, int index);
// Free the simple array, will free the memory of the array and the elements
void SimpleArray_freeSimpleArray(SimpleArray_t array);
// Reserve the simple array, will change the capacity of the array
void SimpleArray_reserveSimpleArray(SimpleArray_t array, int capacity);

#endif //LAB1_SIMPLEARRAY_H
