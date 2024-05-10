/* Passenger.cpp
 * This is the implementation of the passenger class, which literally just 
 * contains a function to print the passenger's info.
 * Submitted By: Matthew Torres. 3/2/21
 */

#include "Passenger.h"

/* print() 
 * Purpose:This function prints the information contained in each instance of 
 * a passenger struct in the required format.
 * Arguments: takes an output stream to which it prints.
 * Returns: Nothing, but prints to the given output stream.
 */
void Passenger::print(std::ostream &output)
{
    output << "[" << id << ", " << from << "->" << to <<"]";
}
