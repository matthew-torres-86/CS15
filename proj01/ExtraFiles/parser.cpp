/* parser.cpp
 * This file contains the parseRString() function that will later be used in 
 * RPNCalc. 
 * Submitted by: Matthew Torres. 3/10/2021
 */
 #include <string>
 #include <iostream>
 #include "DatumStack.h"
 
 using namespace std;
 
 /* parseRString()
  * Purpose: This function takes in an rstring and "zips" it into a single 
  * string until the brackets are closed, or the line ends. Afterwards, it
  * carries on reading from input into the DatumStack 
  * Arguments: Takes an input stream from which to read the rString
  * Returns: A single string that contains all of the components of an rstring
 */
 string parseRString(istream &input)
 {
    string d = " ";
    string fullString = "{ ";
    DatumStack brackets;
    Datum newD("{");
    brackets.push(newD);
    while(not input.fail() and not brackets.isEmpty())
    {
        input >> d;
        Datum newD(d);
        if(d == "{")
        {
            brackets.push(newD);
            cout << "Added open bracket" << endl;
        }
        else if(d =="}")
        {
            if(brackets.top().toString()=="{")
            {
                brackets.pop();
                cout << "Closed open bracket" << endl;
            }
            else
            {
                brackets.push(newD);
                cout << "Added close bracket" << endl;
            }
        }
        cout << "Added " << d << " to string" << endl;
        fullString += d + " ";
        cout << "Full string: " << fullString << endl;
    }
    return fullString;
 }
 
 
 // int main(int argc, char *argv[])
 // {
 //    string j;
 //    cout << parseRString(cin) <<endl;
 //    return 0;
 // }