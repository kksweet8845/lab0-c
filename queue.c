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
    else {
        q->head = NULL;
        q->tail = NULL;
        q->len = 0;
    }
    return q;
}

list_ele_t *list_new(char *s)
{
    list_ele_t *l = malloc(sizeof(list_ele_t));
    if (l == NULL)
        return NULL;
    char *ts = malloc((strlen(s) + 1) * (sizeof(char)));
    if (ts == NULL) {
        free(l);
        return NULL;
    }
    strcpy(ts, s);
    l->value = ts;
    l->next = NULL;
    return l;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return;
    list_ele_t *cur, *temp;
    for (cur = q->head; cur != NULL; cur = temp) {
        temp = cur->next;
        if (cur->value != NULL)
            free(cur->value);
        if (cur != NULL)
            free(cur);
    }
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
    list_ele_t *newh;
    /* Return false if q is NULL or could not allocate space */
    if (q == NULL)
        return false;
    /* Handling allocate space for the string and copy it */
    newh = list_new(s);
    if (newh == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->len += 1;
    if (q->len == 1)
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
    list_ele_t *newh;
    /*  Rturn false if q is NULL*/
    if (q == NULL)
        return false;
    /*  Create a new list */
    newh = list_new(s);
    /* Return false if the list is NULL */
    if (newh == NULL)
        return false;
    q->tail->next = newh;
    q->tail = newh;
    q->len += 1;
    if (q->len == 1)
        q->head = newh;
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
    if (q == NULL || (q->head == NULL && q->tail == NULL) || q->len == 0 ||
        sp == NULL)
        return false;
    list_ele_t *cur = q->head;
    q->head = q->head->next;
    q->len -= 1;
    /* Tips: fill all the char with `\0` teminator */
    memset(sp, '\0', (bufsize) * sizeof(char));
    /* copy the first bufsize-1, then sp will already have the \0 teminator */
    strncpy(sp, cur->value, bufsize - 1);
    if (cur->value != NULL)
        free(cur->value);
    if (cur != NULL)
        free(cur);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    return q->len;
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
    if (q == NULL)
        return;
    list_ele_t *cur, *pre, *tmp_head = NULL;
    q->tail = q->head;
    for (cur = q->head; cur != NULL; cur = q->head) {
        pre = tmp_head;
        tmp_head = cur;
        q->head = cur->next;
        cur->next = pre;
    }
    q->head = tmp_head;
}
