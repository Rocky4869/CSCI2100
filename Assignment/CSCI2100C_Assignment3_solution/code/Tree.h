//
// Created by muzhi on 4/4/2022.
//

#ifndef CSCI2100C_ASSIGNMENT3_TREE_H
#define CSCI2100C_ASSIGNMENT3_TREE_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TreeNode.h"
typedef struct TreeCDT *TreeADT;
TreeADT EmptyTree(void);
TreeADT NonemptyTree(TreeNodeADT, int, ...);
// The first argument is the root;
// The second argument is the number of children of the root;
// The other arguments are subtrees of type TreeADT.
TreeADT Subtree(int, TreeADT);
// Returns the nth subtree where n is given in the first argument. n = 1, 2, ...
int NumberOfSubtrees(TreeADT); // number of children of the root
bool TreeIsEmpty(TreeADT);
TreeNodeADT Root(TreeADT);

#endif //CSCI2100C_ASSIGNMENT3_TREE_H
