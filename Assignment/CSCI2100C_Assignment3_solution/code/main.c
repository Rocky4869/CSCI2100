#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "queue.h"

#define MAXNUMBER 101

char *BFS(TreeADT T){
    // initialize the result array.
    char *result = (char*)malloc(100*sizeof(char));
    // enqueue the whole tree to an empty queueADT of tree.
    queueADT Q = EmptyQueue();
    Enqueue(Q, T);
    /* For each tree node, enqueue all its subtrees in a queueADT of tree.
    Then dequeue a tree from the queue, and enqueue all its subtrees to the same queue.
    Repeat these steps. */
    int index = 0;
    while (!QueueIsEmpty(Q)) {
        TreeADT newT = Dequeue(Q);
        result[index++] = GetNodeContent(Root(newT));
        int treeNumber = NumberOfSubtrees(newT);
        for (int i = 1; i <= treeNumber; i++)
            Enqueue(Q, Subtree(i, newT));
    }
    result[index] = '\0';
    return result;
}

int *Tree2Array(TreeADT T){
    // initialize the result array.
    int *result = (int*)malloc(101*sizeof(int));
    // enqueue the whole tree to an empty queueADT of tree.
    queueADT Q = EmptyQueue();
    Enqueue(Q, T);
    /* For each tree node, enqueue all its subtrees in a queueADT of tree.
    Then dequeue a tree from the queue, and enqueue all its subtrees to the same queue.
    Repeat these steps. */
    int index = 1, nodeRoot = 0;
    // initialize the first element to 0, which indicates nothing.
    result[0] = 0;
    while (!QueueIsEmpty(Q)) {
        TreeADT newT = Dequeue(Q);
        int treeNumber = NumberOfSubtrees(newT);
        for (int i = 1; i <= treeNumber; i++) {
            Enqueue(Q, Subtree(i, newT));
            result[index++] = nodeRoot;
        }
        nodeRoot++;
    }
    return result;
}


int main() {
    TreeADT ta, tb, tc, td, te;
    TreeNodeADT a = NewNode('A');
    TreeNodeADT b = NewNode('B');
    TreeNodeADT c = NewNode('C');
    TreeNodeADT d = NewNode('D');
    TreeNodeADT e = NewNode('E');


    te = NonemptyTree(e, 0);
    td = NonemptyTree(d, 1, te);
    tc = NonemptyTree(c, 1, td);
    tb = NonemptyTree(b, 1, tc);
    ta = NonemptyTree(a, 1, tb);

    char* arr1 = BFS(ta);
    for (int i = 0; i < 5; i++) {
        printf("%c ", arr1[i]);
    }
    printf("\n");

    int* arr2 = Tree2Array(ta);
    for (int i = 1; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    return 0;
}
