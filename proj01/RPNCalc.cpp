/* RPNCalc.cpp
 * This file is the implementation for RPNCalc. It contains key functions
 * that read in the users commands and perform various operations based on 
 * these commands.
 * Submitted by: Matthew Torres. 3/16/2021 
*/

#include "RPNCalc.h"

// empty constructor
RPNCalc::RPNCalc()
{}

// empty destructor: no heap allocated memory to delete
RPNCalc::~RPNCalc()
{}

/* run()
 * Purpose: public run function called from main. Simply calls checkCommands()
 * with an input of cin.
 * Arguments: none
 * Returns: nothing, calls the major operational function checkCommands()
*/
void RPNCalc::run()
{
    checkCommands(cin);
    cerr << "Thank you for using CalcYouLater." << endl;
}

/* checkCommands()
 * Purpose: searches through list of valid commands to determine which (if any)
 * the user is calling. If it finds a valid command, it performs the desired
 * operation or calls a function that does so. 
 * Arguments: an istream variable used for modularity to account for the 
 * various types of input that you need to read commands from.
 * Returns: nothing, but modifies the calculator DatumStack.
*/
void RPNCalc::checkCommands(istream &input)
{
    string query = ""; //stores value from input
    int number = 0; // used to push numerical values from got_int
    bool toContinue = true; //tells program when to stop iterating through 
    //queries
    
    while(not (input.fail() or input.eof()) and toContinue)
    {        
        //store input
        input >> query;
        if(input.eof())
        {
            return;
        }
        // pushing numerical values
        if(got_int(query, &number))
        {
            Datum newD(number);
            calculator.push(newD);
        }
        
        //performing simple commands
        else if (simpleCommands(query))
        {
            print("simple");
            toContinue = true;
        }
        
        //performing complex commands
        else if(complexCommands(query))
        {
            toContinue = true;
        }
        
        //dealing with rStrings
        else if(query == "{")
        {
            Datum newD(parseRString(input));
            if(newD.toString() != "{")
            {
                calculator.push(newD);
            }
        }
        
        //stops dealing with rstrings
        else if(query == "}")
        {
            toContinue=false;
        }
        
        //quits program
        else if(query == QUIT) 
        {    
            toContinue=false;
        }
        
        //error checking for invalid queries
        else
        {
            cerr << query << ": unimplemented" << endl;
        }
    }
}

/* simpleCommands()
 * Purpose: checks input to see if any of the simple commands are found. 
 * performs desired operations and returns true if the simple commands have 
 * been accomplished. 
 * Arguments: a string that holds the query sent from checkCommands()
 * Returns: a bool for whether a simple command has been found
*/
bool RPNCalc::simpleCommands(string query)
{
    //pushes bools to DatumStack
    if(query == TRUEQ or query == FALSEQ){
        Datum newD(query == TRUEQ);
        calculator.push(newD);
        return true;
    }
    
    //performs "not" operation (switches top element in stack if bool)
    else if(query == NOTQ){
        boolSwitch();
        return true;
    }
    
    //performs "print" operation (prints top element of datumStack)
    else if(query == PRINT){
        print(); 
        return true;
    }
    
    //performs "clear" operation (clears DatumStack)
    else if(query == CLEAR){
        calculator.clear();
        return true;
    }
    
    //performs "drop" operation (removes top element in DatumStack)
    else if(query == DROP){
        if(errorCheck("empty"))
        {
            return true;
        }
        calculator.pop();
        return true;
    }
    
    //performs "dup" operation (duplicates top element in DatumStack)
    else if(query == DUPLICATE){
        if(errorCheck("empty"))
        {
            return true;
        }
        calculator.push(calculator.top());
        return true;
    }
    
    //performs "swap" operation (swaps top 2 elements in DatumStack)
    else if(query == SWAP){
        if(errorCheck("empty"))
        {
            return true;
        }
        swap(); 
        return true;
    }
    
    //cycles through the operations to find the correct one. performs 
    //calculation in operators function
    for(int i = 0; i < 10; i++){
        if(query == OPS[i]){
            operators(query);
            return true;
        }
    }
    
    //none of the simple commands have been found
    return false;
}

/* complexCommands()
 * Purpose: checks input to see if any of the complex commands are found. 
 * performs desired operations and returns true if the simple command has 
 * been accomplished. 
 * Arguments: a string that holds the query sent from checkCommands()
 * Returns: a bool for whether a complex command has been found
*/
bool RPNCalc::complexCommands(string query)
{
    //performs "exec" operation ("decompresses" an rstring, and runs commands 
    // within)
     if(query == EXECUTE){
         istringstream sstream;
         sstream.str(calculator.top().getRString());
        execute(sstream);
        return true;
    }
    
    //performs "file" operation (opens filename stored in rstring)
    else if(query == OPENFILE){
        openFile(); 
        return true;
    }
    
    //performs "if" operation (pops 2 rstrings off the stack and tests a 
    //condition to see which one to execute)
    else if(query == IFQ){
        executeIf(); 
        return true;
    }
    
    //none of the complex commands have been found
    else{
        return false;
    }
}

/* got_int()
 * Purpose: takes a string to see if it is an int. Modifies an int to store the 
 * numeric value that the string represents 
 * Arguments: a string to represent an int. A pointer to an int value to modify
 * such that the string int is converted to an int
 * Returns: a bool that states whether the string was numeric
*/
bool RPNCalc::got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* boolSwitch()
 * Purpose: pops a bool from the DatumStack, reverses is,  then pushes it back 
 * on the stack. If the top of the stack is not a bool, catches and prints
 * an error message.
 * Arguments: None
 * Returns: Nothing, but modifies the last element in the stack if it is a bool
*/
void RPNCalc::boolSwitch()
{
    //error checking for empty_stack and datum_not_bool
    if (errorCheck("empty"))
    {
        return;
    }
    if (errorCheck("bool"))
    {
        calculator.pop();
        return;
    }
    
    //pop reverse of bool onto stack
    Datum newD(not calculator.top().getBool());
    calculator.pop();
    calculator.push(newD);
}

/* print()
 * Purpose: prints error if stack is empty. otherwise prints top item on stack
 * Arguments: none.
 * Returns: nothing, but prints to cout the top datum in the stack
*/
void RPNCalc::print() 
{
    //error checking for empty_stack
    if (errorCheck("empty"))
    {
        return;
    }
    
    //print top element on DatumStack
    cout << calculator.top().toString() << endl;
}

/* swap()
 * Purpose: prints error if stack is empty. otherwise, switches top two elements
 * in the stack.
 * Arguments: none
 * Returns: nothing, but modifies the datumStack.
*/
void RPNCalc::swap()
{
    //error check for empty
    if (errorCheck("empty"))
    {
        return;
    }
    
    //store and pop first element
    Datum datum1 = calculator.top();
    calculator.pop();
    
    //error check for empty again
    if (errorCheck("empty"))
    {
        calculator.push(datum1);
        return;
    }
    
    //store and pop second element
    Datum datum2 = calculator.top();
    calculator.pop();
    
    //reverse order
    calculator.push(datum1);
    calculator.push(datum2); 
}

/* operators()
 * Purpose: handles the numeric operators 
 * Arguments: none
 * Returns: nothing, but modifies the datumStack.
*/
void RPNCalc::operators(string q)
{
    int num1, num2;
    
    //error check for empty
    if(errorCheck("empty"))
    {
        return;
    } 
    
    //== functions differently from other operators
    if (q == "==")
    {
        //pop and store datum
        Datum datum1 = calculator.top();
        calculator.pop();
        Datum datum2 = calculator.top();
        calculator.pop();
        
        //push bool for equality
        Datum newD(datum1 == datum2);
        calculator.push(newD);
    }
    else
    {
        //all operators besides == must use int values
        if(errorCheck("int"))
        {
            //undoes entire command
            calculator.pop();
            calculator.pop();
            return;
        }  
        
        //pop and store first int
        num2 = calculator.top().getInt();
        calculator.pop();
        
        //ensure second value is an int
        if(errorCheck("int"))
        {
            calculator.pop();
            return;
        }  
        
        //pop and store second int
        num1 = calculator.top().getInt();
        calculator.pop();
    }
    
    //addition 
    if(q == "+")
    {
        Datum newD(num1 + num2);
        calculator.push(newD);
    }
    
    //subtraction
    else if(q == "-")
    {
        Datum newD(num1 - num2);
        calculator.push(newD);
    }
    
    //multiplucation
    else if((q == "*"))
    {
        Datum newD(num1 * num2);
        calculator.push(newD);
    }
    
    //division
    else if(q == "/")
    {
        //divide by 0 error
        if(num2 == 0)
        {
            cerr << "Error: division by 0." <<endl;
        }
        else
        {
            Datum newD(num1 / num2);
            calculator.push(newD);
        }
    }
    
    //mod
    else if(q == "mod")
    {
        //divide by 0 error
        if(num2 == 0)
        {
            cerr << "Error: division by 0." <<endl;
        }
        else
        {
            Datum newD(num1 % num2);
            calculator.push(newD);
        }
    }
    
    //greater than
    else if(q == ">")
    {
        Datum newD(num1 > num2);
        calculator.push(newD);
    }
    
    //less than
    else if(q == "<")
    {
        Datum newD(num1 < num2);
        calculator.push(newD);
    }
    
    //greater than or equal to
    else if (q == ">=")
    {
        Datum newD(num1 >= num2);
        calculator.push(newD);
    }
    
    //less than or equal to
    else if(q == "<=")
    {
        Datum newD(num1 <= num2);
        calculator.push(newD);
    }
}

/* parseRString()
 * Purpose: parses over an rString entered as a command by the user and Returns
 * the entire string, from the opening bracket to its corresponding closing 
 * bracket
 * Arguments: takes a input stream which it parses over
 * Returns: the concatenated string of all the individual rString parts
*/
string RPNCalc::parseRString(istream &sstream)
{
    string d = ""; //stores input from istream
    string fullString = "{"; //the "compressed" rstring pushed onto stack
    DatumStack brackets; //a datumstack to keep track of brackets
    Datum newD("{"); //the original open bracket
    brackets.push(newD); 

    //iterates through until open brackets have all been closed
    while(not sstream.fail() and not brackets.isEmpty())
    {
        sstream >> d;
        Datum newD(d);
        
        //if bracket, push onto brackets stack
        if(d == "{")
        {
            brackets.push(newD);
        }
        
        //if closing bracket, close an open bracket or push onto stack
        else if(d =="}")
        {
            if(brackets.top().toString()=="{")
            {
                brackets.pop();
            }
            else
            {
                brackets.push(newD);
            }
        }
        
        //concatenate segment onto fullstring
        fullString += " " + d;
    }
    
    //return fullstring to be pushed onto DatumStack
    return fullString;
}

/* execute()
 * Purpose: provides functionality for the "exec" command. 
 * "decompresses" an rString stored on the datumStack and passes it 
 * as an istringstream to the checkCommands function.
 * Arguments: takes an input stream which it sends to check commands 
 * Returns: nothing, but modifies the datumStack.
*/
void RPNCalc::execute(istream &sstream)
{
    //parse over first bracket
    string d;
    sstream >> d;
    
    //pop entire rString off of stack
    calculator.pop();

    //check commands from within the rstring
    checkCommands(sstream);
}

/* openFile()
 * Purpose: reads in a filename from an rString. opens file and passes it to
 * checkCommands function as an istream
 * Arguments: none
 * Returns: nothing, but modifies the datumStack.
*/
void RPNCalc::openFile()
{
    ifstream infile;
    stringstream sstream;
    string f;
    
    //error checking for not rstring
    if(not calculator.top().isRString())
    {
        cerr << "Error: file operand not rstring"<<endl;
        calculator.pop();
        return;
    }

    //load rstring into stringstream and pop entire rstring from stack
    sstream.str(calculator.top().getRString());
    calculator.pop();
    
    //parse past open bracket and then read in filename
    sstream >> f; 
    sstream >> f;
    
    //open file
    infile.open(f);
    
    //error checking for invalid filename
    if(not infile.is_open())
    {
        cerr << "Unable to read " << f<<endl;
        return;
    }
    
    //check commands from file
    checkCommands(infile);
}

/* executeIf()
 * Purpose: provides functionality for the "if" command, which pops multiple
 * datum from the stack and performs a comparison to determine which rstring
 * executes 
 * Arguments: none
 * Returns: nothing, but modifies the datumStack.
*/
void RPNCalc::executeIf()
{ 
    bool condition;
    istringstream sstream;
    string trueCase, falseCase;
    
    //checking if falsecase is int for recursivity
    if(calculator.top().isInt())
    {
        return;
    }
    //checking if falsecase is string, popped off stack and stored
    else if(calculator.top().isRString())
    {
        falseCase = calculator.top().toString();
        calculator.pop();
    }
    //error checking for not int or string
    else
    {
        cerr << "Error: expected rstring in if branch" << endl; 
        return;
    }
    
    //checking if trueCase is int for recursivity
    if(calculator.top().isInt())
    {
        return;
    }
    //checking if trueCase is string, popped off stack and stored
    else if(calculator.top().isRString())
    {
        trueCase = calculator.top().getRString();
        calculator.pop();
    }
    //error checking for not int or string
    else
    {
        cerr << "Error: expected rstring in if branch" << endl; 
        return;
    }
    
    //error checking for bool 
    if(calculator.top().isBool())
    {
        condition = calculator.top().getBool();
        calculator.pop();
    }
    else
    {
        cerr << "Error: expected boolean in if test" <<endl;
        return;
    }
    
    //executing the true case if bool is true and false case if bool is false
    if(condition)
    {
        Datum newD(trueCase);
        calculator.push(newD);
    }
    else
    {
        Datum newD(falseCase);
        calculator.push(newD);
    }
    sstream.clear();
    sstream.str(calculator.top().getRString());
    execute(sstream);
}

/* errorCheck()
 * Purpose: takes a string to determine which type of error to check for, then
 * uses a try-catch block to catch and print the runtime_error(s).
 * Arguments: a string to determine which type of error is possible when the 
 * function is called
 * Returns: a bool to determine if the error was actually called, or if the 
 * program is clear to resume.
*/
bool RPNCalc::errorCheck(string error)
{
    //try block for various runtime_errors
    try{
        if(error == "empty")
        {
            calculator.top();
        }
        else if(error == "int")
        {
            calculator.top().getInt();
        }
        else if(error == "bool")
        {
            calculator.top().getBool();
        }
        else if(error == "rString")
        {
            calculator.top().getRString();
        }
    }
    //catch block to cerr error
    catch(runtime_error e)
    {
        cerr << "Error: " << e.what()<<endl;
        return true;
    }
    
    //if no error is found, return false and continue as normal
    return false;
}


