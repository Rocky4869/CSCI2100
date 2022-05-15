//
// Created by xinyun zhang on 2/2/2022.
//

#ifndef EXERCISE3_BUSTERMINUS_H
#define EXERCISE3_BUSTERMINUS_H
#include "stack.h"
#include "queue.h"


void simulator(char* departureAPath, char* departureBPath, char* departureCPath,
               char* fareAPath, char* fareBPath, char* fareCPath,
               char* passengerArrivalPath);

typedef struct displayBoard{
    int departureTime;
    int busFare;
} displayBoard;

displayBoard* EmptyDisplayBoard(void);

typedef struct busStop {
    stackADT departureTime;
    stackADT busFare;
    queueADT passengerQ;
} busStop;

busStop* EmptyBusStop(void);

#endif //EXERCISE3_BUSTERMINUS_H;