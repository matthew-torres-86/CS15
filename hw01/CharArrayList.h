/*
 * CharArrayList.h
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by Matthew Torres, 2/15/2021
 * 
 * One implementation of the CharArrayList interface. Stores characters,
 * preserving their order and imitating some functionalities of the C++ 
 * std::string.
 * 
 * Note: This is implemented using a dynamic array.
 */

#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

class CharArrayList {
    public:
        // constructors
        // initial capacity will be zero for default constructor
        CharArrayList();
        // start with a single character
        CharArrayList(char c); 
        // start with a list of characters
        CharArrayList(char *arr, int size); 
        // start with another CharArrayList
        CharArrayList(const CharArrayList &other); 
        // destructor
        ~CharArrayList();
        // assignment operator overload
        CharArrayList &operator =(const CharArrayList &rhs);


        // CharArrayList functions
        // get information about the list -- these won't modify the list
        bool isEmpty() const;
        int  size() const;
        char first() const;
        char last() const;
        char elementAt(int idx) const;
        void print() const;
        // insert into the list
        void pushAtBack(char c);
        void pushAtFront(char c);
        void insertAt(char c, int idx);
        // remove from the list
        void clear();
        void popFromFront();
        void popFromBack();
        void removeAt(int idx);
        // other ways to edit the list
        void replaceAt(char c, int idx);
        void concatenate(const CharArrayList &other);

    private:
        /* we will store the information in a dynamic array, so we need
        * variables for the array's address, the number of characters in the 
        * list, and the current size of the array in memory */
        char *data;
        int  len, cap; 

        // helper functions
        char *increaseCap();
        char *decreaseCap();
};

#endif