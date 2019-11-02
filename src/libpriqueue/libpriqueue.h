/** @file libpriqueue.h
 */

#ifndef LIBPRIQUEUE_H_
#define LIBPRIQUEUE_H_

typedef struct _list_node
{
  struct _list_node *next;
  struct _list_node *prev;
  void* val;
} list_node;

void node_init(list_node *n, void* v);

/**
  Priqueue Data Structure
*/
typedef struct _priqueue_t
{
<<<<<<< Updated upstream
  list_node* head;
  list_node* tail;
=======
  list_node *front;
  list_node *back;
>>>>>>> Stashed changes
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
