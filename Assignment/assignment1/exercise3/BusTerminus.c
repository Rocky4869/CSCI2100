//
// Created by xinyun zhang on 2/2/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "queue.h"
#include "stack.h"
#include "BusTerminus.h"

//void testqueue(queueADT queue){
//    int len = QueueLength(queue);
//    for(int i=0; i < len; i++){
//        queueElement passenger = Dequeue(queue);
//        printf("passenger %d, time: %d, type: %d, A-OK: %d, B-Ok: %d, C-OK: %d\n", i+1, passenger->timeEnqueued, passenger->PassengerClass, passenger->routeAOK, passenger->routeBOK, passenger->routeCOK);
//        Enqueue(queue, passenger);
//    }
//}
//void teststack(stackADT stack){
//    int len = StackDepth(stack);
//
//    stackADT helperStack = EmptyStack();
//    printf("********test stack************\n");
//    for(int i=0; i < len; i++){
//        stackElementT  element = Pop(stack);
//        printf("%d\n", element);
//        Push(helperStack, element);
//    }
//    printf("********end test stack************\n");
//    for(int i=0; i < len; i++)
//        Push(stack, Pop(helperStack));
//}



void LoadSingleValue(char* path, stackADT stack){
    stackADT helperStack = EmptyStack();
    FILE *fp = fopen(path, "r");
    if(!fp){
        printf("Fail to open the file!!!");
        exit(0);
    }
    char line[100];
    int n = 0;
    while(fgets(line, sizeof(line), fp)!=NULL){
        line[strcspn(line, "\r\n")]='\0';
        if(strlen(line) == 0)
            continue;
        int element = atoi(line);
        Push(helperStack, element);
        n++;
    }
    fclose(fp);
    int len = StackDepth(helperStack);
    for(int i=0; i < len; i++){
        stackElementT element = Pop(helperStack);
        Push(stack, element);
    }
}

void LoadBusInformation(char* departPath, char* farePath, busStop* stop){
    stackADT departureTime = stop->departureTime;
    stackADT busFare = stop->busFare;
    LoadSingleValue(farePath, busFare);
    LoadSingleValue(departPath, departureTime);
}

void InitBusStop(busStop* stop){
    stop->passengerQ = EmptyQueue();
    stop->busFare = EmptyStack();
    stop->departureTime = EmptyStack();
}

void InitDisplayBoard(displayBoard* board){
   board->busFare = 0;
   board->departureTime = -1;
}

void LoadPassengerArrival(char* passengerArrivalPath, queueADT queue){
    FILE *fp = fopen(passengerArrivalPath, "r");
    if(!fp){
        printf("Fail to open the file!!!");
        exit(0);
    }
    char line[100];
    int n = 0;
    while(fgets(line, sizeof(line), fp)!=NULL){
            line[strcspn(line, "\r\n")]='\0';
            if(strlen(line) == 0)
                continue;
            PassengerADT passenger = (PassengerADT) malloc(sizeof (Passenger));
            passenger->PassengerClass=-1;
            passenger->routeAOK=0;
            passenger->routeBOK=0;
            passenger->routeCOK=0;
            passenger->timeEnqueued=0;
            char *token = strtok(line, " ");
            int cnt = 0;
            while(token != NULL){
                // printf("the token is %s\n", token);
                if(cnt == 0){
                    int time = atoi(token);
                    passenger->timeEnqueued = time;
                }
                if(cnt == 1){
                    int passengerType = atoi(token);
                    passenger->PassengerClass = passengerType;
                }
                if(cnt > 1){
                    if(strcmp("A", token) == 0)
                        passenger->routeAOK = 1;
                    if(strcmp("B", token) == 0)
                        passenger->routeBOK = 1;
                    if(strcmp("C", token) == 0)
                        passenger->routeCOK = 1;
                }
                token = strtok(NULL, " ");
                cnt++;
            }
            n++;
            Enqueue(queue, passenger);
    }
    fclose(fp);
}

//void LoadPassengerArrival(char* passengerArrivalPath, queueADT queue){
//    FILE *fp = fopen(passengerArrivalPath, "r");
//    if(!fp){
//        printf("Fail to open the file!!!");
//        exit(0);
//    }
//    char line[100];
//    int n = 0;
//    while(fgets(line, sizeof(line), fp)!=NULL){
//        line[strcspn(line, "\r\n")]='\0';
//        if(strlen(line) == 0)
//            continue;
//        char *token = strtok(line, " ");
//        while(token != NULL){
//            printf("the token is %s\n", token);
//            token = strtok(NULL, " ");
//        }
//    }
//    fclose(fp);
//
//}

void UpdataDisplayBoard(displayBoard* board, busStop* stop, int currrentTime){
    // check whether the last bus has left or not
    if(currrentTime > board->departureTime){
        int len = StackDepth(stop->departureTime);
        if(len > 0){
            board->departureTime = Pop(stop->departureTime);
            board->busFare = Pop(stop->busFare);
        }
        else{
            // no future bus
            board->departureTime = -1;
            board->busFare = 0;
        }
    }
}

queueElement QueueFront(queueADT queue){
    // assert non-empty queue
    int len = QueueLength(queue);
    queueElement element = Dequeue(queue);
    Enqueue(queue, element);
    for(int i=0; i < len-1; i++){
        Enqueue(queue, Dequeue(queue));
    }
    return element;
}

int CompareTwoRoutes(int const *queueLen, int const *fare, int const *select, int i, int j){
    // both i and j are not selected
    if(select[i] == 0 && select[j] == 0)
        return -1;
    // only j is selected
    if(select[i] == 0)
        return j;
    // only i is selected
    if(select[j] == 0)
        return i;
    // both i and j can be selected
    // 1. compare queue length
    if(queueLen[i] > queueLen[j])
        return j;
    if(queueLen[i] < queueLen[j])
        return i;
    // 2. compare fares
    if(fare[i] < fare[j])
        return i;
    if(fare[i] > fare[j])
        return j;
    // 3. alphabetic order
    if(i < j)
        return i;
    return j;

}

void ComputeFares(int *fare, int type){
    // adult
    if(type == 1)
        return;
    // child and senior
    for(int i=0; i<3; i++){
        fare[i] = fare[i] / 2;
        if(type == 2 && fare[i] > 2)
            fare[i] = 2;
    }
}

void simulator(char* departureAPath, char* departureBPath, char* departureCPath,
               char* fareAPath, char* fareBPath, char* fareCPath,
               char* passengerArrivalPath){


    // initialization
    int cntA = 0, cntB = 0, cntC = 0;
    int fareA = 0, fareB = 0, fareC = 0;
    int timeA = 0, timeB = 0, timeC = 0;
    busStop busStopA, busStopB, busStopC;
    InitBusStop(&busStopA);
    InitBusStop(&busStopB);
    InitBusStop(&busStopC);
    displayBoard displayBoardA, displayBoardB, displayBoardC;
    InitDisplayBoard(&displayBoardA);
    InitDisplayBoard(&displayBoardB);
    InitDisplayBoard(&displayBoardC);

    // load data from the txt file for the bus stop
    LoadBusInformation(departureAPath, fareAPath, &busStopA);
    LoadBusInformation(departureBPath, fareBPath, &busStopB);
    LoadBusInformation(departureCPath, fareCPath, &busStopC);
    // load data from the txt file for the passenger information
    queueADT passengerQueue = EmptyQueue();
    LoadPassengerArrival(passengerArrivalPath, passengerQueue);

//    teststack(busStopA.departureTime);
//    teststack(busStopA.busFare);
//    teststack(busStopB.departureTime);
//    teststack(busStopB.busFare);
//    teststack(busStopC.departureTime);
//    teststack(busStopC.busFare);

    // printf("queue length: %d\n", QueueLength(passengerQueue));
    // testqueue(passengerQueue);

    // simulate every minutes
    for(int time=0; time<1439; time++){
        // update the display board
        UpdataDisplayBoard(&displayBoardA, &busStopA, time);
        UpdataDisplayBoard(&displayBoardB, &busStopB, time);
        UpdataDisplayBoard(&displayBoardC, &busStopC, time);
        while(QueueLength(passengerQueue) > 0){
            PassengerADT passenger = QueueFront(passengerQueue);
            if(passenger->timeEnqueued > time)
                break;
            passenger = Dequeue(passengerQueue);
            int queueLen[3] = {displayBoardA.departureTime > 0?QueueLength(busStopA.passengerQ):INT_MAX,
                               displayBoardB.departureTime > 0?QueueLength(busStopB.passengerQ):INT_MAX,
                               displayBoardC.departureTime > 0?QueueLength(busStopC.passengerQ):INT_MAX};
            // printf("The queue lengths A: %d, B: %d, C: %d\n", queueLen[0], queueLen[1], queueLen[2]);
            int fare[3] = {displayBoardA.busFare, displayBoardB.busFare, displayBoardC.busFare};
            int routeSelect[3] = {0, 0, 0};
            if(passenger->routeAOK)
                routeSelect[0] = 1;
            if(passenger->routeBOK)
                routeSelect[1] = 1;
            if(passenger->routeCOK)
                routeSelect[2] = 1;
            int passengerType = passenger->PassengerClass;
            ComputeFares(fare, passengerType);
            // compare route b and c
            int index = CompareTwoRoutes(queueLen, fare, routeSelect, 1, 2);
            // compare route a with (route b or c)
            if(index != -1)
                index = CompareTwoRoutes(queueLen, fare, routeSelect, 0, index);
            else
                index = 0;
            queueADT selectedQueue;
            int *cnt, *totalFare, *totalTime;
            int timeToDepart;
            switch (index) {
                case 0:
                    selectedQueue = busStopA.passengerQ;
                    cnt = &cntA;
                    totalFare = &fareA;
                    totalTime = &timeA;
                    timeToDepart = displayBoardA.departureTime;
                    break;
                case 1:
                    selectedQueue = busStopB.passengerQ;
                    cnt = &cntB;
                    totalFare = &fareB;
                    totalTime = &timeB;
                    timeToDepart = displayBoardB.departureTime;
                    break;
                case 2:
                    selectedQueue = busStopC.passengerQ;
                    cnt = &cntC;
                    totalFare = &fareC;
                    totalTime = &timeC;
                    timeToDepart = displayBoardC.departureTime;
                    break;
                default:
                    printf("Bus route selection error!");
                    exit(0);
            }
            Enqueue(selectedQueue, passenger);
            // check whether there are buses
            if(timeToDepart > 0) {
                (*totalTime) += timeToDepart - passenger->timeEnqueued;
                (*cnt)++;
                (*totalFare) += fare[index];
            }
        }
        // clean the bus stop
        if(displayBoardA.departureTime == time)
            busStopA.passengerQ = EmptyQueue();
        if(displayBoardB.departureTime == time)
            busStopB.passengerQ = EmptyQueue();
        if(displayBoardC.departureTime == time)
            busStopC.passengerQ = EmptyQueue();
    }
    printf("The total number of passengers for route A: %d\n", cntA);
    printf("The total number of passengers for route B: %d\n", cntB);
    printf("The total number of passengers for route C: %d\n", cntC);
    printf("The total number of bus fare received for route A: %d\n", fareA);
    printf("The total number of bus fare received for route B: %d\n", fareB);
    printf("The total number of bus fare received for route C: %d\n", fareC);
    printf("The average waiting time for route A: %f\n", (double)((double)timeA / (cntA)));
    printf("The average waiting time for route B: %f\n", (double)((double)timeB / (cntB)));
    printf("The average waiting time for route C: %f\n", (double)((double)timeC / (cntC)));
}
