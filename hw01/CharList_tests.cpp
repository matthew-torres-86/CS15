/* 
 * CharList_tests.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * Edited by Matthew Torres 2/5/2021
 * 
 * Uses Matt Russell's unit_test framework to test the CharArrayList and
 * CharLinkedList.
 * More information on this testing framework can be found at: (link to more 
 * information unit_test)
 */
#include <iostream>
#include <cassert>
#include "CharArrayList.h"
#include "CharLinkedList.h"

using namespace std;
/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* default constructor test
 * Run the ArrayList default constructor to make sure there are no runtime
 * errors or memory leaks
 */
void default_constructor_AL()
{
    CharArrayList testArrayList;
}

/* secondary constructor test
 * Run the ArrayList secondary constructor to make sure there are no runtime
 * errors or memory leaks, as well as ensure that the data parameter is 
 * properly stored in the list by asserting the first element is 'j'
 */
void secondary_constructor_AL()
{
    CharArrayList testArrayList('j');
    assert(testArrayList.elementAt(0)=='j');
}

/* third constructor test
 * Run the ArrayList third constructor to make sure there are no runtime
 * errors or memory leaks as well as ensure that the data in the array is 
 * properly stored in the ArrayList by asserting the third element is 'j'
 */
void third_constructor_AL()
{
    char *testing= new char[5]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    testing[4] = 'k';
    CharArrayList testArrayList(testing, 5);
    assert(testArrayList.elementAt(3)=='j');
    delete [] testing;
}

/* copy constructor and push back test
 * Run the secondary constructor, pushAtBack() method, and copy constructor 
 * together to ensure that pushAtBack() properly adds an element to the 
 * arrayList and that the copy constructor successfully copies an ArrayList 
 */
void copy_constructor_and_push_back_AL()
{
    CharArrayList *original = new CharArrayList('a'); 
    original->pushAtBack('b');
    CharArrayList *copy = new CharArrayList(*original);
    assert(copy->elementAt(1)=='b');
    delete original;
    delete copy;
}

/* is empty test
 * Run the default constructor and then ensure that the ArrayList is empty 
 * using the isEmpty() method
 */
void is_empty_AL()
{
    CharArrayList *testing = new CharArrayList(); 
    assert(testing->isEmpty());
    delete testing;
}

/* size test
 * Run the third constructor to create an arrayList using an array of size 5, 
 * then use the size method to ensure that the ArrayList created also has a 
 * size of 5
 */
void size_AL()
{
    char *testing= new char[5]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    testing[4] = 'k';
    CharArrayList testArrayList(testing, 5);
    assert(testArrayList.size()==5);
    delete [] testing;
}

/* first, last and element at test
 *  Run the third constructor to create an arrayList using an array of size 5, 
 * then use the first(), last() and elementAt() methods based on knowledge of 
 * the placement of the items in the arrayList to ensure that they work properly
 */
void first_last_elementAt_AL()
{
    char *testing= new char[5]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    testing[4] = 'k';
    CharArrayList testArrayList(testing, 5);
    assert(testArrayList.first()=='g' 
    and testArrayList.last()=='k' 
    and testArrayList.elementAt(2)=='i');
    delete [] testing;
}

/* push at front test
 *  Run the secondary constructor to create an ArrayList. Then run the 
 * pushAtFront() function. Finally, assert that the first element is the one 
 * that was inserted into the front and the back element is the one that was 
 * pushed backward to ensure that the pushAtFront function works properly.  
 */
void push_at_front_AL()
{
    CharArrayList *testing = new CharArrayList('a'); 
    testing->pushAtFront('b');
    assert(testing->first()=='b' and testing->last()=='a');
    delete testing;
}

/* insert at test
 *  Run the third constructor to create an ArrayList from an array. Then run 
 * the insertAt() function to insert an element to the ArrayList at a specified 
 * index. Then assert that the element at the specified index is truly the 
 * element that you inserted, and that the last element had been pushed 
 * backward properly  
 */
void insert_at_AL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'i';
    testing[2] = 'j';
    testing[3] = 'k';
    CharArrayList *testArrayList = new CharArrayList(testing, 4);
    testArrayList->insertAt('h', 1);
    testArrayList->insertAt('l', 5);
    assert(testArrayList->elementAt(1)=='h' 
    and testArrayList->elementAt(4)=='k');
    delete [] testing;
    delete testArrayList;
}

/* remove at test
 *  Run the third constructor to create an ArrayList from an array. Then run 
 * the removeAt() function to remove multiple elements from the arrayList.
 * Then assert that the element at the back had been shifted forward properly.
 */
void remove_at_AL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    CharArrayList *testArrayList = new CharArrayList(testing, 4);
    testArrayList->removeAt(0);
    testArrayList->removeAt(0);
    testArrayList->removeAt(0);
    assert(testArrayList->first()=='j');
    delete [] testing;
    delete testArrayList;
}

/* replace at test
 *  Run the third constructor to create an ArrayList from an array. Then run 
 * the replaceeAt() function to replace an element in the array. Then assert 
 * that the element at the specified index had been properly replaced.
 */
void replace_at_AL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'w';
    testing[3] = 'j';
    CharArrayList *testArrayList = new CharArrayList(testing, 4);
    testArrayList->replaceAt('i', 2);
    assert(testArrayList->elementAt(2)=='i');
    delete [] testing;
    delete testArrayList;
}

/*
 * error messages tests
 * creates an empty ArrayList and intentionally causes error messages because 
 * of array boundaries
 *NOTE: Commented out sections will cause test failure, by design
*/
void error_messages_AL()
{
    CharArrayList *testArrayList = new CharArrayList();
    // testArrayList->removeAt(5);
    // testArrayList->insertAt('c', 5);
    // testArrayList->replaceAt('c', 5);
    // testArrayList->popFromFront();
    // testArrayList->popFromBack();
    delete testArrayList;
}
/*******************************************************************\
*                      CHAR LINKED LIST TESTS                       *
\*******************************************************************/

/* default constructor test
 * Run the LinkedList default constructor to make sure there are no runtime
 * errors or memory leaks
 */
void default_constructor_LL()
{
    CharLinkedList testLinkedList;
}

/* secondary constructor test
 * Run the LinkedList secondary constructor to make sure there are no runtime
 * errors or memory leaks, as well as ensure that the data parameter is 
 * properly stored in the list by asserting the first element is 'j'
 */
void secondary_constructor_LL()
{
    CharLinkedList testLinkedList('j');
    assert(testLinkedList.elementAt(0)=='j');
}

/* third constructor test
 * Run the LinkedList third constructor to make sure there are no runtime
 * errors or memory leaks as well as ensure that the data in the array is 
 * properly stored in the LinkedList by asserting the third element is 'j'
 */
void tertiary_constructor_LL()
{
    char *testing= new char[5]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    testing[4] = 'k';
    CharLinkedList testLinkedList(testing, 5);
    assert(testLinkedList.elementAt(3)=='j');
    delete [] testing;
}

/* copy constructor and push back test
 * Run the secondary constructor, pushAtBack() method, and copy constructor 
 * together to ensure that pushAtBack() properly adds an element to the 
 * LinkedList and that the copy constructor successfully copies a LinkedList 
 */
void copy_constructor_and_push_back_LL()
{
    CharLinkedList *original = new CharLinkedList('a'); 
    original->pushAtBack('b');
    CharLinkedList *copy = new CharLinkedList(*original);
    assert(copy->elementAt(1)=='b');
    delete original;
    delete copy;
}

/* is empty test
 * Run the default constructor and then ensure that the LinkedList is empty 
 * using the isEmpty() method
 */
void is_empty_LL()
{
    CharLinkedList *testing = new CharLinkedList(); 
    assert(testing->isEmpty());
    delete testing;
}

/* size test
 * Run the third constructor to create a LinkedList using an array of size 5, 
 * then use the size method to ensure that the LinkedList created also has a 
 * size of 5
 */
void size_LL()
{
    char *testing= new char[5]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    testing[4] = 'k';
    CharLinkedList testLinkedList(testing, 5);
    assert(testLinkedList.size()==5);
    delete [] testing;
}

/* first, last and element at test
 *  Run the third constructor to create a LinkedList using an array of size 5, 
 * then use the first(), last() and elementAt() methods based on knowledge of 
 * the placement of the items in the LinkedList to ensure that they work 
 * properly
 */
void first_last_elementAt_LL()
{
    char *testing= new char[5]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    testing[4] = 'k';
    CharLinkedList testLinkedList(testing, 5);
    assert(testLinkedList.first()=='g' 
    and testLinkedList.last()=='k' 
    and testLinkedList.elementAt(2)=='i');
    delete [] testing;
}

/* push at front test
 *  Run the secondary constructor to create a LinkedList. Then run the 
 * pushAtFront() function. Finally, assert that the first element is the one 
 * that was inserted into the front and the back element is the one that was 
 * pushed backward to ensure that the pushAtFront function works properly.  
 */
void push_at_front_LL()
{
    CharLinkedList *testing = new CharLinkedList('a'); 
    testing->pushAtFront('b');
    assert(testing->first()=='b');
    delete testing;
}

/* insert at test
 *  Run the third constructor to create a LinkedList from an array. Then run 
 * the insertAt() function to insert an element to the LinkedList at a 
 * specified index. Then assert that the element at the specified index is 
 * truly the element that you inserted, and that the last element had been 
 * pushed backward properly. 
 */
void insert_at_LL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'i';
    testing[2] = 'j';
    testing[3] = 'k';
    CharLinkedList *testLinkedList = new CharLinkedList(testing, 4);
    testLinkedList->insertAt('h', 1);
    testLinkedList->insertAt('l', 5);
    assert(testLinkedList->elementAt(1)=='h' and testLinkedList->elementAt(4)=='k');
    delete [] testing;
    delete testLinkedList;
}

/* remove at test
 *  Run the third constructor to create a LinkedList from an array. Then run 
 * the remvoveAt() function to remove multiple elements from the LinkedList.
 * Then assert that the element at the back had been shifted forward properly.
 */
void remove_at_LL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    CharLinkedList *testLinkedList = new CharLinkedList(testing, 4);
    testLinkedList->removeAt(0);
    testLinkedList->removeAt(0);
    testLinkedList->removeAt(0);
    assert(testLinkedList->first()=='j');
    delete [] testing;
    delete testLinkedList;
}

/* replace at test
 *  Run the third constructor to create a LinkedList from an array. Then run 
 * the replaceAt() function to replace an element in the array. Then assert 
 * that the element at the specified index had been properly replaced.
 */
void replace_at_LL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'w';
    testing[3] = 'j';
    CharLinkedList *testLinkedList = new CharLinkedList(testing, 4);
    testLinkedList->replaceAt('i', 2);
    assert(testLinkedList->elementAt(2)=='i');
    delete [] testing;
    delete testLinkedList;
}

/*  print test
 *  run the print function to ensure there are no errors and the output looks 
 * correct
 */
void print_LL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    CharLinkedList *testLinkedList = new CharLinkedList(testing, 4);
    testLinkedList->print();
    delete [] testing;
    delete testLinkedList;
}

/*
 * concatenate test 
 * runs the concatenate function on two linkedlists created from arrays, then 
 * tests to ensure that the size and final element are what is expected based
 * on the data from the two arrays.
*/
void concatenate_LL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    CharLinkedList *testLinkedList = new CharLinkedList(testing, 4);
    
    char *toConcatenate = new char[3]; 
    toConcatenate[0] = 'k';
    toConcatenate[1] = 'l';
    toConcatenate[2] = 'm';
    CharLinkedList *toAddToBack = new CharLinkedList(toConcatenate, 3);
    
    testLinkedList->concatenate(*toAddToBack);
    assert(testLinkedList->size() == 7 
            and testLinkedList->elementAt(6) == 'm');
            
    delete toAddToBack;
    delete [] toConcatenate;
    delete testLinkedList;
    delete [] testing;
}

/*
 * pop front and back tests
 * create linkedList, pop from front and back and ensure that the resulting 
 * array has characters in the right place.
*/
void pop_front_and_back_LL()
{
    char *testing= new char[4]; 
    testing[0] = 'g';
    testing[1] = 'h';
    testing[2] = 'i';
    testing[3] = 'j';
    CharLinkedList *testLinkedList = new CharLinkedList(testing, 4);
    testLinkedList->popFromFront();
    testLinkedList->popFromBack();
    assert(testLinkedList->first()=='h' 
           and testLinkedList->last()=='i');
    delete [] testing;
    delete testLinkedList;
}

/*
 * error messages tests
 * creates an empty linkedList and intentionally causes error messages because 
 * of array boundaries
 *NOTE: Commented out sections will cause test failure, by design
*/
void error_messages_LL()
{
    CharLinkedList *testLinkedList = new CharLinkedList();
    // testLinkedList->removeAt(5);
    // testLinkedList->insertAt('c', 5);
    // testLinkedList->replaceAt('c', 5);
    // testLinkedList->popFromFront();
    // testLinkedList->popFromBack();
    delete testLinkedList;
}