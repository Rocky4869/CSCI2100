//
// Created by muzhi on 4/4/2022.
//

#ifndef CSCI2100C_ASSIGNMENT3_TREENODE_H
#define CSCI2100C_ASSIGNMENT3_TREENODE_H

#include <stdlib.h>
typedef struct TreeNodeCDT *TreeNodeADT;
typedef char NodeContentT; // For simplicity, we only store one character in a node.
TreeNodeADT NewNode(NodeContentT);
NodeContentT GetNodeContent(TreeNodeADT);

#endif //CSCI2100C_ASSIGNMENT3_TREENODE_H
