/* RPNCalc.h
 * This file is the interface for RPNCalc. It contains information about 
 * key functions and members used throughout the implementation.
 * Submitted by: Matthew Torres. 3/16/2021 
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include "DatumStack.h"

#ifndef RPNCALC_H
#define RPNCALC_H

//constants for the queries that the user can enter
const string TRUEQ = "#t";
const string FALSEQ = "#f";
const string NOTQ = "not";
const string PRINT = "print";
const string CLEAR = "clear";
const string DROP = "drop";
const string DUPLICATE = "dup";
const string SWAP = "swap";
const string QUIT = "quit";
const string EXECUTE = "exec";
const string OPENFILE = "file";
const string IFQ = "if";
const string OPS[10] = {"+", "-", "*", "/", "mod", "<", ">", "<=", ">=", "=="};

class RPNCalc{
    public:
        //constructor and destructor
        RPNCalc();
        ~RPNCalc();
        
        //public run function, called from main
        void run();
    private: 
        //checkCommands function, which calls other helper functions to handle
        //RPNCalc operations
        void checkCommands(istream &input);
        
        //helper functions to assist with locating and excecuting commands 
        //entered by user
        bool simpleCommands(string query);
        bool complexCommands(string query);
        
        //got_int, taken from got_int.cpp and used to assist with pushing ints
        //onto DatumStack
        bool got_int(string s, int *resultp);
        
        //helper functions that assist with the calculations performed by 
        //RPNCalc
        
        //simple commands
        void boolSwitch();
        void print();
        void swap();
        void operators(string q);
        
        //complex commands
        string parseRString(istream &sstream);
        void execute(istream &sstream);
        void openFile();
        void executeIf();
        
        //error checking
        bool errorCheck(string error);
        
        //private DatumStack member that stores all of the data used by the 
        //calculator
        DatumStack calculator;
        
};
#endif