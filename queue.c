#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    // If q is NULL, q->head leads to segmentation fault(dereferencing NULL
    // ptr).
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp;
        // printf("current size: %d\n", q_size(q));
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
        q->size -= 1;
    }
    free(q);
    return;
}
// void q_free(queue_t *q)
//{
//    /* TODO: How about freeing the list elements and the strings? */
//    /* Free queue structure */
//    list_ele_t *head = q->head;
//    while (head) {
//        list_ele_t *tmp;
//        tmp = head;
//        head = head->next;
//        free(tmp->value);
//        free(tmp);
//    }
//    free(q);
//}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* TODO: What should you do if the q is NULL? */
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    char *dest = malloc(strlen(s) + 1);
    if (!dest || !newh) {
        printf("Couldn't allocate space.");
        return false;
    }
    strlcpy(dest, s, strlen(s) + 1);
    newh->value = dest;
    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    if (q->size == 1)
        q->tail = newh;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Remember: It should operate in O(1) time */

    if (!q)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    char *dest = malloc(strlen(s) + 1);
    if (!dest || !newh) {
        printf("Couldn't allocate space.");
        return false;
    }
    strlcpy(dest, s, strlen(s) + 1);
    newh->value = dest;
    newh->next = NULL;

    if (q->tail) {
        // printf("q->tail isn't NULL!\n");
        q->tail->next = newh;
        q->tail = newh;
    } else
        q->tail = q->head = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;
    list_ele_t *tmp = q->head;
    q->head = q->head->next;

    // if sp is non-NULL
    strlcpy(sp, tmp->value, bufsize);
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    // Step1: First, assign the head node as the tail node.
    // Step2: At each step, assign this (would-be) tail node's next node to be
    // the head. Step3: Repeat Step2 until the tail becomes exactly the tail
    // node(next node is NULL).
    if (!q || !q->head)
        return;
    list_ele_t *tmp;
    q->tail = q->head;
    while (q->tail->next) {
        tmp = q->tail->next;
        q->tail->next = tmp->next;
        tmp->next = q->head;
        q->head = tmp;
    }
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
