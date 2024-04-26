#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

List *list_create(){
    List *list = malloc(sizeof(List));

    if (list != NULL) {
        list->head = NULL; // Initially, the list is empty
        list->debut = NULL;
    }

    return list;
}

void list_append(List *list, void *data){

    if(list == NULL){
        return;
    }
    // Creating the node to append
    ListNode *newNode = malloc(sizeof(ListNode));
    if(newNode == NULL){
        return;
    }

    newNode->value = data;
    newNode->next = NULL;

    // Add to the list
    if(list->head == NULL){
        newNode->index = 0;
        list->head = newNode;
        list->debut = newNode;
    }
    else{
        newNode->index = list->head->index + 1;
        list->head->next = newNode;
        list->head = newNode;
    }

    list->size += 1;
        
    
}
void *list_get(List *list, int index){

    if (list == NULL || list->head == NULL ) {
        printf("Index out of bounds or list is empty\n");
        return NULL;
    }
    if(index < 0 || index > list->head->index){
        printf("Index out of bounds\n");
        return NULL;
    }

    ListNode *current = list->debut;

    while(current->index < index && current->next != NULL){
        current = current->next;
    }

    // Returns the node's value of the given index
    return current->value;

}

int list_size(List *list){
    return list->size;
}

// Inserts node before the given index
void list_insert(List *list, int index, void *data){

    if(list == NULL){
        return;
    }
    // Creating the node to insert
    ListNode *newNode = malloc(sizeof(ListNode));
    if(newNode == NULL){
        return;
    }

    newNode->value = data;
    newNode->next = NULL;
    newNode->index = index;

    ListNode *current = list->debut;

    if(index == 0){
        newNode->next = list->debut;
        list->debut = newNode;
        current = list->debut;
    }
    
    else{

        // Traverse the list to the node of preceding index
        while(current->index != index - 1){
            current = current->next;
        }

        newNode->next = current->next;
        current->next = NULL;
        current->next = newNode;

        current = current->next;
    }

    list->size += 1;

    // Updates the indices
    for(int i = index + 1; i < list_size(list); i++){
        current = current->next;
        current->index += 1;
    }
    
}

int list_indexOf(List *list, void *data){

    ListNode *current = list->debut;

    while(current->value != data){
        current = current->next;

        // The node hasn't been found
        if(current == NULL){
            return -1;
        }
    }

    return current->index;
}

void list_delete(List *list, int index){
    

    if (list == NULL || index >= list->size || index < 0){
        return;
    }
    if(index == list->size - 1){
        head_delete(list);
    }
    else if(index == 0){
        tail_delete(list);
    }
    else{

        ListNode *current = list->debut;

        // Traverse the list until the node preceding index
        while(current->index < index - 1){
            current = current->next;
        }

        ListNode *toDelete = current->next;
        current->next = current->next->next;
        current = toDelete->next;
        toDelete->next = NULL;
        free(toDelete);

        // Shifts the indices after the deleted node
        while(current->next != NULL){
            current->index -= 1;
            current = current->next;
        }
        list->head->index -= 1;

        list->size -= 1;
    }
}

// private
void tail_delete(List *list){

    list->size -= 1;

    ListNode *tail = list->debut;
    list->debut = list->debut->next; // Shifts debut pointer to next node
    tail->next = NULL; // deletes link between the former tail and current tail

    tail = NULL;
    free(tail);

    ListNode *current = list->debut;
    // Traverse the list and shifts the indices
    while(current->index - 1 < list->size && current->next != NULL){
        current->index -= 1;
        current = current->next;
    }
    list->head->index -= 1;

    current = NULL;
    free(current);

}

// private
void head_delete(List *list){

    list->size -= 1;

    if(list->size == 0){
        free(list->head);
        return;
    }

    ListNode *current = list->debut;

    // Traverse the list until the second to last node
    while(current->index < list->size - 2){
        current = current->next;
    }

    list->head = NULL;
    list->head = current;
    free(current->next);
    current->next = NULL;
    
}

int list_contains(List *list, void *data){

    ListNode *current = list->debut;

    while(current != NULL){

        if(current->value == data){
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void list_destroy(List *list) {
    if(list == NULL) {
        return;
    }

    for (ListNode *node = list->debut; node != NULL;) {
        ListNode *tmp = node->next;

        free(node);

        node = tmp;
    }

    free(list);
}