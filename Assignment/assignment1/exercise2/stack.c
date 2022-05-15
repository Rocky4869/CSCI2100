//
// Created by xinyun zhang on 15/1/2022.
//

#include <stdlib.h>
#include "stack.h"

typedef struct cellT{
    stackElementT value;
    struct cellT* below;
} cellT;

struct stackCDT {
    cellT *top;
};
stackADT EmptyStack(void){
    stackADT stack;
    stack = (stackADT)malloc(sizeof(*stack));
    stack->top=NULL;
    return(stack);
}

void Push(stackADT stack, stackElementT element){
    cellT *cp;
    cp = (cellT*) malloc(sizeof(cellT));
    cp->value = element;
    cp->below=NULL;
    if(stack->top==NULL){
        stack->top = cp;
    }
    else{
        cp->below = stack->top;
        stack->top = cp;
    }
}

stackElementT Pop(stackADT stack){
    cellT *cp;
    cp = stack->top;
    stack->top = cp->below;
    cp->below = NULL;
    return cp->value;
}

int StackDepth(stackADT stack){
    int n=0;
    cellT* cp;
    for(cp=stack->top; cp!=NULL; cp=cp->below){
        n++;
    }
    return(n);
}
int StackIsEmpty(stackADT stack){
    return(stack->top == NULL);
}