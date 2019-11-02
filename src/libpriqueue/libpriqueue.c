/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"


void node_init(list_node *n, void* v) {
  n->next = NULL;
  n->prev = NULL;
  n->val = v;
}


/**
  Initializes the priqueue_t data structure.
  
  Assumtions
    - You may assume this function will only be called once per instance of priqueue_t
    - You may assume this function will be the first function called using an instance of priqueue_t.
  @param q a pointer to an instance of the priqueue_t data structure
  @param comparer a function pointer that compares two elements.
  See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
  q->cmp = comparer;
  q->size = 0;
  q->head = NULL;
  q->tail = NULL;
}


/**
  Insert the specified element into this priority queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr a pointer to the data to be inserted into the priority queue
  @return The zero-based index where ptr is stored in the priority queue, where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
  list_node* entry = malloc(sizeof(list_node));
  node_init(entry, ptr);

  int index = 0;
  list_node* iter = q->head;

  if(iter == NULL) {
    q->head = entry;
  }
  else {
    while(iter->next != NULL && q->cmp(iter->val, ptr) > 0) {
      iter = iter->next;
      index++;
    }
    if(iter->prev != NULL) iter->prev->next = entry;
    entry->next = iter->next;
    entry->prev = iter;
    if(iter->next != NULL) iter->next = entry;
  }

  if(index == 0) {
    q->head = entry;
  }

  if(index == q->size) {
    q->tail = entry;
  }
  
  q->size++;
  print_queue(q);
  return index;
}


/**
  Retrieves, but does not remove, the head of this queue, returning NULL if
  this queue is empty.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return pointer to element at the head of the queue
  @return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
  if(q->size == 0) return NULL;
	return q->head;
}

void print_queue(priqueue_t *q) {
  list_node* t;
  for(t = q->head; t != NULL; t = t->next) {
    printf("%d ", *(int *)(t->val));
  }
  printf("\n");
}

/**
  Retrieves and removes the head of this queue, or NULL if this queue
  is empty.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return the head of this queue
  @return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
  if(q->size == 0) return NULL;
  list_node *head = priqueue_at(q, 0);
  priqueue_remove_at(q, 0);
  return head;
}


/**
  Returns the element at the specified position in this list, or NULL if
  the queue does not contain an index'th element.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of retrieved element
  @return the index'th element in the queue
  @return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
  if(index >= q->size) return NULL;
   list_node* node = q->head;
  while (index > 0 && node != NULL) {
    node = node->next;
    index--;
  }
	return node;
}


/**
  Removes all instances of ptr from the queue. 
  
  This function should not use the comparer function, but check if the data contained in each element of the queue is equal (==) to ptr.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr address of element to be removed
  @return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
  int count = 0;
  list_node* temp = q->head;
  while(temp != NULL) {
    if(temp->val == ptr) {
      list_node* nodeToDelete = temp;
      temp->prev->next = temp->next;
      temp = temp->next;
      free(nodeToDelete);
      count++;
    }
    else {
      temp = temp->next;
    }
  }
  q->size -= count;
	return count;
}


/**
  Removes the specified index from the queue, moving later elements up
  a spot in the queue to fill the gap.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of element to be removed
  @return the element removed from the queue
  @return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
  if(index >= q->size) return NULL;

  list_node* temp = q->head;
  while(index > 1) {
    temp = temp->next;
    index--;
  }
  if(temp->prev != NULL) temp->prev->next = temp->next;
  void* element = temp->val;
  free(temp);
  q->size--;
	return element;
}


/**
  Return the number of elements in the queue.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
	return q->size;;
}


/**
  Destroys and frees all the memory associated with q.
  
  @param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{
  list_node* x = q->head;
  list_node* temp;
  while(x != NULL) {
    temp = x->next;
    free(x);
    x = temp;
  }
}
