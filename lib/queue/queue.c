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
    if(queue == NULL){
        return;
    }

    QueueNode *newNode = malloc(sizeof(QueueNode));

    newNode->next = NULL;
    newNode->value = data;

    if(queue->head != NULL){
        queue->tail->next = newNode;
        queue->tail = newNode;
    } else{
        queue->head = newNode;
        queue->tail = newNode;
    }

    queue->size += 1;
}
void *queue_dequeue(Queue *queue){

    if(queue == NULL){
        return NULL;
    }

    if(queue->size == 0){
        printf("queue is empty.");
        return NULL;
    }

    QueueNode *head = queue->head;
    
    QueueNode *current = queue->tail;

    if(head != NULL){
        queue->head = head->next;

        void *data = head->value;

        free(head);

        queue->size -= 1;

        return data;
    }

    return NULL;

}
int queue_size(Queue *queue){

    return queue->size;

}