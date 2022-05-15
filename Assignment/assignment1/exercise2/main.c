#include <stdio.h>
#include "stack.h"

//void DisplayStack(stackADT stack){
//    int len = StackDepth(stack);
//    stackADT helperStack = EmptyStack();
//    printf("Display start: \n");
//    for(int i=0; i < len; i++){
//        stackElementT element = Pop(stack);
//        printf("%d\n", element);
//        Push(helperStack, element);
//    }
//    for(int i=0; i < len; i++)
//        Push(stack, Pop(helperStack));
//    printf("End of display\n");
//}

int main() {
    stackADT stack = EmptyStack();
//    printf("stack is empty: %d\n", StackIsEmpty(stack));
//    DisplayStack(stack);
//    printf("----------%d -------\n", StackDepth(stack));
    Push(stack, 3);
    printf("stack is empty: %d\n", StackIsEmpty(stack));
//    DisplayStack(stack);
//    printf("-----------%d--------\n", StackDepth(stack));
    Push(stack, 5);
    Push(stack, 7);
//    DisplayStack(stack);
//    printf("----------%d--------\n", StackDepth(stack));
    int i = Pop(stack);
//    printf("Pop out %d\n", i);
//    DisplayStack(stack);
    i = Pop(stack);
//    printf("-----------%d------------\n", StackDepth(stack));
//    DisplayStack(stack);
    i = Pop(stack);
//    printf("-----------%d------------\n", StackDepth(stack));
//    DisplayStack(stack);
    Push(stack, 2);
    Push(stack, 4);
//    DisplayStack(stack);
    return 0;
}
