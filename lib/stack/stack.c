#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Stack *stack_create(){

    Stack *stack = malloc(sizeof(Stack));

    if(stack != NULL){
        stack->head = NULL;
        stack->size = 0;
        stack->maxSize = 2147483647;
    }

    return stack;

}
int stack_size(Stack *stack){

    return stack->size;

}
void stack_push(Stack *stack, void *data){

    if(stack->size + 1 > stack->maxSize){
        printf("Stack overflow :(");
        return;
    }

    StackNode *newNode = malloc(sizeof(StackNode));
    if(newNode->value != NULL){
        memcpy(newNode->value, data, sizeof(*data));
    }
    newNode->next = NULL;
    newNode->value = data;

    if(stack->size == 0){
        stack->head = newNode;
    }
    else{
        newNode->next = stack->head;
        stack->head = newNode;
    }

    stack->size += 1;

}
void *stack_pop(Stack *stack){

    if(stack->size == 0){
        printf("stack is empty.");
        return NULL;
    }

    StackNode * head = stack->head;
    stack->head = stack->head->next;
    stack->size -= 1;

    void* value = head->value;
    free(head);

    return value;

}
void stack_destroy(Stack *stack){
    int size = stack->size;

    if(stack != NULL){
        for(int i = 0; i < size; i++){
            stack_pop(stack);
        }
        free(stack);
    }

}