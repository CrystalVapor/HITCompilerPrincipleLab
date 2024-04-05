//
// Created by Crystal on 2024/4/3.
//

#ifndef LAB1_SIMPLELIST_H
#define LAB1_SIMPLELIST_H

typedef struct SimpleListNode_s {
    struct SimpleListNode_s *next;
    struct SimpleListNode_s *prev;
    void *data;
}SimpleListNode;
typedef struct SimpleListNode_s* SimpleListNode_t;

typedef struct SimpleList_s{
    SimpleListNode_t head;
    SimpleListNode_t tail;
    int size;
}SimpleList;
typedef struct SimpleList_s* SimpleList_t;

/**
 * Create an empty list
 * @return new list
 */
SimpleList_t SimpleList_create();

/**
 * Destroy a list
 * @param list list to destroy
 * @param destroyData function to destroy data
 * @return NULL
 */
SimpleList_t SimpleList_destroy(SimpleList_t list, void (*destroyData)(void* data));

/**
 * Push data to the back of the list, will create a new node
 * @param list list to push
 * @param data data to push
 * @return new node
 */
SimpleListNode_t SimpleList_push_back(SimpleList_t list, void* data);

/**
 * Push data to the front of the list, will create a new node
 * @param list list to push
 * @param data data to push
 * @return new node
 */
SimpleListNode_t SimpleList_push_front(SimpleList_t list, void* data);

/**
 * Pop the last node of the list
 * @param list
 * @return the data of the last node
 */
void* SimpleList_pop_back(SimpleList_t list);

/**
 * Pop the first node of the list
 * @param list
 * @return the data of the first node
 */
void* SimpleList_pop_front(SimpleList_t list);

/**
 * Insert data to the list before the given position
 * @param list list to insert
 * @param pos position to insert
 * @param data data to insert
 */
void SimpleList_insertBefore(SimpleList_t list, SimpleListNode_t pos, void* data);

/**
 * Insert data to the list after the given position
 * @param list list to insert
 * @param pos position to insert
 * @param data data to insert
 */
void SimpleList_insertAfter(SimpleList_t list, SimpleListNode_t pos, void* data);

/**
 * Append list2 to list1
 * do not use list2 or list1 after this operation, it's not safe
 * only returned list is considered valid
 * @param list1
 * @param list2
 * @return appended list1
 */
SimpleList_t SimpleList_append(SimpleList_t list1, SimpleList_t list2);
#endif //LAB1_SIMPLELIST_H
