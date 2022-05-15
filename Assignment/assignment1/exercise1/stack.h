//
// Created by xinyun zhang on 2/2/2022.
//

#ifndef EXERCISE1_STACK_H
#define EXERCISE1_STACK_H

typedef struct stackCDT *stackADT;
typedef int stackElementT;
stackADT EmptyStack(void);
void Push(stackADT stack, stackElementT element);
stackElementT Pop(stackADT stack);
int StackDepth(stackADT stack);
int StackIsEmpty(stackADT stack);
#endif //EXERCISE1_STACK_H
