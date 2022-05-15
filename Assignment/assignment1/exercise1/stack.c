//
// Created by xinyun zhang on 15/1/2022.
//

#include <stdlib.h>
#include "stack.h"

typedef struct cellT{
    stackElementT value;
    struct cellT* above;
} cellT;

struct stackCDT {
    cellT *bottom;
    cellT *top;
};

stackADT EmptyStack(void){
    stackADT stack;
    stack = (stackADT)malloc(sizeof(*stack));
    stack->bottom=NULL;
    stack->top=NULL;
    return(stack);
}

void Push(stackADT stack, stackElementT element){
    cellT *cp;
    cp = (cellT*) malloc(sizeof(cellT));
    cp->value = element;
    cp->above = NULL;
    if(stack->top==NULL){
        stack->top = cp;
        stack->bottom = cp;
    }
    else{
        stack->top->above = cp;
        stack->top = cp;
    }
}

stackElementT Pop(stackADT stack){
    cellT *cp, *element;
    if(stack->top == stack->bottom){
        element = stack->top;
        stack->top = NULL;
        stack->bottom = NULL;
    }
    else{
        for(cp=stack->bottom; cp->above!=NULL; cp=cp->above){
            if(cp->above == stack->top){
                element = cp->above;
                cp->above = NULL;
                stack->top = cp;
                break;
            }
        }
    }
    return element->value;
}

int StackDepth(stackADT stack){
    int n=0;
    cellT* cp;
    for(cp=stack->bottom; cp!=NULL; cp=cp->above){
        n++;
    }
    return(n);
}
int StackIsEmpty(stackADT stack){
    return(stack->top == NULL);
}