
/* SYSC 2006 Winter 2019 Lab 10
 *
 * circular_queue.c - circular linked-list implementation of a queue.
 */

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "circular_queue.h"

/* Return a pointer to a new, empty queue.
 * Terminate (via assert) if memory for the queue cannot be allocated.
 */
queue_t *queue_construct(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    assert(queue != NULL);

    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

/* Return true if the specified queue contains no elements;
 * otherwise return false.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */ 
_Bool queue_is_empty(const queue_t *queue)
{
    assert(queue != NULL);
    return queue->size == 0;
}

/* Return the number of elements stored in the specified queue.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
int queue_size(const queue_t *queue)
{
    assert(queue != NULL);
    return queue->size;
}

/* Print the contents of the specified queue to the console, 
 * from front to rear: [value0, value1, value3, ...]
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
void queue_print(const queue_t *queue)
{
    assert(queue!= NULL);

    if (queue_is_empty(queue)) {  // Handle an empty queue (no nodes).
        printf("[]");
    }

    node_t *current;

    printf("[");

    /* Print all the elements in the queue, except for the one at the rear. */
    for (current = queue->rear->next;  // queue->rear points to the tail node
                                       // (the node at the rear of the queue).
                                       // The tail node points to the head node
                                       // (the node at the front of the queue).
         current != queue->rear; 
         current = current -> next) {
        printf("%d, ", current->data);
    }

    /* Now print the element at the rear of the queue. */
    printf("%d]", current->data);
}

/*--------------------------------------------------------
 *
 * Solutions to Lab 10 exercises.
 */

/* Enqueue the specified value to the rear of a queue.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
void enqueue(queue_t *queue, int value)
{
	assert(queue!=NULL);
    if(queue->size==0){
        node_t *last_node = malloc(sizeof(node_t));
        last_node->data = value;
        queue->size++;
        queue->rear=last_node;
        queue->rear->next = queue->rear;
    }else{
            node_t *node_next = malloc(sizeof(node_t));
            node_next->data = value;
            node_next->next = queue->rear->next;
            queue->rear->next = node_next;
            queue->rear = node_next;
            queue->size++;
        }
}

/* Copy the value at the front of a queue to the variable pointed to by
 * parameter element, and return true.
 * Return false if the queue is empty.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
_Bool front(const queue_t *queue, int *element)
{
    assert(queue!=NULL);
    if(queue->size==0){
      return false;
    }else{
      *element = queue->rear->next->data;
      return true;
    }
}

/* Copy the value at the front of a queue to the variable pointed to by
 * parameter element, remove that value from the queue, and return true.
 * Return false if the queue is empty.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
_Bool dequeue(queue_t *queue, int *element)
{
    assert(queue!=NULL);
    if(queue->size == 0){
      return false;
    }else if(queue->size == 1){
      *element = queue->rear->data;
      free(queue->rear);
      queue->size--;
      return true;
    }else{
      *element = queue->rear->next->data;
      node_t *node_free = queue->rear->next;
      queue->rear->next = node_free->next;
      free(node_free);
      queue->size--;
      return true;
    }
}
