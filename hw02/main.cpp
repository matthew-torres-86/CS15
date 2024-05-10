/* main.cpp
 * The driver file for MetroSim.cpp, which reads in a station file and passes
 * input and output streams based on the number of command line arguments
 * Submitted By: Matthew Torres. 3/2/21
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "MetroSim.h"

using namespace std;

void readStationFile(vector<string> *stations, string filename);

int main(int argc, char *argv[])
{
	//Error checking for command line arguments
	if(argc != 3 and argc != 4)
	{
		cerr << "Usage. ./MetroSim stationsFile outputFile [commandsFile]" 
		<< endl;
		exit(EXIT_FAILURE);
	}
	
	//Creates a string vector to store names of different stations
	vector<string> *stations = new vector<string>;
	
	//read in station file and stores data in above vector
	readStationFile(stations, argv[1]);
	
	//creates new MetroSim instance
	MetroSim *MBTA = new MetroSim(stations);
	
	//input and output streams to be sent to MetroSim
	ifstream infile;
	ofstream outfile;
	
	//opens output file
	outfile.open(argv[2]);
	
	//defaults to input stream std::cin
	if(argc == 3)
	{
		MBTA->run(outfile, cin);
	}
	//However if there is a 4th arg, uses input file
	else if(argc == 4)
	{
		infile.open(argv[3]);
		if(not infile.is_open())
		{
			cerr << "ERROR: Could not open " << argv[3] << endl;
			exit(EXIT_FAILURE);
		}
		MBTA->run(outfile, infile);
	}
	
	//close the files, delete heap allocated memory, return 0
	infile.close();
	outfile.close();
	
	delete MBTA;
	delete stations;
	return 0;
}

void readStationFile(vector<string> *stations, string filename)
{
	//open infile to read in stations
	ifstream infile;
	infile.open(filename);
	
	if(not infile.is_open())
	{
		cerr << "Error: could not open file " << filename << endl;
		exit(EXIT_FAILURE);
	}
	
	//add station names to string vector.
	string nextStation;
	while(!infile.eof())
	{
		getline(infile, nextStation);
		stations->push_back(nextStation);
	}
	infile.close();
}
