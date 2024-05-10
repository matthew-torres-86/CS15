/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Matthew Torres, 4/21/2021
 *
 * Purpose: The driver file for SixDegrees.cpp that determines which 
 * I/O streams to send it and calls the run function.
 */
#include <iostream>
#include <fstream>
#include "SixDegrees.h"
#include "CollabGraph.h" 
using namespace std;

// SIXDEGREES MAIN DRIVER
int main(int argc, char *argv[])
{
    SixDegrees ArtistCollabs;
    ifstream infile;
    ifstream cmdfile;
    ofstream outfile;
    infile.open(argv[1]);
    if(not infile.is_open())
    {
        cerr << argv[1] << " could not be opened."<<endl;
        exit(EXIT_FAILURE);
    }
    
    if(argc == 2)
    {
        ArtistCollabs.run(infile, cin, cout);
    }
    else if(argc == 3)
    {
        cmdfile.open(argv[2]);
        if(not cmdfile.is_open())
        {
            cerr << argv[2] << " could not be opened."<<endl;
            exit(EXIT_FAILURE);
        }
        ArtistCollabs.run(infile, cmdfile, cout);
    }
    else if(argc == 4)
    {
        cmdfile.open(argv[2]);
        if(not cmdfile.is_open())
        {
            cerr << argv[2] << " could not be opened."<<endl;
            exit(EXIT_FAILURE);
        }
        outfile.open(argv[3]);
        if(not outfile.is_open())
        {
            cerr << argv[3] << " could not be opened."<<endl;
            exit(EXIT_FAILURE);
        }
        ArtistCollabs.run(infile, cmdfile, outfile);
    }
    return 0;
}
