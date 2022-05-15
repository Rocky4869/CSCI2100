//
// Created by xinyun zhang on 15/1/2022.
//

#ifndef FIRSTCPROG_STACK_H
#define FIRSTCPROG_STACK_H

typedef struct stackCDT *stackADT;
typedef int stackElementT;
stackADT EmptyStack(void);
void Push(stackADT stack, stackElementT element);
stackElementT Pop(stackADT stack);
int StackDepth(stackADT stack);
int StackIsEmpty(stackADT stack);

#endif //FIRSTCPROG_STACK_H
