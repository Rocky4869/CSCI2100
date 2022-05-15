//
// Created by xinyun zhang on 15/1/2022.
//

#include <stdlib.h>
#include "stack.h"

struct stackCDT {stackElementT elements[100]; int count;};

stackADT EmptyStack(void){
    stackADT stack;
    stack = (stackADT)malloc(sizeof(*stack));
    stack->count=0;
    return(stack);
}

void Push(stackADT stack, stackElementT element){
    stack->elements[(stack->count)++]=element;
}
stackElementT Pop(stackADT stack){
    return(stack->elements[--(stack->count)]);
}
int StackDepth(stackADT stack){
    return(stack->count);
}
int StackIsEmpty(stackADT stack){
    return(stack->count == 0);
}