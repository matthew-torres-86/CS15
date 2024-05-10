/* DatumStack.h
 * This file is the interface for DatumStack.cpp
 * Submitted by: Matthew Torres. 3/10/2021 
*/
#ifndef DATUM_STACK_H
#define DATUM_STACK_H

#include "Datum.h"
#include <vector>
#include <stdexcept>

using namespace std;
class DatumStack{
    public:
        //consrcutors and deconstructor
        DatumStack();
        DatumStack(Datum* dArray, int dSize);
        ~DatumStack();
        
        //interface as defined in spec
        bool isEmpty();
        void clear();
        int size();
        Datum top();
        void pop();
        void push(Datum newD);
    private:
        //under the hood vector
        vector<Datum> *data;
};
#endif