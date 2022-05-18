//
// Created by muzhi on 4/4/2022.
//

#ifndef CSCI2100C_ASSIGNMENT3_QUEUE_H
#define CSCI2100C_ASSIGNMENT3_QUEUE_H

#include "Tree.h"

typedef struct queueCDT *queueADT;
typedef TreeADT queueElementT;

queueADT EmptyQueue(void);
void Enqueue(queueADT, queueElementT);
queueElementT Dequeue(queueADT);
int QueueLength(queueADT);
int QueueIsEmpty(queueADT);

#endif //CSCI2100C_ASSIGNMENT3_QUEUE_H
