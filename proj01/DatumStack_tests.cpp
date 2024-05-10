/* DatumStack_tests.cpp
 * This is the testing file for DatumStack.cpp, which uses Matt Russell's 
 * testing framework to ensure that each of the functions in DatumStack.cpp
 * work as expected.
 * Submitted by: Matthew Torres. 3/16/2021
*/
#include <iostream>
#include <cassert>
#include "Datum.h"
#include "DatumStack.h"

/* constructor and destructor test
 * creates and deletes a datumstack to ensure that any heap allocated 
 * memory is cleaned up and there are no runtime errors
*/
void datum_stack_constructor_and_destructor()
{
    DatumStack *tester = new DatumStack();
    delete tester;
}

/* is empty test
 * creates a new datumstack and then asserts that it is empty when created
*/
void datum_stack_is_empty()
{
    DatumStack *tester = new DatumStack();
    assert(tester->isEmpty());
    delete tester;
}

/* push and top test
 * creates a datum stack and 3 datum objects to push onto the stack. 
 * asserts that the top element was the one that was pushed onto the DatumStack 
 * last
*/
void datum_stack_push_and_top()
{
    DatumStack *tester = new DatumStack();
    Datum newD1(4);
    Datum newD2(false);
    Datum newD3("{ 1 2 + }");
    tester->push(newD1);
    tester->push(newD2);
    tester->push(newD3);
    assert(tester->top() == newD3);
    delete tester;
}

/* clear test
 * creates a datum stack, pushes 3 elements onto it, then runs clear(). 
 * asserts that datum stack isEmpty() after it has been cleared
*/
void datum_stack_clear()
{
    DatumStack *tester = new DatumStack();
    Datum newD1(4);
    Datum newD2(false);
    Datum newD3("{ 1 2 + }");
    tester->push(newD1);
    tester->push(newD2);
    tester->push(newD3);
    tester->clear();
    assert(tester->isEmpty());
    delete tester;
}

/* size test
 * pushes 3 elements onto a new datumstack then asserts that the size of the 
 * datumstack is 3
*/
void datum_stack_size()
{
    DatumStack *tester = new DatumStack();
    Datum newD1(4);
    Datum newD2(false);
    Datum newD3("{ 1 2 + }");
    tester->push(newD1);
    tester->push(newD2);
    tester->push(newD3);
    assert(tester->size() == 3);
    delete tester;
}

/* empty top test
 * ensures that the runtime_error is handled properly when top() is ran on an
 * empty datumStack
*/
void empty_top()
{
    DatumStack *tester = new DatumStack();
    try{
        tester->top();
    }
    catch(runtime_error e){
        cerr << "Error: " <<e.what();
    }
    delete tester;
}

/* pop test
 * creates a new datumstack, pushes 3 elements onto it. Then pops one element 
 * off of it and asserts that the element now at the top of the stack is the
 * second element pushed onto stack
*/
void datum_stack_pop()
{
    DatumStack *tester = new DatumStack();
    Datum newD1(4);
    Datum newD2(false);
    Datum newD3("{ 1 2 + }");
    tester->push(newD1);
    tester->push(newD2);
    tester->push(newD3);
    tester->pop();
    assert(tester->top() == newD2);
    delete tester;
}

/* empty pop test
 * attempts to pop from an empty datumStack to ensure that the runtime_error 
 * is handled properly
*/
void empty_pop()
{
    DatumStack *tester = new DatumStack();
    try{
        tester->pop();
    }
    catch(runtime_error e){
        cerr << "Error: " <<e.what();
    }
    delete tester;
}