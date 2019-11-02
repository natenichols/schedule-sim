/** @file libpriqueue.h
 */

#ifndef LIBPRIQUEUE_H_
#define LIBPRIQUEUE_H_

typedef struct _list_node
{
<<<<<<< HEAD
  struct list_node* next;
  struct list_node* prev;
=======
  struct heap_node* left;
  struct heap_node* right;
>>>>>>> 48ba4a687956f86f459c95530c88099ae054c0df
  void* val;
} list_node;


/**
  Priqueue Data Structure
*/
typedef struct _priqueue_t
{
  struct list_node* front;
  struct list_node* back;
  unsigned int size;
  int (*cmp)(const void*, const void*);
} priqueue_t;


void   priqueue_init     (priqueue_t *q, int(*comparer)(const void *, const void *));

int    priqueue_offer    (priqueue_t *q, void *ptr);
void * priqueue_peek     (priqueue_t *q);
void * priqueue_poll     (priqueue_t *q);
void * priqueue_at       (priqueue_t *q, int index);
int    priqueue_remove   (priqueue_t *q, void *ptr);
void * priqueue_remove_at(priqueue_t *q, int index);
int    priqueue_size     (priqueue_t *q);

void   priqueue_destroy  (priqueue_t *q);

#endif /* LIBPQUEUE_H_ */
