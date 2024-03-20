//
// Created by Crystal on 2024/3/19.
//

#ifndef LAB1_SYMBOLTABLE_H
#define LAB1_SYMBOLTABLE_H

#include "SimpleArray.h"
#include "SimpleHashTable.h"

typedef SimpleArray_t SymbolTableStack_t;

typedef SimpleHashTable_t SymbolTable_t;

typedef struct SymbolRecord_s {
    char *key;
    void *element;
} SymbolRecord;
typedef SymbolRecord* SymbolRecord_t;

// create a token table
SimpleHashTable * SymbolTable_createSymbolTable();

// destroy the token table
void SymbolTable_destroySymbolTable(SimpleHashTable * symbolTable);

// insert the token into the token table, will allocate memory in hashtable for the token
void SymbolTable_insert(SimpleHashTable * symbolTable, const char* Symbol);

// find the token in the token table, return NULL if the token does not exist
void* SymbolTable_find(SimpleHashTable * symbolTable, const char* Symbol);

// remove the token from the token table, and free the memory in hashtable for the token
void SymbolTable_remove(SimpleHashTable * symbolTable, const char* Symbol);

// create a token table stack
SymbolTableStack_t SymbolTableStack_createSymbolTableStack();

// destroy the token table stack
void SymbolTableStack_destroySymbolTableStack(SymbolTableStack_t symbolTableStack);

// push the token table into the token table stack
void SymbolTableStack_push(SymbolTableStack_t symbolTableStack, SimpleHashTable * symbolTable);

// pop the token table from the token table stack
SimpleHashTable * SymbolTableStack_pop(SymbolTableStack_t symbolTableStack);

// get the top token table from the token table stack
SimpleHashTable * SymbolTableStack_top(SymbolTableStack_t symbolTableStack);

// get the token table from the token table stack from top to down
SimpleHashTable * SymbolTableStack_topDown(SymbolTableStack_t symbolTableStack, int index);

// get the size of the token table stack
int SymbolTableStack_getSize(SymbolTableStack_t symbolTableStack);

SimpleHashTable * SymbolTableStack_pushNew(SymbolTableStack_t symbolTableStack);

#endif //LAB1_SYMBOLTABLE_H
