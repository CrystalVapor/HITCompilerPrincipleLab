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

/**
 * A hash function that takes a key and returns a hash value.
 * @param key the key to be hashed
 * @param keySize the size of the key
 * @param tableSize the size of the hash table
 * @return the hash value of the key
 */
typedef int (*HashFunc)(const void* key, int keySize, int tableSize);

/**
 * A compare function that takes two keys and returns 0 if they are the same.
 * @param keyA the first key
 * @param keyB the second key
 * @param keySize the size of the key
 * @return 0 if the two keys are the same, otherwise return a non-zero value
 */
typedef int (*CompareFunc)(const void* keyA, const void* keyB, int keySize);

/**
 * A Traverse function that takes an element and do something with it.
 * @param element the element to be traversed
 */
typedef void (*TraverseFunc)(const void* element);

/**
 * An advanced traverse function that takes a key, an element and extra parameters and do something with them.
 * @param key the key of the element
 * @param keySize the size of the key
 * @param element the element to be traversed
 * @param extraParamCount the number of extra parameters
 * @param ... the extra parameters
 */
typedef void (*AdvancedTraverseFunc)(const void* key, int keySize, const void* element, int extraParamCount, ...);

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

/**
 * Create a hash table with the given element size, hash function and compare function, default table size is THOUSAND_HASH_TABLE_SIZE
 * @param elementSize the size of the element
 * @param hashFunc the hash function, use NULL to use the default hash function(pjw)
 * @param compareFunc the compare function, use NULL to use the default compare function(memcmp)
 * @return the created hash table
 */
SimpleHashTable_t SimpleHashTable_createHashTable(int elementSize, HashFunc hashFunc, CompareFunc compareFunc);

/**
 * Create a hash table with the given element size, hash function, compare function and table size
 * @param elementSize the size of the element
 * @param keyHashFunc the hash function for the key, use NULL to use the default hash function(pjw)
 * @param keyCompareFunc the compare function for the key, use NULL to use the default compare function(memcmp)
 * @param tableSize the size of the hash table
 * @return the created hash table
 */
SimpleHashTable_t SimpleHashTable_createWithSize(int elementSize, HashFunc keyHashFunc, CompareFunc keyCompareFunc, int tableSize);

/**
 * Destroy the hash table, and call the destructor on every element if it is not NULL
 * @param hashTable the hash table to be destroyed
 * @param destructorForKey the destructor for the key, use NULL if no destructor is needed
 * @param destructorForElement the destructor for the element, use NULL if no destructor is needed
 */
void SimpleHashTable_destroy(SimpleHashTable_t hashTable, Destructor destructorForKey, Destructor destructorForElement);

/**
 * Force insert the element with the key, and call the destructor if the key already exists and it is not NULL
 * @param hashTable table to insert
 * @param key key to insert
 * @param keySize size of the key
 * @param element element to insert
 * @param destructorForKey destructor for the key
 * @param destructorForElement destructor for the element
 */
void SimpleHashTable_forceInsert(SimpleHashTable_t hashTable, const void* key, int keySize, const void* element, Destructor destructorForKey, Destructor destructorForElement);

/**
 * Insert the element with the key, will not insert if the key already exists
 * @param hashTable the hash table to insert
 * @param key the key to insert
 * @param keySize the size of the key
 * @param element the element to insert
 * @return 0 if the element is inserted successfully, -1 if the key already exists
 */
int SimpleHashTable_insert(SimpleHashTable_t hashTable, const void* key, int keySize, const void* element);

/**
 * Find the element with the key
 * @param hashTable the hash table to find
 * @param key the key to find
 * @param keySize the size of the key
 * @return the element with the key, NULL if the key does not exist
 */
void* SimpleHashTable_find(SimpleHashTable_t hashTable, const void* key, int keySize);

/**
 * Remove the element with the key, and call the destructor if it is not NULL
 * @param hashTable the hash table to remove
 * @param key the key to remove
 * @param keySize the size of the key
 * @param destructorForKey the destructor for the key, use NULL if no destructor is needed
 * @param destructorForElement the destructor for the element, use NULL if no destructor is needed
 */
void SimpleHashTable_remove(SimpleHashTable_t hashTable, const void* key, int keySize, Destructor destructorForKey, Destructor destructorForElement);

/**
 * Traverse the hash table and call the traverse function on every element
 * @param hashTable the hash table to traverse
 * @param traverseFunc the traverse function
 */
void SimpleHashTable_traverse(SimpleHashTable_t hashTable, TraverseFunc traverseFunc);

/**
 * Traverse the hash table and call the advanced traverse function on every element
 * @param hashTable the hash table to traverse
 * @param traverseFunc the advanced traverse function
 * @param extraParamCount the number of extra parameters
 * @param ... the extra parameters
 */
void SimpleHashTable_advancedTraverse(SimpleHashTable_t hashTable, AdvancedTraverseFunc traverseFunc, int extraParamCount, ...);

/**
 * Default hash function, use PJW hash algorithm
 * @param key       the key to be hashed
 * @param keySize   the size of the key
 * @param size      the size of the hash table
 * @return          the hash value of the key
 */
int pjwHash(const char* key, int keySize, int size);

#endif //LAB1_SIMPLEHASHTABLE_H
