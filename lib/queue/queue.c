#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

Queue *queue_create(){

    Queue *queue = malloc(sizeof(Queue));

    if(queue != NULL){
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }

    return queue;

}
void queue_destroy(Queue *queue){

    int size = queue->size;

    if(queue != NULL){
        for(int i = 0; i < size; i++){
            queue_dequeue(queue);
        }
        free(queue);
    }

}
void queue_enqueue(Queue *queue, void *data){

    QueueNode *newNode = malloc(sizeof(QueueNode));
    if(newNode->value != NULL){
        memcpy(newNode->value, data, sizeof(*data));
    }
    newNode->next = NULL;
    newNode->value = data;

    newNode->next = queue->tail;
    queue->tail = newNode;
    
    if(queue->size == 0){
        queue->head = newNode;
    }

    queue->size += 1;

}
void *queue_dequeue(Queue *queue){

    if(queue->size == 0){
        printf("queue is empty.");
        return NULL;
    }

    QueueNode * head = queue->head;
    
    QueueNode * current = queue->tail;

    for(int i = 0; i < queue->size - 2; i++){
        current = current->next;
    }

    queue->head = current;

    queue->size -= 1;

    void* value = head->value;
    free(head);

    return value;

}
int queue_size(Queue *queue){

    return queue->size;

}