//
// Created by Crystal on 2024/3/19.
//

#ifndef LAB1_SYMBOLTABLE_H
#define LAB1_SYMBOLTABLE_H

#include "SimpleArray.h"

#define THOUSAND_HASH_TABLE_SIZE 1009
#define DEFAULT_HASH_BUCKET_SIZE 10

typedef int (*HashFunc)(const char*, int);
typedef int (*CompareFunc)(const void*, const void*);

typedef struct SimpleHashTable_s{
    HashFunc hashFunc;
    CompareFunc compareFunc;
    SimpleArray_t elementTable;
    int elementSize;
    int size;
}SimpleHashTable;
typedef SimpleHashTable* SimpleHashTable_t;

typedef SimpleArray_t SymbolTableStack_t;

// create a hash table with the given element size, hash function, compare function and size
SimpleHashTable_t SimpleHashTable_createHashTable(int elementSize, HashFunc hashFunc, CompareFunc compareFunc, int size);

// destroy the hash table, and call the destructor on every element if it is not NULL
void SimpleHashTable_destroyHashTable(SimpleHashTable_t hashTable, Destructor destructor);

// insert the element with the key, if the key already exists, a new element will still be inserted
// if you don't want this, you should call SimpleHashTable_find to check if the key already exists
void SimpleHashTable_insert(SimpleHashTable_t hashTable, const char* key, const void* element);

// find the element with the key, return NULL if the key does not exist
void* SimpleHashTable_find(SimpleHashTable_t hashTable, const char* key);

// remove the element with the key, and call the destructor if it is not NULL
void SimpleHashTable_removeWithDestructor(SimpleHashTable_t hashTable, const char* key, Destructor destructor);

typedef SimpleHashTable_t SymbolTable_t;

// create a symbol table
SymbolTable_t SymbolTable_createSymbolTable();

// destroy the symbol table
void SymbolTable_destroySymbolTable(SymbolTable_t symbolTable);

// insert the symbol into the symbol table, will allocate memory in hashtable for the symbol
void SymbolTable_insert(SymbolTable_t symbolTable, const char* Symbol);

// find the symbol in the symbol table, return NULL if the symbol does not exist
void* SymbolTable_find(SymbolTable_t symbolTable, const char* Symbol);

// remove the symbol from the symbol table, and free the memory in hashtable for the symbol
void SymbolTable_remove(SymbolTable_t symbolTable, const char* Symbol);

// create a symbol table stack
SymbolTableStack_t SymbolTableStack_createSymbolTableStack();

// destroy the symbol table stack
void SymbolTableStack_destroySymbolTableStack(SymbolTableStack_t symbolTableStack);

// push the symbol table into the symbol table stack
void SymbolTableStack_push(SymbolTableStack_t symbolTableStack, SymbolTable_t symbolTable);

// pop the symbol table from the symbol table stack
SymbolTable_t SymbolTableStack_pop(SymbolTableStack_t symbolTableStack);

// get the top symbol table from the symbol table stack
SymbolTable_t SymbolTableStack_top(SymbolTableStack_t symbolTableStack);

// get the symbol table from the symbol table stack from top to down
SymbolTable_t SymbolTableStack_topDown(SymbolTableStack_t symbolTableStack, int index);

// get the size of the symbol table stack
int SymbolTableStack_getSize(SymbolTableStack_t symbolTableStack);

SymbolTable_t SymbolTableStack_pushNew(SymbolTableStack_t symbolTableStack);

#endif //LAB1_SYMBOLTABLE_H
