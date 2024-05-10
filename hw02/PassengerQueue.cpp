/* PassengerQueue.cpp
 * This is the implementation for the passenger queue, which stores passengers 
 * in a queue data structure with key functions to simulate the actions 
 * required by MetroSim, including enqueueing and dequeueing passengers, 
 * as well as printing their info in an organized manner.
*/
#include "PassengerQueue.h"

/* PassengerQueue Constructor
 * Creates the "under the hood" passenger vector
*/
PassengerQueue::PassengerQueue()
{
    passengerVector = new vector<Passenger>;
}

/* PassengerQueue Destructor
 * Deletes the "under the hood" passenger vector
*/
PassengerQueue::~PassengerQueue()
{
    
    delete passengerVector;
}

/* front()
 * Purpose: Returns, but does not remove, the front element of the Queue
 * Arguments: None
 * Returns: the first element of the Queue
*/
Passenger PassengerQueue::front()
{
    return passengerVector->front();
}

/* dequeue()
 * Purpose: Removes the first element of the queue
 * Arguments: None
 * Returns: Nothing, but alters the queue by shifting all elements upward.
*/
void PassengerQueue::dequeue()
{
    if(not empty())
    {
        passengerVector->erase(passengerVector->begin());
    }
    else
    {
        cerr << "Cannot Pop from an Empty List" <<endl;
    }
}

/* PassengerQueue Constructor
 * Purpose: Adds an element to the queue at the proper location, organized by 
 * "to" station and then "from" station
 * Arguments: The passenger to add to the queue
 * Returns: Nothing, but alters the array such that there is an additional 
 * element somewhere between [0, Size())
*/
void PassengerQueue::enqueue(const Passenger &newp)
{
    
    int i = size()-1;
    //if the queue is empty, add to the back of the queue
    if(passengerVector->empty())
    {
        passengerVector->push_back(newp);
    }
    //if the array isn't empty...
    else if(passengerVector->at(i).to > newp.to)
    {
        //Iterate backwards from end of queue until you find the desired "to" 
        //station
        while(passengerVector->at(i).to > newp.to and i > 0)
        {
            i--;
        }
        //Then iterate forward through the elements with the same "to"
        //station until you find a "from" station that is higher than the 
        //"from" station of the given element.
        while(passengerVector->at(i).from < newp.to and
        passengerVector->at(i).to == newp.to)
        {
            i++;
        }
        //insert the element at the proper location
        passengerVector->insert(passengerVector->begin()+i, newp);
    }
    //if the back of the queue is the proper location for the element, just 
    //push at back
    else
    {
        passengerVector->push_back(newp);
    }
}

/* size()
 * Purpose: returns the size of the queue
 * Arguments: none
 * Returns: an int for the size of the queue
*/
int PassengerQueue::size()
{
    return passengerVector->size();
}

/* Print()
 * Purpose: prints each of the elements of the passenger queue
 * Arguments: an output stream to print to
 * Returns: Nothing, but prints to the output stream.
*/
void PassengerQueue::print(ostream &output)
{
    for(int i=0; i<size(); i++)
    {
        passengerVector->at(i).print(output);
    }
}

/* empty()
 * Purpose: returns a bool that states whether the queue is empty
 * Arguments: none
 * Returns: a bool that states whether or not the queue is empty.
*/
bool PassengerQueue::empty()
{
    return passengerVector->empty();
}
