//
// Created by Crystal on 2024/3/19.
//

#include <string.h>
#include <stdlib.h>

#include "Structure/SymbolTable.h"

int pjwHash(const char* key, int size) {
    const int BitsInUnsignedInt = (int)(sizeof(int) * 8);
    const int ThreeQuarters = (int)((BitsInUnsignedInt * 3) / 4);
    const int OneEighth = (int)(BitsInUnsignedInt / 8);
    const int HighBits = (int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    int hash = 0;
    int test = 0;

    for (int i = 0; i < strlen(key); i++) {
        hash = (hash << OneEighth) + key[i];

        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash % size;
}

int stringCompare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

SimpleHashTable_t SimpleHashTable_createHashTable(int elementSize, HashFunc hashFunc, CompareFunc compareFunc, int size) {
    SimpleHashTable_t hashTable = (SimpleHashTable_t)malloc(sizeof(SimpleHashTable));
    hashTable->hashFunc = hashFunc;
    hashTable->compareFunc = compareFunc;
    hashTable->elementSize = elementSize;
    hashTable->elementTable = SimpleArray_newArrayWithCapacity(sizeof(SimpleArray_t), DEFAULT_HASH_BUCKET_SIZE*2);
    hashTable->size = size;
    SimpleArray_resize(hashTable->elementTable, THOUSAND_HASH_TABLE_SIZE);
    SimpleArray_zeroFilled(hashTable->elementTable);
    return hashTable;
}

void SimpleHashTable_destroyHashTable(SimpleHashTable_t hashTable, Destructor destructor) {
    for (int i = 0; i < THOUSAND_HASH_TABLE_SIZE; i++) {
        SimpleArray_t list = (SimpleArray_t)SimpleArray_getElement(hashTable->elementTable, i);
        if (list != NULL) {
            if(destructor != NULL) {
                SimpleArray_freeSimpleArrayWithDestructor(list, destructor);
            }
        }
    }
    SimpleArray_freeSimpleArray(hashTable->elementTable);
    free(hashTable);
}

void SimpleHashTable_insert(SimpleHashTable_t hashTable, const char* key, const void* element) {
    int index = hashTable->hashFunc(key, hashTable->size);
    SimpleArray_t list = (SimpleArray_t)SimpleArray_getElement(hashTable->elementTable, index);
    if (list == NULL) {
        list = SimpleArray_newArray(hashTable->elementSize);
        SimpleArray_setElement(hashTable->elementTable, index, &list);
    }
    SimpleArray_addElement(list, element);
}

void* SimpleHashTable_find(SimpleHashTable_t hashTable, const char* key) {
    int index = hashTable->hashFunc(key, hashTable->size);
    SimpleArray_t list = (SimpleArray_t)SimpleArray_getElement(hashTable->elementTable, index);
    if (list == NULL) {
        return NULL;
    }
    for (int i = 0; i < list->num; i++) {
        if (hashTable->compareFunc(key, SimpleArray_getElement(list, i)) == 0) {
            return SimpleArray_getElement(list, i);
        }
    }
    return NULL;
}


void SimpleHashTable_removeWithDestructor(SimpleHashTable_t hashTable, const char* key, Destructor destructor) {
    int index = hashTable->hashFunc(key, hashTable->size);
    SimpleArray_t list = (SimpleArray_t)SimpleArray_getElement(hashTable->elementTable, index);
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->num; i++) {
        if (hashTable->compareFunc(key, SimpleArray_getElement(list, i)) == 0) {
            SimpleArray_removeElementWithDestructor(list, i, destructor);
            return;
        }
    }
}

SymbolTable_t SymbolTable_createSymbolTable() {
    return SimpleHashTable_createHashTable(sizeof(char*), pjwHash, stringCompare, THOUSAND_HASH_TABLE_SIZE);
}

void SymbolTable_destroySymbolTable(SymbolTable_t symbolTable) {
    SimpleHashTable_destroyHashTable(symbolTable, free);
}

void SymbolTable_insert(SymbolTable_t symbolTable, const char* Symbol) {
    char* newSymbol = (char*)malloc(strlen(Symbol) + 1);
    strcpy(newSymbol, Symbol);
    SimpleHashTable_insert(symbolTable, Symbol, &newSymbol);
}

void* SymbolTable_find(SymbolTable_t symbolTable, const char* Symbol) {
    return SimpleHashTable_find(symbolTable, Symbol);
}

void SymbolTable_remove(SymbolTable_t symbolTable, const char* Symbol) {
    SimpleHashTable_removeWithDestructor(symbolTable, Symbol, free);
}

SymbolTableStack_t SymbolTableStack_createSymbolTableStack() {
    return SimpleArray_newArray(sizeof(SymbolTable_t));
}

void SymbolTableStack_destroySymbolTableStack(SymbolTableStack_t symbolTableStack) {
    for (int i = 0; i < symbolTableStack->num; i++) {
        SymbolTable_destroySymbolTable(*(SymbolTable_t*)SimpleArray_getElement(symbolTableStack, i));
    }
    SimpleArray_freeSimpleArray(symbolTableStack);
}

void SymbolTableStack_push(SymbolTableStack_t symbolTableStack, SymbolTable_t symbolTable) {
    SimpleArray_addElement(symbolTableStack, &symbolTable);
}

SymbolTable_t SymbolTableStack_pop(SymbolTableStack_t symbolTableStack) {
    SymbolTable_t symbolTable = SimpleArray_getElement(symbolTableStack, symbolTableStack->num - 1);
    SimpleArray_removeElement(symbolTableStack, symbolTableStack->num - 1);
    return symbolTable;
}

SymbolTable_t SymbolTableStack_top(SymbolTableStack_t symbolTableStack) {
    return SimpleArray_getElement(symbolTableStack, symbolTableStack->num - 1);
}

SymbolTable_t SymbolTableStack_topDown(SymbolTableStack_t symbolTableStack, int index) {
    return SimpleArray_getElement(symbolTableStack, symbolTableStack->num - 1 - index);
}

int SymbolTableStack_getSize(SymbolTableStack_t symbolTableStack) {
    return symbolTableStack->num;
}

SymbolTable_t SymbolTableStack_pushNew(SymbolTableStack_t symbolTableStack) {
    SymbolTable_t symbolTable = SymbolTable_createSymbolTable();
    SymbolTableStack_push(symbolTableStack, symbolTable);
    return symbolTable;
}


