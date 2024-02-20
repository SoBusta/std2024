#include <stdio.h>

#include "acutest.h"
#include "./../lib/stack/stack.h"

void size_and_push(){
    Stack* stack = stack_create();
    
    TEST_ASSERT_(stack_size(stack) == 0, "Stack size should be 0");
    stack_push(stack, (void*) 1);
    TEST_ASSERT_(stack_size(stack) == 1, "Stack size should be 1");
    stack_push(stack, (void*) 2);
    TEST_ASSERT_(stack_size(stack) == 2, "Stack size should be 2");
    stack_push(stack, (void*) 3);
    TEST_ASSERT_(stack_size(stack) == 3, "Stack size should be 3");
}

void pop(){
    Stack* stack = stack_create();
    
    stack_push(stack, (void*) 1);
    stack_push(stack, (void*) 2);
    stack_push(stack, (void*) 3);
    
    TEST_ASSERT_(stack_pop(stack) == (void*) 3, "Stack pop should return 3");
    TEST_ASSERT_(stack_size(stack) == 2, "Stack size should be 2");
    TEST_ASSERT_(stack_pop(stack) == (void*) 2, "Stack pop should return 2");
    TEST_ASSERT_(stack_size(stack) == 1, "Stack size should be 1");
    TEST_ASSERT_(stack_pop(stack) == (void*) 1, "Stack pop should return 1");
    TEST_ASSERT_(stack_size(stack) == 0, "Stack size should be 0");
    TEST_ASSERT_(stack_pop(stack) == NULL, "Stack pop should return NULL");
    TEST_ASSERT_(stack_size(stack) == 0, "Stack size should be 0");
}


TEST_LIST = {
    { "size_and_push", size_and_push },
    { "pop", pop },
    { NULL, NULL }
};
