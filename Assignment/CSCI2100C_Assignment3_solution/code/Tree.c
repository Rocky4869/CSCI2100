//
// Created by muzhi on 4/4/2022.
//

#include "Tree.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"
#include "TreeNode.h"
struct TreeCDT {
    TreeNodeADT rt;
    int nrSubtrees;
    TreeADT subtree[100];
// The maximum number of subtrees is 99.
// If nrSubtrees = 𝑘, then only subtree[1] to subtree[𝑘] are used.
// subtree[0] is never used.
};

TreeADT EmptyTree(void) {
    TreeADT t = (TreeADT) malloc(sizeof(struct TreeCDT));
    t->rt = NULL;
    t->nrSubtrees = 0;
}

TreeADT NonemptyTree(TreeNodeADT root, int number, ...) {
    va_list args;
    TreeADT t = (TreeADT) malloc(sizeof(*t));
    t->rt = root;
    t->nrSubtrees = number;
    if (number==0) return t;
    va_start(args, number);
    for (int i=0; i < number; i++){
        t->subtree[i+1] = va_arg(args, TreeADT);
    }
    va_end(args); // va_end is used
    return t;
}


TreeADT Subtree(int n, TreeADT t) {
    if (n >= 100) exit(EXIT_FAILURE);
    return t->subtree[n];
}

// Returns the nth subtree where n is given in the first argument. n = 1, 2, ...
int NumberOfSubtrees(TreeADT t) {
    if (TreeIsEmpty(t)) exit(EXIT_FAILURE);
    return t->nrSubtrees;
}

bool TreeIsEmpty(TreeADT t) {
    if (t == NULL) return true;
    if (t->rt == NULL) return true;
    return false;
}

TreeNodeADT Root(TreeADT t) {
    if (t == NULL) exit(EXIT_FAILURE);
    return t->rt;
}