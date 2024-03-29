#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    void *value;
    int index;
    struct listNode *next;

} ListNode;

typedef struct list
{
    ListNode *debut;
    ListNode *head;
    int size;
} List;

List *list_create();
int list_size(List *list);
void *list_get(List *list, int index);
int list_contains(List *list, void *data);
void list_append(List *list, void *data);
void list_insert(List *list, int index, void *data);
int list_indexOf(List *list, void *data);
void list_delete(List *list, int index);
void list_destroy(List *list);
void head_delete(List *list); // private
void tail_delete(List *list); // private


#endif
