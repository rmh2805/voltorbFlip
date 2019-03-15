/// file: linkedList.h
/// author: rmh2805@rit.edu
/// purpose: An opaque linked list ADT implementation in C

#ifndef   _LINKED_LIST_H_
#define   _LINKED_LIST_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct linkedList_s * linkedList_t;
typedef void (*freeVal_f)(void*);

//==========================<Allocation and Freeing>===========================//
/**
  * Creates a pointer to an empty linked list ADT
  * 
  * @param freeVal The routine to free provided values, takes a void*. If not needed, pass NULL
  * @return The allocated and initialized LinkedList (NULL if failed)
  */
linkedList_t createLinkedList(freeVal_f freeVal);

/**
  * Frees the Linked list, including properly handling stored values
  * 
  * @param list The linked list to free
  */
void deleteLinkedList(linkedList_t list);

//=================================<Add Nodes>=================================//
/**
  * Adds 'val' at index 'i' in linked list 'list'
  * 
  * @param list The linked list to insert into
  * @param val The value to insert into the list
  * @param idx The index to insert at ('val' will be inserted here)
  * @note If 'idx' is out of range (not less than the size after insertion), val will be appended to the list
  * @return The address 'val' was inserted at (either 'idx' or the last valid index on the list) 
  */
size_t insertAtIdx(linkedList_t list, void* val, size_t idx);

/**
  * Adds a new node with the provided value to the start of the list
  * 
  * @param list The linked list to modify
  * @param val The value to add to the list
  * @return 0 if successful, 1 if failed
  */ 
size_t prepend(linkedList_t list, void* val);

/**
  * Adds a new node with the provided value to the end of the list
  * 
  * @param list The linked list to modify
  * @param val The value to add to the list
  * @return The index val was added at (last index on the list)
  */
size_t append(linkedList_t list, void* val);

/**
  * Appends 'numNodes' empty nodes to the end of 'list' (values are all NULL)
  * 
  * @param list The linked list to modify
  * @param numNodes The number of empty nodes to append to the end of the list
  * @return The index of the last inserted node (last index on the list)
  */ 
size_t addNodes(linkedList_t list, size_t numNodes);
 
//===============================<Remove Nodes>================================//
/**
  * Removes node at index 'idx' from the list without freeing the associated value
  * 
  * @param list The linked list to modify
  * @param idx The index to remove
  * @return The value formerly at 'idx', NULL if invalid index
  */
void* removeIdx (linkedList_t list, size_t idx);

/**
  * Removes node at index 'idx' from the list, freeing the associated value
  * 
  * @param list The linked list to modify
  * @param idx THe index to delete
  */
void deleteIdx (linkedList_t list, size_t idx);

//============================<Getters And Setters>============================//
/**
  * Returns the value at index 'idx' on 'list'
  * 
  * @param list The linked list to check
  * @param idx The index to get from
  * @return The value at the specified index (NULL if out of range)
  */
void* getIdx (linkedList_t list, size_t idx);

/**
  * Changes the value at index 'idx' on 'list' to 'val,' freeing the previous resident
  * @note No notification of failure (invalid index
  * 
  * @param list The linked list to modify
  * @param idx The index to set
  * @param val The value to set
  */
void setIdx (linkedList_t list, size_t idx, void* val);

/**
  * Grabs the size (number of elements in) the list
  * 
  * @param list The linked list to operate on
  * @return The size (number of elements in) the list
  */
size_t getSize (linkedList_t list);

#endif //_LINKED_LIST_H_
