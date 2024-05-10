/*
 * CharArrayList.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by Matthew Torres, 2/15/2021
 * 
 * Stores characters in a certain order. It imitates some functions of the
 * C++ string. 
 * 
 * Notes: this implementation uses a dynamic array. So, potential
 * drawbacks as compared to the CharLinkedList class include slower insertions
 * and removals at the front of the list. On the other hand, since only one
 * pointer variable is needed for the entire list (as opposed to one pointer
 * per element in the CharLinkedList), the CharArrayList class has the
 * advantage of more efficient memory usage over the CharLinkedList.
 */

#include "CharArrayList.h"

// for print
#include <iostream>

using namespace std;

/* Purpose: initializes an empty CharArrayList */
CharArrayList::CharArrayList()
{
    //initialize empty array
    len  = 0;
    cap  = 0;
    data = nullptr;
}

/*    Purpose: initializes a CharArrayList containing one character
 * Parameters: the character that should be stored in the new list
 */
CharArrayList::CharArrayList(char c)
{
    //initialize array
    len = 1;
    cap = 1;
    data = new char[cap];
    //insert char parameter to array
    data[0] = c;
}

/*    Purpose: initializes a CharArrayList containing all of the specified 
 *             characters, in the given order
 * Parameters: An array (in order) of characters to be stored in the list;
 *             the length of the given array (as an int)
 */
CharArrayList::CharArrayList(char *arr, int size)
{
    //initialize array
    len = size;
    cap = size;
    data = new char[cap];
    //copy data from array parameter
    for(int i = 0; i < size; i++)
    {
        data[i] = arr[i];
    }
}

/* Purpose: copy constructor -- creates a list with the same information as
 *          the one passed in
 * 
 *    Note: The array capacity may be different from the capacity of the list
 *          that is copied from. That is fine. What is important is that both
 *          lists will store the same information -- to the client, they will
 *          be the same.
 * 
 *    TODO: Currently does not work because pushAtBack and elementAt are 
 *          not implemented.
 */
CharArrayList::CharArrayList(const CharArrayList &other) 
{
    len = 0; // start with an empty list
    cap = 0;
    data = nullptr;

    // push each item from the other list onto this one
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(other.elementAt(i));
    }
}

/* Purpose: destructor -- frees all memory associated with the list */
CharArrayList::~CharArrayList()
{
    delete [] data;
}

/* Purpose: assignment operator -- makes the current list contain the same
 *          information as the one on the right hand side
 * 
 *    Note: The array capacity may be different from the list that is being
 *          copied from.
 * 
 *    TODO: Currently does not work because clear, pushAtBack and
 *          elementAt are not implemented.
 */
CharArrayList &CharArrayList::operator =(const CharArrayList &rhs) 
{
    if (this != &rhs) {
        clear(); // clear the current list
        
        // add each element from the other list into this one
        for (int i = 0; i < rhs.size(); i++) {
            pushAtBack(rhs.elementAt(i));
        }
    }
    return *this;
}

/* isEmpty
 *    Purpose: Check if the list is empty
 * Parameters: none
 *    Returns: a boolean -- true if the list is empty, false if it isn't
 * 
 *       Note: "empty" refers to if the client is currently storing any
 *             information in the list. The capacity of the ArrayList is
 *             irrelevant.
 */
bool CharArrayList::isEmpty() const 
{
    //return bool for size==0
    return size() == 0;
}

/* size
 *    Purpose: Get the number of characters being stored in the list
 * Parameters: none
 *    Returns: The number of characters currently stored in the list, as an
 *             int (but will never be negative)
 */
int CharArrayList::size() const 
{
    //return size of list
    return len;
}

/* first
 *    Purpose: Get the first element in the list.
 * Parameters: none
 *    Returns: The first element in the list, as a char.
 * 
 *       Note: Prints an error and exits if the list is empty.
 */
char CharArrayList::first() const 
{
    //if list is empty, send error message and exit program
    if(isEmpty())
    {
        cerr << "Cannot get the first element of an empty list"<<endl;
        exit(EXIT_FAILURE);
    }
    //return first element
    return data[0];
}

/* last
 *    Purpose: Get the last element in the list.
 * Parameters: none
 *    Returns: The last element in the list, as a char.
 * 
 *       Note: prints an error and exits if the list is empty.
 */
char CharArrayList::last() const 
{
    //if empty, send error message and exit program
    if(isEmpty())
    {
        cerr << "Cannot get the last element of an empty list"<< endl;
        exit(EXIT_FAILURE);
    }
    //return last element
    return data[len-1];
}

/* elementAt
 *    Purpose: Get the character at a given position.
 * Parameters: The index to be accessed, as an int. Should be in bounds; in 
 *             other words, should be in the range [0, size() )
 *    Returns: The element at the specified index, as a char
 */
char CharArrayList::elementAt(int idx) const
{
    //if arrayList is empty, send error message and exit
    if(isEmpty())
    {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    //return element at the given index
    return data[idx];
}

/* print
 *    Purpose: Prints the list to the terminal (cout)
 * Parameters: None
 *    Returns: None
 */
void CharArrayList::print() const
{
    cout << "[CharArrayList of size " << size() <<  " <<";

    for (int i = 0; i < size(); i++) {
            cout << elementAt(i);
    }

    cout << ">>]" << endl;
}

/* clear
 *    Purpose: Makes the list empty
 * Parameters: None
 *    Returns: None
 * 
 *       Note: Does not change the capacity of the array nor free any memory.
 */
void CharArrayList::clear() 
{
    //set length to 0
    len = 0;
}

/* pushAtBack
 *    Purpose: Adds a character to the back of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharArrayList::pushAtBack(char c)
{
    //if length exceeds capacity, double capacity
    if(len == cap)
    {
        data = increaseCap();
    }
    //insert element at the back.
    data[len] = c;
    //increase length
    len++;
}

/* pushAtFront
 *    Purpose: Adds a character to the front of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharArrayList::pushAtFront(char c)
{
    char to_shift;
    //if length exceeds capacity, double capacity.
    if(len == cap)
    {
        data = increaseCap();
    }
    //insert new element at the front of the array, and shift others backward
    for(int i = 0; i <= len; i++)
    {
        to_shift = data[i];
        data[i] = c;
        c = to_shift;
    }
    //increase length
    len++;
}

/* insertAt
 *    Purpose: Adds a character to the list at a given position
 * Parameters: The character to be added to the list and the position at which
 *             it should be added. The position should be in-bounds, that is,
 *             in the range [0, size()]. Providing size() as the index will
 *             insert the character at the back of the list.
 *    Returns: None
 */
void CharArrayList::insertAt(char c, int idx)
{
    char to_shift;
    //if length exceeds capacity, increase capacity
    if(len == cap)
    {
        data = increaseCap();
    }
    //insert new element and shift remaining elements backward
    for(int i = idx; i <= len; i++)
    {
        to_shift = data[i];
        data[i] = c;
        c = to_shift;
    }
    //increase the length
    len++;
}

/* popFromFront
 *    Purpose: Removes the first element from the list
 * Parameters: None
 *    Returns: None
 *
 *       Note: Prints an error message and quits if the list is empty
 */
void CharArrayList::popFromFront()
{
    // confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    removeAt(0);
}

/* popFromBack
 *    Purpose: Removes the last element from the list
 * Parameters: None
 *    Returns: None
 * 
 *       Note: Prints an error message and exits if the list is empty
 */
void CharArrayList::popFromBack()
{
    // confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    removeAt(size() - 1);
}


/* removeAt
 *    Purpose: Removes the element at a given index
 * Parameters: The position at which to remove an element, which should be the
 *             index of an element currently in the list; in other words,
 *             should be in the interval [0, size)
 *    Returns: None
 * 
 *       Note: If the amount of space in the array that is in use drops to less 
 *             than one fourth, the array should be shrunk to half its size.
 */
void CharArrayList::removeAt(int idx)
{
    // confirm index is in range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    // remove the element by shifting all subsequent elements to the left
    for (int i = idx; i < size() - 1; i++) {
        data[i] = data[i + 1];
    }
    // update the length
    len--;

    if(cap > len*2)
    {
        data=decreaseCap();
    }
}

/* replaceAt
 *    Purpose: Replaces the element at the given index with the given value
 * Parameters: A character to put in the list and the index of the
 *             element to replace. The index should be in-bounds, in the
 *             range [0, size() )
 * 
 *       Note: Prints an error message and exits if the index is out of bounds
 */
void CharArrayList::replaceAt(char c, int idx)
{
    if (isEmpty()) 
    {
        cerr << "Cannot replace in an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    data[idx] = c;
}
/* concatenate
 *    Purpose: Adds the contents of a CharArrayList to the back of the current 
 *             one.
 * Parameters: A CharArrayList whose contents should be pushed to the back of
 *             the current list. Will not be altered
 *    Returns: None
 */
void CharArrayList::concatenate(const CharArrayList &other)
{
    for(int i = len; i < (len + other.size()); i++)
    {
        if(len == cap)
        {
            data = increaseCap();
        }
        data[i] = other.elementAt(i);
    }
}

/*
 * increaseCap
 *    Purpose: A helper function that doubles the capacity of the arrayList 
 *             when an element is added beyond the curent capacity.
 * Parameters: None
 *    Returns: A char array that is a copy of the previous array just with a
 *             larger capacity.
*/
char *CharArrayList::increaseCap()
{
    //Double capacity
    cap *= 2;
    //create new array with doubled capacity
    char *newData = new char[cap];
    //copy data from old array
    for(int i = 0; i < len; i++)
    {
        newData[i] = data[i];
    }
    //delete old array and return new array
    delete [] data;
    return newData;
}

/*
 * decreaseCap
 *    Purpose: A helper function that halves the capacity of the arrayList 
 *             when an element is removed resulting in the size of the array 
 *             being less than or equal to half the capacity.
 * Parameters: None
 *    Returns: A char array that is a copy of the previous array just with a
 *             smaller capacity.
*/
char* CharArrayList::decreaseCap()
{
    //half capacity
    cap = cap/2;
    //create new array with half capacity
    char *newData = new char[cap];
    //copy data from old array to new array
    for(int i = 0; i < len; i++)
    {
        newData[i] = data[i];
    }
    //delete old array and return new array
    delete [] data;
    return newData;
}
