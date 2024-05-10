/* 
 * CharLinkedList.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by Matthew Torres, 2/15/2021
 * 
 * Stores characters in a certain order. It imitates some functions of the
 * C++ string. 
 * 
 * NOTE: This is implemented using a doubly-linked list. It is not circular
 *       and does not have a "back" pointer.
 */

#include "CharLinkedList.h"

// for the print function
#include <iostream>

using namespace std;

/* Purpose: initializes an empty CharLinkedList */
CharLinkedList::CharLinkedList()
{
    //initialize empty front node
    firstNode = new Node;
    firstNode -> data = '\0';
    firstNode -> next = nullptr;
    firstNode -> prev = nullptr;
}

/*    Purpose: initializes a CharLinkedList containing one character
 * Parameters: the character that should be stored in the new list
 */
CharLinkedList::CharLinkedList(char c)
{
    //initialize nodes
    firstNode = new Node;
    Node *newNode = new Node;
    //setup front node
    firstNode->data = '\0';
    firstNode->next = newNode;
    firstNode->prev = nullptr;
    //setup second node using char parameter
    newNode->data = c;
    newNode->next = nullptr;
    newNode->prev = firstNode;
}

/*    Purpose: initializes a CharLinkedList containing all of the specified 
 *             characters, in the given order
 * Parameters: An array (in order) of characters to be stored in the list;
 *             the length of the given array (as an int)
 */
CharLinkedList::CharLinkedList(char *arr, int size)
{
    //initialize node
    firstNode = new Node;
    firstNode->data = '\0';
    firstNode->next = nullptr;
    firstNode->prev = nullptr;
    //copy data from array parameter to linkedList
    for(int i=0; i<size; i++)
    {
        pushAtBack(arr[i]);
    }
    
}

/* Purpose: copy constructor -- creates a list with the same information as
 *          the one passed in
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other) 
{
    //initialize node
    firstNode = new Node;
    firstNode->data = '\0';
    firstNode->next = nullptr;
    firstNode->prev = nullptr;
    //copy data from CharLinkedList Parameter to new CharLinkedList
    for(int i = 0; i < other.size(); i++)
    {
        pushAtBack(other.elementAt(i));
    }
}

/* Purpose: destructor -- frees all memory associated with the list */
CharLinkedList::~CharLinkedList()
{
    Node *curr;
    curr = firstNode;
    //Iterates to the back of the list
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    //deletes elements one by one from the back of the list to the front
    while(curr->prev !=nullptr)
    {
        curr = curr->prev;
        delete curr->next; 
    }
    //deletes the front node
    delete curr;
}

/* Purpose: assignment operator -- makes the current list contain the same
 *          information as the one on the right hand side
 */
CharLinkedList &CharLinkedList::operator =(const CharLinkedList &rhs) 
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
 */
bool CharLinkedList::isEmpty() const 
{
    //If no nodes follow empty front node, list is empty
    return firstNode->next == nullptr;
}

/* size
 *    Purpose: Get the number of characters being stored in the list
 * Parameters: none
 *    Returns: The number of characters currently stored in the list, as an
 *             int (will never be negative)
 */
int CharLinkedList::size() const 
{
    int result = 0;
    Node* curr = firstNode;
    //count nodes in the list as it iterates through
    while(curr->next != nullptr)
    {
        result++;
        curr = curr->next;
    }
    //return count
    return result;
}

/* first
 *    Purpose: Get the first element in the list.
 * Parameters: none
 *    Returns: The first element in the list, as a char.
 * 
 *       Note: Prints an error message and exits if the list is empty.
 */
char CharLinkedList::first() const 
{
    //if empty, send error message and exit program
    if(isEmpty())
    {
        cerr << "Cannot get the first element of an empty list";
        exit(EXIT_FAILURE);
    }
    //return data from first data-filled node
    return firstNode->next->data;
}

/* last
 *    Purpose: Get the last element in the list.
 * Parameters: none
 *    Returns: The last element in the list, as a char.
 * 
 *       Note: Prints an error message and exits if the list is empty.
 */
char CharLinkedList::last() const 
{
    Node *curr = firstNode;
    //if empty, send error message and exit program
    if(isEmpty())
    {
        cerr << "Cannot get the last element of an empty list";
        exit(EXIT_FAILURE);
    }
    //iterate to back of list
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    //return last element
    return curr->data;
}

/* elementAt
 *    Purpose: Get the character at a given position.
 * Parameters: The index to be accessed, as an int. Should be in bounds; in 
 *             other words, should be in the range [0, size() )
 *    Returns: The element at the specified index, as a char
 */
char CharLinkedList::elementAt(int idx) const
{
    Node *curr;
    curr = firstNode->next;
    //iterate to element at the given index
    for(int i = 0; i < idx; i++)
    {
        //if out of bounds, send error message and exit program
        if(curr->next == nullptr)
        {
            cerr << "Index " << idx << " not in range [0.." << size() << "]"
                 <<endl;
            exit(EXIT_FAILURE);
        }
        curr = curr->next;
    }
    //return data at given index
    return curr -> data;
}

/* print
 *    Purpose: Prints the list to the terminal (cout)
 * Parameters: None
 *    Returns: None
 */
void CharLinkedList::print() const
{
    //print start
    cout << "[CharLinkedList of size " << size() <<  " <<";
    //print each element
    for (int i = 0; i < size(); i++) {
            cout << elementAt(i);
    }
    //print end
    cout << ">>]" << endl;
}

/* clear
 *    Purpose: Makes the list empty
 * Parameters: None
 *    Returns: None
 */
void CharLinkedList::clear() 
{
    Node *curr;
    curr = firstNode;
    //advance to back of list
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    //delete each element from back of list to front
    while(curr->prev !=firstNode)
    {
        curr = curr->prev;
        delete curr->next; 
    }
    //do not delete first node
    if(curr != firstNode)
    {
        delete curr;
    }
}

/* pushAtBack
 *    Purpose: Adds a character to the back of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharLinkedList::pushAtBack(char c)
{
    Node *curr;
    curr = firstNode;
    //advance to back of list
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    //initialize new node with data from parameter and appropriate pointers
    Node *newNode = new Node;
    newNode->data = c;
    curr->next = newNode;
    newNode->prev = curr;
    newNode->next = nullptr;
}

/* pushAtFront
 *    Purpose: Adds a character to the front of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharLinkedList::pushAtFront(char c)
{
    //initialize new node with data from parameter and appropriate pointers
    Node *newNode = new Node;
    newNode->next = firstNode->next;
    newNode->prev = firstNode;
    newNode->data = c;
    newNode->next->prev = newNode;
    firstNode->next = newNode;
}

/* insertAt
 *    Purpose: Adds a character to the list at a given position
 * Parameters: The character to be added to the list and the position at which
 *             it should be added. The position should be in-bounds, that is,
 *             in the range [0, size()]. Providing size() as the index will
 *             insert the character at the back of the list.
 *    Returns: None
 */
void CharLinkedList::insertAt(char c, int idx)
{
    Node *curr=firstNode;
    //advance to given index
    for(int i=0; i <= idx; i++)
    {
        //ensure index is in bounds of the list
        if(curr == nullptr)
        {
            cerr << "Index " << idx << " not in range [0.." << size() << "]"
            << endl;
            exit(EXIT_FAILURE);
        }
        curr = curr->next;
    }
    //if index points to the back of the list, push at back
    if(curr == nullptr)
    {
        pushAtBack(c);
    }
    //if not, insert element manually at the given index
    else
    {
        //Initialize new node with appropriate pointers and data from parameter
        Node *newNode=new Node;
        newNode->data = c;
        newNode->prev = curr->prev;
        newNode->prev->next = newNode;
        newNode->next = curr;
        newNode->next->prev = newNode;
    }
}

/* popFromFront
 *    Purpose: Removes the first element from the list
 * Parameters: None
 *    Returns: None
 *       Note: Prints an error message and exits if the list is empty
 */
void CharLinkedList::popFromFront()
{
    //confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    //remove element at the front
    removeAt(0);
}

/* popFromBack
 *    Purpose: Removes the last element from the list
 * Parameters: None
 *    Returns: None
 *       Note: Prints an error message and exits if the list is empty
 */
void CharLinkedList::popFromBack()
{
    //confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    //remove element at the back
    removeAt(size()-1);
}

/* removeAt
 *    Purpose: Removes the element at a given index
 * Parameters: The position at which to remove an element, which should be the
 *             index of an element currently in the list; in other words,
 *             should be in the interval [0, size)
 *    Returns: None
 */
void CharLinkedList::removeAt(int idx)
{
    Node *curr=firstNode;
    //ensure index is in range
    if(idx >= size())
    {
        cerr << "Index " << idx << " not in range [0.." << size() << "]"
        << endl;
        exit(EXIT_FAILURE);
    }
    //advance to given index
    for(int i=0; i <= idx; i++)
    {
        curr = curr->next;
    }
    //re-assign pointer values of surrounding nodes to "sew together" the hole
    curr->prev->next = curr->next;
    if(curr->next != nullptr)
    {
        curr->next->prev =curr->prev;
    }
    //delete the node at given index
    delete curr;
}

/* replaceAt
 *    Purpose: Replaces the element at the given index with the given value
 * Parameters: A character to put in the list and the index of the
 *             element to replace. The index should be in-bounds, in the
 *             range [0, size() )
 *       Note: Prints an error message and exits if the index is out of bounds
 */
void CharLinkedList::replaceAt(char c, int idx)
{
    Node *curr=firstNode;
    //ensure index is in range
    if(idx >= size())
    {
        cerr << "Index " << idx << " not in range [0.." << size() << "]"
        << endl;
        exit(EXIT_FAILURE);
    }
    //advance to given index
    for(int i=0; i <= idx; i++)
    {
        curr = curr->next;
    }
    //replace data of node at given index with char parameter
    curr->data = c;
}

/* concatenate
 *    Purpose: Adds the contents of a CharLinkedList to the back of the current 
 *             one.
 * Parameters: A CharLinkedList whose contents should be pushed to the back of 
 *             the current list. Will not be altered
 *    Returns: None
 */
void CharLinkedList::concatenate(const CharLinkedList &other)
{
    //add each of the elements of the parameter linkedlist to the back of the 
    //current linkedlist
    for(int i = 0; i < other.size(); i++)
    {
        this->pushAtBack(other.elementAt(i));
    }
}

