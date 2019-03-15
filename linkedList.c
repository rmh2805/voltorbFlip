/// file: linkedList.c
/// author: rmh2805@rit.edu
/// purpose: An opaque linked list ADT implementation in C 
#include "linkedList.h"

struct node_s {
    void * val;
    struct node_s * next;
};

typedef struct node_s * node_t;

struct linkedList_s {
    node_t first;
    node_t last;
    freeVal_f freeVal;
    size_t size;
};
//=============================================================================//
//==================================<Statics>==================================//
//=============================================================================//
//====================<Static Allocation and Freeing>=====================//
/**
  * Creates a new node with the provided value
  * 
  * @param val The value to associate with the new node
  * @return The newly created node (NULL if failed)
  */
static node_t createNode (void* val){
    node_t new = malloc(sizeof(struct node_s));
    if(!new)
        return NULL;
    
    new->val = val;
    new->next = NULL;
    return new;
}

/**
  * Frees the provided node and its associated value
  * 
  * @param node The node to free
  * @param freeVal The pointer to the function to free the value
  * @return 'node's 'next' value 
  */ 
static node_t deleteNode (node_t node, freeVal_f freeVal){
    if (node == NULL) {
        return NULL;
    }
    node_t toReturn = node->next;
    
    if (freeVal) {
        freeVal(node->val);
        node->val = NULL;
    }
    
    free(node);
    return toReturn;        
}

//===========================<Static Utilities>===========================//
/**
  * Returns the node at index 'idx' on 'list'
  * 
  * @param list The linked list to traverse
  * @param idx The index to grab
  * @return The node at 'idx' on 'list'
  */
static node_t traverseToIdx (linkedList_t list, size_t idx){
    if (list == NULL) {
        return NULL;
    }
    
    if(list->first == NULL || list->size <= idx){
        return NULL;
    } 
    
    if (list->size - 1 == idx) {
        return list->last;
    } 

    node_t node = list->first;
    
    for(size_t i = 0; i < idx; i++){
        if (node->next == NULL)
            return NULL;
        node = node->next;
    }
        
    return node;
}

//=============================================================================//
//================================<Non-Statics>================================//
//=============================================================================//
//========================<Allocation and Freeing>========================//
linkedList_t createLinkedList (freeVal_f freeVal) {
    linkedList_t new = malloc(sizeof(struct linkedList_s));
    if (new == NULL)
        return NULL;
    
    new->first = NULL;
    new->last = NULL;    
    new->freeVal = freeVal;
    new->size = 0;
    
    return new;
}

void deleteLinkedList (linkedList_t list) {
    if (list != NULL) {    
        node_t node = list->first;
        while (node != NULL)
            node = deleteNode(node, list->freeVal);
        
        list->first = NULL;
        list->last = NULL;
        free(list);
    }
}

//==============================<Add Nodes>===============================//
size_t insertAtIdx(linkedList_t list, void* val, size_t idx) {
    if (list == NULL) {
        return 0;
    }
    
    if (idx == 0) {
        prepend(list, val);
        return 0;
    }
    
    if (idx < list->size) {
        node_t prev = traverseToIdx(list, idx-1);
        
        if (prev != NULL) {
            node_t new = createNode(val);
            
            if (new == NULL)
                return 0;
            
            new->next = prev->next;
            prev->next = new;
            list->size += 1;
            return idx;
        }
    } 
    
    return append(list, val);
}

size_t prepend(linkedList_t list, void* val){
    if(list == NULL) {
        return 1;
    }
    
    node_t new = createNode(val);
    
    if (new == NULL)
        return 1;
    
    if (list->first == NULL) {
        list->first = new;
        list->last = new;
    } else {
        node_t next = list->first;
        new->next = next;
        list->first = new;
    }
    
    list->size += 1;
    return 0;
}

size_t append (linkedList_t list, void* val) {
    if (list) {
        node_t new = createNode(val);
        size_t idx = list->size;
        
        if (new == NULL)
            return 0;
        
        if(list->last == NULL) {
            list->first = new;
            list->last = new;
            list->size = 0;
            idx = 0;
        } else {
            list->last->next = new;
            list->last = new;
        }
        
        list->size += 1;
        return idx;
    } else {
        return 0;
    }
}

size_t addNodes(linkedList_t list, size_t numNodes){
    for (size_t i = 0; i < numNodes; i++){
        append(list, NULL);
    }
    
    return list->size - 1;
}
 
//=============================<Remove Nodes>=============================//
void* removeIdx (linkedList_t list, size_t idx){
    if(list == NULL) 
        return NULL;
    
    node_t prev = traverseToIdx(list, idx - 1);
    
    if(prev == NULL)
        return NULL;
    
    if(prev->next == NULL)
        return NULL;
        
    void* val = prev->next->val;
    prev->next = deleteNode(prev->next, NULL);
    
    list->size -= 1;
    
    return val;
}

void deleteIdx (linkedList_t list, size_t idx){
    if (list) { 
        void* val = removeIdx (list, idx);
        
        if (val != NULL && list->freeVal != NULL) {
            list->freeVal(val);
        }
    }
}

//=========================<Getters And Setters>==========================//
void* getIdx (linkedList_t list, size_t idx) {
    if(list == NULL)
        return NULL;
        
    node_t node = traverseToIdx(list, idx);
    
    if(node == NULL)
        return NULL;
    
    return node->val;
}

void setIdx (linkedList_t list, size_t idx, void* val){
    if(list != NULL){
        node_t node = traverseToIdx(list, idx);
        
        if(node != NULL){
            if(list->freeVal != NULL)
                list->freeVal(node->val);
                
            node->val = val;
        }
    }
}

size_t getSize (linkedList_t list){
    if(list == NULL)
        return 0;
    return list->size;
}
