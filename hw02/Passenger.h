/* Passenger.h
 * 
 * Submitted by: Matthew Torres: 2/19/2021
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>
#include <string>

//passenger struct
struct Passenger
{

        int id, from, to;
        //default constructor
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }
        
        //overloaded constructor
        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        //print function
        void print(std::ostream &output);

};

#endif
