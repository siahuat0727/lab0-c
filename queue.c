/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

    /* How about freeing the list elements and the strings? */
    while (q->size)
        q_remove_head(q, NULL, 0);

    /* Free queue structure */
    free(q);
}

list_ele_t *ele_create(char *s)
{
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return NULL;

    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc(strlen(s) + 1);

    /* What if either call to malloc returns NULL? */
    if (newh->value == NULL) {
        free(newh);
        return NULL;
    }

    strcpy(newh->value, s);
    newh->next = NULL;

    return newh;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;

    /* Create list element */
    list_ele_t *newh = ele_create(s);
    if (newh == NULL)
        return false;

    /* Insert element and update queue structure*/
    newh->next = q->head;
    q->head = newh;
    if (q->size++ == 0)
        q->tail = newh;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return false;

    /* Create list element */
    list_ele_t *newh = ele_create(s);
    if (newh == NULL)
        return false;

    /* Insert element and update queue structure*/
    if (q->size++)
        q->tail->next = newh;
    else
        q->head = newh;
    q->tail = newh;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->size == 0)
        return false;

    /* Copy removed string */
    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    /* Remove element and update queue structure */
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    if (--(q->size) == 0)
        q->tail = NULL;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->size == 0)
        return;

    q->tail = q->head;
    while (q->tail->next) {
        list_ele_t *e = q->tail->next;
        q->tail->next = e->next;
        e->next = q->head;
        q->head = e;
    }
}
