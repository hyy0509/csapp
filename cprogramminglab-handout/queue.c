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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    } else {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) return;
    list_ele_t *head = q->head;
    list_ele_t *next;
    while (head != NULL) {
        next = head->next;
        head->next = NULL;
        free(head);
        head = next;
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    q->head = NULL;
    q->tail = NULL;
    free(q);
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
    if (q == NULL) return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* What should you do if the q is NULL? */
    if (newh == NULL) return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    // @todo calloc, malloc, free
    newh->value = (char *) calloc(strlen(s) + 1, sizeof *s);
    strcpy(newh->value, s);
    newh->next = q->head;
    q->head = newh;
    q->size++;
    if (q->tail == NULL) {
        q->tail = newh;
    }
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
    if (q == NULL) return false;
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) return false;
    newt->value = (char *) calloc(strlen(s) + 1, sizeof *s);
    strcpy(newt->value, s);
    newt->next = NULL;
    if (q->tail == NULL) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size++;
    return true;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
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
    if (q == NULL || q->tail == NULL) return false;
    /* You need to fix up this code. */
    list_ele_t *ohead = q->head;
    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    q->head = q->head->next;
    q->size--;
    if (q->size == 0) {
        q->tail = NULL;
    }
    ohead->next = NULL;
    free(ohead);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->tail == NULL) {
        return 0;
    } else {
        return q->size;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
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
    if (q == NULL || q->size <= 1) {
        return;
    }
    // list_ele_t *oldh = q->head;
    // list_ele_t *oldt = q->tail;
    list_ele_t *before = NULL;
    list_ele_t *cur = q->head;
    list_ele_t *next;
    while (cur != NULL) {
        next = cur->next;
        cur->next = before;
        before = cur;
        cur = next;
    }
    // q->head = oldt;
    // q->tail = oldh;
    list_ele_t *oldt = q->tail;
    q->tail = q->head;
    q->head = oldt;
    /* You need to write the code for this function */
}

