//
// Created by xinyun zhang on 2/2/2022.
//

#ifndef EXERCISE3_QUEUE_H
#define EXERCISE3_QUEUE_H

#include "passenger.h"

typedef struct queueCDT *queueADT;
typedef PassengerADT queueElement;
queueADT EmptyQueue(void);
void Enqueue(queueADT queue, queueElement element);
queueElement Dequeue(queueADT queue);
int QueueLength(queueADT queue);
int QueueIsEmpty(queueADT queue);

#endif //EXERCISE3_QUEUE_H
