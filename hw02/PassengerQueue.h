/* PassengerQueue.h
 * This is the interface for the passenger queue, which contains important 
 * implementation details to do with the passenger queue data structures.
*/

#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include "Passenger.h"
#include <vector>
using namespace std;

class PassengerQueue{
    public:
        //constructor and deconstructor
        PassengerQueue();
        ~PassengerQueue();
        
        //public member functions used in MetroSim and 
        //PassengerQueue classes
        Passenger front();
        void dequeue();
        void enqueue(const Passenger &newp);
        int size();
        void print(ostream &output);
        bool empty();

    private:
        //Private "under the hood" vector
        vector<Passenger> *passengerVector;
};
#endif