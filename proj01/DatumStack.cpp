/* DatumStack.cpp
 * This file is the implementation for DatumStack.cpp
 * Submitted by: Matthew Torres. 3/10/2021 
*/
#include "DatumStack.h"

// DatumStack default constructor
DatumStack::DatumStack()
{
    data=new vector<Datum>;
}

// DatumStack overloaded constructor: takes a datum array and int for size
DatumStack::DatumStack(Datum *dArray, int dSize)
{
    data=new vector<Datum>;
    for(int i=0; i<dSize; i++)
    {
        data->push_back(dArray[i]);
    }
}

// DatumStack destructor
DatumStack::~DatumStack()
{
    delete data;
}

/* isEmpty()
 * Purpose: returns a bool for whether the under-the-hood datum vector is empty
 * Arguments: none
 * Returns: bool that is true if the Datumstack is empty
*/
bool DatumStack::isEmpty()
{
    return data->empty();
}

/* clear()
 * Purpose: Clears all of the elements in the under-the-hood vector
 * Arguments: none
 * Returns: nothing, but empties the DatumStack
*/
void DatumStack::clear()
{
    data->clear();
}

/* size()
 * Purpose: returns an int for the size of the under-the-hood vector
 * Arguments: none
 * Returns: an int that represents the size of the DatumStack
*/
int DatumStack::size()
{
    return data->size();
}

/* top()
 * Purpose: returns the element at the back of the under-the-hood vector
 * Arguments: none
 * Returns: the top element of the DatumStack
*/
Datum DatumStack::top()
{
    if(isEmpty())
    {
        throw runtime_error("empty_stack");
    }
    else
    {
        return data->back();
    }
}

/* pop()
 * Purpose: removes the last element in the under-the-hood vector
 * Arguments: none
 * Returns: nothing, but alters the size of the DatumStack
*/
void DatumStack::pop()
{
    if(isEmpty())
    {
        throw runtime_error("empty_stack");
    }
    else
    {
        data->pop_back();
    }
}

/* push()
 * Purpose: adds an element to the back of the under-the-hood vector
 * Arguments: none
 * Returns: nothing, but increases the size of the array
*/
void DatumStack::push(Datum newD)
{
    data->push_back(newD);
}
