//
// Created by Crystal on 2024/3/19.
//

#include <string.h>
#include <stdlib.h>

#include "Structure/SymbolTable.h"
#include "Structure/SimpleHashTable.h"
#include "SimpleHashTable.h"

int stringCompare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}


SimpleHashTable * SymbolTable_createSymbolTable() {
    return SimpleHashTable_createHashTableWithSize(sizeof(char *), pjwHash, stringCompare, THOUSAND_HASH_TABLE_SIZE);
}

void SymbolTable_destroySymbolTable(SimpleHashTable * symbolTable) {
    SimpleHashTable_destroyHashTable(symbolTable, free);
}

void SymbolTable_insert(SimpleHashTable * symbolTable, const char* Symbol) {
    char* newSymbol = (char*)malloc(strlen(Symbol) + 1);
    strcpy(newSymbol, Symbol);
    SimpleHashTable_insert(symbolTable, Symbol, &newSymbol);
}

void* SymbolTable_find(SimpleHashTable * symbolTable, const char* Symbol) {
    return SimpleHashTable_findWithKey(symbolTable, Symbol);
}

void SymbolTable_remove(SimpleHashTable * symbolTable, const char* Symbol) {
    SimpleHashTable_removeWithDestructor(symbolTable, Symbol, free);
}

SymbolTableStack_t SymbolTableStack_createSymbolTableStack() {
    return SimpleArray_newArray(sizeof(SimpleHashTable *));
}

void SymbolTableStack_destroySymbolTableStack(SymbolTableStack_t symbolTableStack) {
    for (int i = 0; i < symbolTableStack->num; i++) {
        SymbolTable_destroySymbolTable(*(SimpleHashTable * *)SimpleArray_getElement(symbolTableStack, i));
    }
    SimpleArray_freeSimpleArray(symbolTableStack);
}

void SymbolTableStack_push(SymbolTableStack_t symbolTableStack, SimpleHashTable * symbolTable) {
    SimpleArray_addElement(symbolTableStack, &symbolTable);
}

SimpleHashTable * SymbolTableStack_pop(SymbolTableStack_t symbolTableStack) {
    SimpleHashTable * symbolTable = SimpleArray_getElement(symbolTableStack, symbolTableStack->num - 1);
    SimpleArray_removeElement(symbolTableStack, symbolTableStack->num - 1);
    return symbolTable;
}

SimpleHashTable * SymbolTableStack_top(SymbolTableStack_t symbolTableStack) {
    return SimpleArray_getElement(symbolTableStack, symbolTableStack->num - 1);
}

SimpleHashTable * SymbolTableStack_topDown(SymbolTableStack_t symbolTableStack, int index) {
    return SimpleArray_getElement(symbolTableStack, symbolTableStack->num - 1 - index);
}

int SymbolTableStack_getSize(SymbolTableStack_t symbolTableStack) {
    return symbolTableStack->num;
}

SimpleHashTable * SymbolTableStack_pushNew(SymbolTableStack_t symbolTableStack) {
    SimpleHashTable * symbolTable = SymbolTable_createSymbolTable();
    SymbolTableStack_push(symbolTableStack, symbolTable);
    return symbolTable;
}


