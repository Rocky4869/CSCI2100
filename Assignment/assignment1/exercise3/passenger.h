//
// Created by xinyun zhang on 2/2/2022.
//

#ifndef EXERCISE3_PASSENGER_H
#define EXERCISE3_PASSENGER_H
typedef struct Passenger {
    int PassengerClass; /* 0: child; 1: adult; 2: senior citizen */
    int routeAOK;
    int routeBOK;
    int routeCOK;
    int timeEnqueued;
} Passenger;

typedef Passenger *PassengerADT;
#endif //EXERCISE3_PASSENGER_H
