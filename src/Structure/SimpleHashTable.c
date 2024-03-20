//
// Created by m1504 on 2024/3/20.
//


#include <string.h>
#include <malloc.h>
#include "Structure/SimpleHashTable.h"

void SimpleHashTablePair_setPair(SimpleHashTablePair_t pair, const void* key, int keySize, const void* element, int elementSize)
{
    pair->keySize = keySize;
    pair->key = malloc(keySize);
    pair->element = malloc(elementSize);
    memcpy(pair->key, key, keySize);
    memcpy(pair->element, element, elementSize);
}

void SimpleHashTablePair_clearPair(SimpleHashTablePair_t pair, Destructor destructorForKey, Destructor destructorForElement)
{
    if(destructorForKey != NULL)
    {
        destructorForKey(pair->key);
    }
    if(destructorForElement != NULL)
    {
        destructorForElement(pair->element);
    }
    free(pair->key);
    free(pair->element);
}

int pjwHash(const char* key, int keySize, int tableSize) {
    const int BitsInUnsignedInt = (int)(sizeof(int) * 8);
    const int ThreeQuarters = (int)((BitsInUnsignedInt * 3) / 4);
    const int OneEighth = (int)(BitsInUnsignedInt / 8);
    const int HighBits = (int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    int hash = 0;
    int test = 0;

    for (int i = 0; i < keySize; i++) {
        hash = (hash << OneEighth) + key[i];

        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash % tableSize;
}

int defaultCompare(const void* a, const void* b, int keySize) {
    return memcmp(a, b, keySize);
}

int defaultHash(const void* key, int keySize, int tableSize) {
    return pjwHash((const char*)key, keySize, tableSize);
}

SimpleHashTable_t SimpleHashTable_createHashTableWithSize(int elementSize, HashFunc hashFunc, CompareFunc compareFunc, int tableSize) {
    SimpleHashTable_t hashTable = (SimpleHashTable_t)malloc(sizeof(SimpleHashTable));
    hashTable->hashFunc = hashFunc == NULL ? defaultHash : hashFunc;
    hashTable->compareFunc = compareFunc == NULL ? defaultCompare : compareFunc;
    hashTable->elementSize = elementSize;
    hashTable->data = SimpleArray_newArray(sizeof(SimpleArray_t));
    hashTable->tableSize = tableSize;
    SimpleArray_resize(hashTable->data, tableSize);
    SimpleArray_zeroFilled(hashTable->data);
    return hashTable;
}

void SimpleHashTable_destroyHashTable(SimpleHashTable_t hashTable, Destructor destructorForKey, Destructor destructorForElement){
    for (int i = 0; i < THOUSAND_HASH_TABLE_SIZE; i++) {
        SimpleArray_t list = *((SimpleArray_t*)SimpleArray_getElement(hashTable->data, i));
        if (list != NULL) {
            for(int j = 0; j < list->num; j++)
            {
                SimpleHashTablePair_t pair = (SimpleHashTablePair_t)SimpleArray_getElement(list, j);
                SimpleHashTablePair_clearPair(pair, destructorForKey, destructorForElement);
            }
            SimpleArray_freeSimpleArray(list);
        }
    }
    SimpleArray_freeSimpleArray(hashTable->data);
    free(hashTable);
}

int SimpleHashTable_insert(SimpleHashTable_t hashTable, const void* key, int keySize, const void* element) {
    int index = hashTable->hashFunc(key, keySize, hashTable->tableSize);
    SimpleArray_t list = *((SimpleArray_t*)SimpleArray_getElement(hashTable->data, index));
    if (list == NULL) {
        list = SimpleArray_newArrayWithCapacity(sizeof(SimpleHashTablePair), DEFAULT_HASH_BUCKET_SIZE);
        SimpleArray_setElement(hashTable->data, index, &list);
    }
    for(int i = 0; i < list->num; i++)
    {
        SimpleHashTablePair_t pair = (SimpleHashTablePair_t)SimpleArray_getElement(list, i);
        if(pair->keySize == keySize && hashTable->compareFunc(pair->key, key, keySize) == 0)
        {
            return -1;
        }
    }
    SimpleHashTablePair newPair;
    SimpleHashTablePair_setPair(&newPair, key, keySize, element, hashTable->elementSize);
    SimpleArray_addElement(list, &newPair);
    return 0;
}

void* SimpleHashTable_find(SimpleHashTable_t hashTable, const void* key, int keySize) {
    int index = hashTable->hashFunc(key, keySize, hashTable->tableSize);
    SimpleArray_t list = *((SimpleArray_t*)SimpleArray_getElement(hashTable->data, index));
    if (list == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < list->num; i++) {
        SimpleHashTablePair_t pair = (SimpleHashTablePair_t)SimpleArray_getElement(list, i);
        if(pair->keySize == keySize && hashTable->compareFunc(pair->key, key, keySize) == 0)
        {
            return pair->element;
        }
    }
    return NULL;
}

void SimpleHashTable_removeWithDestructor(SimpleHashTable_t hashTable, const void* key, int keySize, Destructor destructorForKey, Destructor destructorForElement) {
    int index = hashTable->hashFunc(key, keySize, hashTable->tableSize);
    SimpleArray_t list = *((SimpleArray_t*)SimpleArray_getElement(hashTable->data, index));
    if (list == NULL)
    {
        return;
    }
    for (int i = 0; i < list->num; i++) {
        SimpleHashTablePair_t pair = (SimpleHashTablePair_t)SimpleArray_getElement(list, i);
        if(pair->keySize == keySize && hashTable->compareFunc(pair->key, key, keySize) == 0)
        {
            SimpleHashTablePair_clearPair(pair, destructorForKey, destructorForElement);
            SimpleArray_removeElement(list, i);
            return;
        }
    }
}

void SimpleHashTable_traverse(SimpleHashTable_t hashTable, TraverseFunc traverseFunc) {
    if(traverseFunc == NULL)
        return;
    for (int i = 0; i < hashTable->tableSize; i++) {
        SimpleArray_t list = *((SimpleArray_t*)SimpleArray_getElement(hashTable->data, i));
        if (list != NULL) {
            for (int j = 0; j < list->num; j++) {
                SimpleHashTablePair_t pair = (SimpleHashTablePair_t)SimpleArray_getElement(list, j);
                traverseFunc(pair->element);
            }
        }
    }
}

void SimpleHashTable_forceInsert(SimpleHashTable_t hashTable, const void *key, int keySize, const void *element,
                                 Destructor destructorForKey, Destructor destructorForElement) {
    int index = hashTable->hashFunc(key, keySize, hashTable->tableSize);
    SimpleArray_t list = *((SimpleArray_t*)SimpleArray_getElement(hashTable->data, index));
    if (list == NULL) {
        list = SimpleArray_newArrayWithCapacity(sizeof(SimpleHashTablePair), DEFAULT_HASH_BUCKET_SIZE);
        SimpleArray_setElement(hashTable->data, index, &list);
    }
    for(int i = 0; i < list->num; i++)
    {
        SimpleHashTablePair_t pair = (SimpleHashTablePair_t)SimpleArray_getElement(list, i);
        if(pair->keySize == keySize && hashTable->compareFunc(pair->key, key, keySize) == 0)
        {
            SimpleHashTablePair_clearPair(pair, destructorForKey, destructorForElement);
            SimpleHashTablePair_setPair(pair, key, keySize, element, hashTable->elementSize);
            return;
        }
    }
    SimpleHashTablePair newPair;
    SimpleHashTablePair_setPair(&newPair, key, keySize, element, hashTable->elementSize);
    SimpleArray_addElement(list, &newPair);
}

