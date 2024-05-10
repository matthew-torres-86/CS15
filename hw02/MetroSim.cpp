/* MetroSim.cpp
 * This program takes in a list of train stations, and either an input file 
 * or user input to run a program that simulates the use of the MBTA Green Line
 * Submitted By: Matthew Torres. 3/2/21
 */

#include "MetroSim.h"

/* MetroSim Constructor
 * Initializes stations list, sets the ID iterator to 0, and creates new
 * vectors and passenger queues for each station.
 * Takes a vector<string> of station names to be added to the vector of station 
 * objects
*/
MetroSim::MetroSim(vector<string> *st)
{
    //Add stations to station vector based on preexisting station 
    //vector<string>
    for(int i = 0; i < (int)(st->size()); i++)
    {
        station *newStation = new station;
        vector<Passenger> *newPassengerV = new vector<Passenger>;
        PassengerQueue *newPassengerQ = new PassengerQueue();
        newStation->name = st->at(i);
        newStation->passengers = newPassengerV;
        newStation->boardedPassengers = newPassengerQ;
        train_location=1;
        stations.push_back(newStation);
    }
    //set ID iterator to 0
    largestID=0;
}

/* MetroSim Destructor
 * Deletes passenger queues, vectors, each of the stations in the stations 
 * vector and the stations vector itself to free up heap-allocated memory
 */
MetroSim::~MetroSim()
{
    //deleting heap allocated objects from memory

    for(int i = 0; i < (int)(stations.size()); i++)
    {
        delete stations[i]->passengers;
        
        delete stations[i]->boardedPassengers;
        delete stations[i];
    }
}

/* run()
 * Purpose: Called from main.cpp, commences the operations of the simulator
 * Arguments: Takes ostream and istream types to accomodate for the ambiguity 
 * of required input and output streams
 * Returns: nothing
 */
void MetroSim::run(ostream &output, istream &input)
{
    //print status of the simulator
    print();
    //prompt user for queries
    prompt(output, input);
}

/* print()
 * Purpose: Prints the status of the simulator to std::cout
 * Arguments: None
 * Returns: nothing, but prints neatly formatted text to std::cout
 */
void MetroSim::print()
{
    //print header with passengers that are riding the train
    cout << "Passengers on the train: {";
    for(int i = 0; i < (int)(stations.size()-1); i++)
    {
        stations[i]->boardedPassengers->print(cout);
    }
    cout << "}" << endl;
    
    //print stations, with passengers that are waiting at each station
    for(int i=1; i<(int)(stations.size()); i++)
    {
        if(i == train_location)
        {
            cout << "TRAIN: ";
        }
        else
        {
            cout << "       ";
        }
        cout << "[" << i << "] ";
        cout << stations.at(i-1)->name;
        cout << " {";
        if(not stations.at(i-1)->passengers->empty())
        {
            for(int j = 0; j < (int)(stations.at(i-1)->passengers->size()); j++)
            {
                stations.at(i-1)->passengers->at(j).print(cout);
            }
        }
        cout << "}" << endl;
    }
}

/* prompt()
 * Purpose: Prints the status of the simulator to std::cout
 * Arguments: None
 * Returns: nothing, but prints neatly formatted text to std::cout
 */
void MetroSim::prompt(ostream &output, istream &input)
{
    string query, query2;
    //prompt for command
    cout << "Command? ";
    input >> query;
    
    //allows for queries to have spaces between characters
    if(query == "m")
    {
        input >> query2;
        if(query2 == "f")
        {
            query = "mf";
        }
        else if(query == "m")
        {
            query = "mm";
        }
    }
    
    //add passenger
    if(query == "p")
    {
        addPassenger(input);
        run(output, input);
    }
    
    //move metro
    else if(query == "mm")
    {
        moveMetro(output);
        run(output, input);
    }
    
    //metro finish
    else if(query == "mf" or input.eof())
    {
        cout << "Thanks for playing MetroSim. Have a nice day!"<<endl;
    }
    
    //undefined query
    else
    {
        run(output, input);
    }
}

/* moveMetro()
 * Purpose: Move the train, board passengers that need to be boarded, offload 
 * passengers that need to be offloaded
 * Arguments: ostream for the output file that displays when passengers leave
 * the train
 * Returns: nothing, but modifies the simulation such that some passengers 
 * board the train, some leave and the train moves to the next station
 */
void MetroSim::moveMetro(ostream &output)
{
    //board passengers
    while(not stations[train_location-1]->passengers->empty())
    {
        Passenger currentPassenger = stations[train_location-1] ->
        passengers -> front();
        
        stations[currentPassenger.to] ->
        boardedPassengers -> enqueue(currentPassenger);
        
        stations[train_location-1] -> passengers -> 
        erase(stations[train_location-1]->passengers->begin());
    }
    
    //move train location
    train_location++;
    if(train_location == (int)stations.size())
    {
        train_location = 1;
    }
    
    //unboard passengers
    while(not stations[train_location]->boardedPassengers->empty())
    {
        Passenger currentPassenger = stations[train_location] -> 
        boardedPassengers->front();
        
        output <<"Passenger " << currentPassenger.id << " left train at " 
               << "station " << stations.at(train_location-1)->name << endl;
        stations[(train_location)]->boardedPassengers->dequeue();
    }
    
}

/* addPassenger()
 * Purpose: Adds a passenger to the correct station passenger queue, with all 
 * the required information
 * Arguments: input stream to initialize key information about the passenger 
 * such as their from station and their to station
 * Returns: nothing, but adds passenger to a passenger queue
 */
void MetroSim::addPassenger(istream &input)
{
    //create new passenger 
    Passenger *newPassenger = new Passenger();
    input >> newPassenger->from;
    input >> newPassenger->to;
    largestID++;
    newPassenger->id = largestID;
    
    //add passenger to desired station
    stations.at(newPassenger->from - 1)->passengers->push_back(*newPassenger);
    
}


