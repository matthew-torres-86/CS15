/* PassengerQueue_tests.cpp
 * This is the test file used to ensure that functions in PassengerQueue.cpp 
 * are working properly 
 * Submitted By: Matthew Torres. 3/2/21
*/
#include <iostream>
#include <cassert>
#include "MetroSim.h"
#include "PassengerQueue.h"
#include "Passenger.h"

/* Passenger Constructor test
 * Creates a new passnger instance to ensure that valgrind passes and 
 * there are no runtime errors with the default constructor
 */
void passenger_constructor()
{
    Passenger *pete = new Passenger();
    assert(pete->id == -1);
    delete pete;
}

/* Passenger Constructor 2 test
 * Creates a new Passenger instance to ensure that valgrind passes, 
 * there are no runtime errors with the overloaded constructor and that data is 
 * stored properly
 */
void passenger_constructor_2()
{
    Passenger *pete = new Passenger(1, 2, 4);
    assert(pete->id == 1);
    delete pete;
}

/* Passenger Queue Constructor test
 * Creates a new passengerQueue instance to ensure that valgrind passes and 
 * there are no runtime errors
 */
void Passenger_Queue_constructor()
{
    PassengerQueue *list = new PassengerQueue();
    delete list;
}

/* Passenger queue enqueue test
 * runs the enqueue function on a passneger queue then ensures that data is 
 * added to queue properly
 */
void Passenger_Queue_enqueue()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 2, 4);
    list->enqueue(*pete);
    delete list;
    delete pete;
}

/* Passenger queue front test
 * Creates a new passenger queue, enqueues a passenger, then ensures that the
 * passengerQueue front() function works properly using information about said
 * passenger
 */
void Passenger_Queue_front()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 2, 4);
    list->enqueue(*pete);
    assert(list->front().id == 1);
    delete list;
    delete pete;
}

/* Enqueue unusual test
 * Ensures that passengers can be sorted properly in the PassengerQueue even 
 * when they are not inserted in numerical order.
 */
void Passenger_Queue_enqueue_unusual_dest()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 7, 14);
    Passenger *paul = new Passenger(2, 8, 12);
    list->enqueue(*pete);
    list->enqueue(*paul);
    assert(list->front().id == 2);
    delete list;
    delete pete;
    delete paul;
}

/* Enqueue many and size test
 * enqueues many passengers to the queue then checks to see if the size() 
 * function returns 
 */
void Passenger_Queue_enqueue_many_with_size()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 1, 12);
    Passenger *paul = new Passenger(2, 1, 14);
    Passenger *pricilla = new Passenger(3, 2, 12);
    Passenger *pedro = new Passenger (4, 1, 26);
    list->enqueue(*pricilla);
    list->enqueue(*pedro);
    list->enqueue(*pete);
    list->enqueue(*paul);
    assert(list->size() == 4 && list->front().id==3);
    delete list;
    delete pete;
    delete paul;
    delete pricilla;
    delete pedro;
}

void Passenger_Queue_enqueue_identical()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 1, 12);
    Passenger *paul = new Passenger(2, 1, 12);
    list->enqueue(*pete);
    list->enqueue(*paul);
    assert(list->front().id==1);
    delete list;
    delete pete;
    delete paul;
}

void Passenger_Queue_dequeue()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 1, 12);
    Passenger *paul = new Passenger(2, 1, 12);
    list->enqueue(*pete);
    list->enqueue(*paul);
    
    list->dequeue();
    assert(list->front().id==2);
    delete list;
    delete pete;
    delete paul;
}

void Passenger_Queue_dequeue_empty()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 1, 12);
    Passenger *paul = new Passenger(2, 1, 12);
    list->enqueue(*pete);
    list->enqueue(*paul);
    
    list->dequeue();
    list->dequeue();
    assert(list->empty());
    delete list;
    delete pete;
    delete paul;
}

void Passenger_Queue_dequeue_beyond_empty()
{
    PassengerQueue *list = new PassengerQueue();
    Passenger *pete = new Passenger(1, 1, 12);
    Passenger *paul = new Passenger(2, 1, 12);
    list->enqueue(*pete);
    list->enqueue(*paul);
    
    list->dequeue();
    list->dequeue();
    list->dequeue();

    delete list;
    delete pete;
    delete paul;
}


