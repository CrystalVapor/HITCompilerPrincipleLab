//
// Created by m1504 on 2024/3/20.
//

#ifndef LAB1_SIMPLEHASHTABLE_H
#define LAB1_SIMPLEHASHTABLE_H

#include "Structure/SimpleHashTable.h"
#include <malloc.h>
#include <string.h>
#include "SimpleArray.h"

#define THOUSAND_HASH_TABLE_SIZE 1009
#define DEFAULT_HASH_BUCKET_SIZE 10
struct SimpleHashTable_s;
typedef struct SimpleHashTable_s * SimpleHashTable_t;

// hash function, return the hash value of the key
typedef int (*HashFunc)(const void* key, int keySize, int tableSize);

// compare function, return 0 if the two keys are the same
typedef int (*CompareFunc)(const void* keyA, const void* keyB, int keySize);

// used for traverse the hash table, will be called on every element
typedef void (*TraverseFunc)(const void* element);

typedef struct SimpleHashTablePair_s {
    void* key;
    int keySize;
    void* element;
}SimpleHashTablePair;
typedef SimpleHashTablePair* SimpleHashTablePair_t;

typedef struct SimpleHashTable_s{
    HashFunc hashFunc;
    CompareFunc compareFunc;
    SimpleArray_t data;
    int elementSize;
    int keySize;
    int tableSize;
}SimpleHashTable;
typedef SimpleHashTable* SimpleHashTable_t;

// create a hash table with the given element size, hash function and compare function, default table size is THOUSAND_HASH_TABLE_SIZE
// set Func to NULL to Use the default hash function and compare function
// the default hash function is pjwHash on whole key, and the default compare function is memcmp on whole key
SimpleHashTable_t SimpleHashTable_createHashTable(int elementSize, HashFunc hashFunc, CompareFunc compareFunc);

// create a hash table with the given element size, hash function, compare function and tableSize
// set Func to NULL to Use the default hash function and compare function
// the default hash function is pjwHash on whole key, and the default compare function is memcmp on whole key
SimpleHashTable_t SimpleHashTable_createWithSize(int elementSize, HashFunc keyHashFunc, CompareFunc keyCompareFunc, int tableSize);

// destroy the hash table, and call the destructor on every element if it is not NULL
void SimpleHashTable_destroy(SimpleHashTable_t hashTable, Destructor destructorForKey, Destructor destructorForElement);

// force insert the element with the key, and call the destructor if the key already exists and it is not NULL
void SimpleHashTable_forceInsert(SimpleHashTable_t hashTable, const void* key, int keySize, const void* element, Destructor destructorForKey, Destructor destructorForElement);

// insert the element with the key, will directly return -1 if the key already exists, otherwise return 0 and insert the element
int SimpleHashTable_insert(SimpleHashTable_t hashTable, const void* key, int keySize, const void* element);

// find the element(s) with the key, return NULL if the key does not exist, notice
void* SimpleHashTable_find(SimpleHashTable_t hashTable, const void* key, int keySize);

// remove the element with the key, and call the destructor if it is not NULL
void SimpleHashTable_removeWithDestructor(SimpleHashTable_t hashTable, const void* key, int keySize, Destructor destructorForKey, Destructor destructorForElement);

void SimpleHashTable_traverse(SimpleHashTable_t hashTable, TraverseFunc traverseFunc);

int pjwHash(const char* key, int keySize, int size);

#endif //LAB1_SIMPLEHASHTABLE_H
