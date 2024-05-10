/* main.cpp
 * This is the driver file for DatumStack.cpp
 * Submitted by Matthew Torres. 3/7/2021 
*/
#include "RPNCalc.h"
#include "Datum.h"
#include "DatumStack.h"
#include <iostream>
using namespace std;
int main()
{
    //create new RPNCalc object
    RPNCalc *myCalc = new RPNCalc();
    
    //run
    myCalc->run();
    
    //delete RPNCalc object
    delete myCalc;
    return 0;
}