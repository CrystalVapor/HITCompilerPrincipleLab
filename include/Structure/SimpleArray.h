//
// Created by Crystal on 2024/3/17.
//

#ifndef LAB1_SIMPLEARRAY_H
#define LAB1_SIMPLEARRAY_H

#define DEFAULT_CAPACITY 100

typedef void (*Destructor)(void*);

struct SimpleArray_s{
    char* data;
    int num;
    int capacity;
    int typeSize;
};
typedef struct SimpleArray_s* SimpleArray_t;
typedef struct SimpleArray_s SimpleArray;

// Create a new simple array, the typeSize is the size of the type of the element
SimpleArray_t SimpleArray_newArray(int typeSize);

// Create a new simple array with capacity, the typeSize is the size of the type of the element
SimpleArray_t SimpleArray_newArrayWithCapacity(int typeSize, int capacity);

// Add an element to the simple array's tail, will copy the content of the element to the array
// remember to free the memory of the element if it's a pointer
int SimpleArray_addElement(SimpleArray_t array, const void* element);

// Get the element at the index, will check if the index is valid
// do not save the pointer of the element, it may be invalid after the array is modified
void* SimpleArray_getElement(SimpleArray_t array, int index);

// Free the simple array, will free the memory of the array and the elements
void SimpleArray_freeSimpleArray(SimpleArray_t array);

// Free the simple array with destructor, will free the memory of the array and the elements
void SimpleArray_freeSimpleArrayWithDestructor(SimpleArray_t array, Destructor elementDestructor);

// Reserve the simple array, will change the capacity of the array
void SimpleArray_reserve(SimpleArray_t array, int capacity);

// Set the element at the index, will copy the content of the element to the array
void SimpleArray_setElement(SimpleArray_t array, int index, const void* element);

// Insert an element to the simple array at the index, will move the elements after the index
void SimpleArray_insertElement(SimpleArray_t array, int index, void* element);

// Remove the element at the index, will move the elements after the index
void SimpleArray_removeElement(SimpleArray_t array, int index);

// Remove the element at the index with destructor, will move the elements after the index
void SimpleArray_removeElementWithDestructor(SimpleArray_t array, int index, Destructor elementDestructor);

// Clear the simple array, will free the memory of the elements
void SimpleArray_clear(SimpleArray_t array);

void SimpleArray_resize(SimpleArray_t array, int newSize);

void SimpleArray_zeroFilled(SimpleArray_t array);

#endif //LAB1_SIMPLEARRAY_H
