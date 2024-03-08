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
    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode->value != NULL) {
        memcpy(newNode->value, data, sizeof(*data));
    }
    newNode->value = data;
    newNode->next = NULL;
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
    
}
void *list_get(List *list, int index){

    if (list == NULL || list->head == NULL || index < 0 || index > list->head->index) {
        printf("Index out of bounds or list is empty\n");
        return NULL;
    }
    ListNode *current  = list->debut;
    while(current->index != index){
        current = current->next;

        if (current == NULL) {
            printf("Index out of bounds\n");
            return NULL;
        }
    }

    return current->value;

}

// int main(void){
//     List* list = list_create();
//     list_append(list, (void*)1);
//     // list_append(list, (void*)2);
//     // list_append(list, (void*)3);
//     printf("%d\n", (int)list_get(list, 0) == 1);
// }
