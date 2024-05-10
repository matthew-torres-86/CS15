/*
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MetroSim
{
public:
    //constructor and deconstructor
    MetroSim(vector<string> *st);
    ~MetroSim();
    
    //public member functions run and prompt
    void run(ostream &output, istream &input);
    void prompt(ostream &output, istream &input);
private:
    //station struct
    struct station{
        string name;
        vector<Passenger> *passengers;
        PassengerQueue *boardedPassengers;
    };
    
    //stations vector to store station structs
    vector<station*> stations;
    
    //important incrementor variables
    int train_location;
    int largestID;
    
    //private member functions
    void addPassenger(istream &input);
    void moveMetro(ostream &output);
    void print();
};

#endif
