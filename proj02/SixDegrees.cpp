/*
 * SixDegrees.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Matthew Torres, 4/21/2021
 *
 * Purpose: The implementation of the SixDegrees class, which 
 populates the graph and handles the BFS, DFS and NOT commands.
 */

#include "SixDegrees.h"


SixDegrees::SixDegrees(){
    
}

/* run()
 * Purpose: This function is the public function called from 
 main which is responsible for populating the graph and running 
 the command loops
 * Arguments: istreams for the input and command files/streams 
 and an ostream for the output file/stream
 * Returns: none, but runs the SixDegrees game.
*/
void SixDegrees::run(istream &input, istream &command, ostream &output){
    populate(input);
    
    command_loop(command, output);
}

/* populate()
 * Purpose: this graph reads in from the input file and populates
 the CollabGraph.
 * Arguments: takes an input file formatted to input artists and 
 their discography
 * Returns: nothing, but modifies the CollabGraph
*/
void SixDegrees::populate(istream &input){
    string name;
    getline(input, name);
    while(not input.eof())
    {
        //make new artist
        Artist newArtist;
        
        //set artist name 
        newArtist.set_name(name);
        getline(input, name);
        
        //set artist discography
        while(name != "*" and not input.eof())
        {
            newArtist.add_song(name);
            getline(input, name);
        }
        
        //add artist to vector and graph
        artists.push_back(newArtist);
        collabs.insert_vertex(newArtist);
        
        //check to see if any collaborations can be added
        check_edges(newArtist);
        getline(input, name);
    }
    
}

/* check_edges()
 * Purpose: Checks an artist's discography against all the other 
 artists discography to find where edges need to be added
 * Arguments: takes an artist
 * Returns: none, but modifies the CollabGraph
*/
void SixDegrees::check_edges(Artist newArtist)
{
    //compare discography of current artist to other artists in vector
    for(int i = 0; i < (int)(artists.size()); i++)
    {
        string collaboration = newArtist.get_collaboration(artists[i]);
        
        //if collaboration exists, add an edge between 2 artists
        if(collaboration != "" and newArtist != artists[i])
        {
            collabs.insert_edge(newArtist, artists[i], collaboration);
        }
    }
}

/* command_loop()
 * Purpose: runs the command loop, calling the required 
 functions for each command.
 * Arguments: takes an istream to read the commands from, and 
 an output file to print the output to
 * Returns: nothing, but prints to output
*/
void SixDegrees::command_loop(istream &command, ostream &output){
    string cmd, start, end;
    getline(command, cmd);
    while(cmd != "quit" and not command.eof())
    {
        // Uncomment to make command.txt output cleaner 
        // if(cmd[0] == '%' or cmd == "")
        // {
        // 
        //     if(cmd[2] != '%') {output << endl << cmd << endl <<endl;}
        //     else {output << cmd << endl;}
        //     command >> cmd;
        //     continue;
        // }
        
        //handles BFS command 
        if(cmd == "bfs")
        {   
            //get start and end artists    
            getline(command, start);
            getline(command, end);
            collabs.clear_metadata();
            
            //if artists exist, perform BFS and print results
            if(not error_check(start, end, output))
            {
                print_results(BFS(get_artist(start), get_artist(end)), output,
                start, end);
            }
        }
        
        //handle DFS command
        else if(cmd == "dfs")
        {      
            //get start and end artists
            getline(command, start);
            getline(command, end);
            collabs.clear_metadata();
            
            //if artists exist, perform DFS and print results
            if(not error_check(start, end, output))
            {
                print_results(DFS(get_artist(start), get_artist(end)), output,
                start, end);
            }
        }
        
        //handle NOT command
        else if(cmd == "not")
        {   
            //get start and end elements     
            getline(command, start);
            getline(command, end);
            
            //get exclusions and finish not command
            get_exclusions(command, output, start, end);
        }
        
        //handle errors in command entry
        else
        {
            output << cmd <<" is not a command. Please try again."<<endl;
        }
        
        //get the next command
        getline(command, cmd);
    }    
}

/* get_exclusions()
 * Purpose: a helper function for the "not" command that 
 reads in the exclusions, checks errors, and calls the NOT() function
 * Arguments: takes an istream for the command, an ostream for the output file
 * and 2 strings for the names of the start and end Artists.
 * Returns: none, but prints to output
*/
void SixDegrees::get_exclusions(istream &command, ostream &output,
                                string start, string end)
{
    bool error_found = false;
    string exclusion;
    queue<Artist> exclusions;
    queue<string> excludeNames;
    
    //push each of the names onto a list of strings (allows for error checking
    //in the order that matches reference implementation)
    getline(command, exclusion);
    while(exclusion != "*" and not command.eof())
    {
        excludeNames.push(exclusion);
        getline(command, exclusion);
    }
    
    //error check start and end names
    if(error_check(start, end, output))
    {
        error_found = true;
    }
    
    
    while(not excludeNames.empty())
    {
        //push each artist that exists onto queue of artists
        if(not error_check(excludeNames.front(), output))
        {
            exclusions.push(get_artist(excludeNames.front()));
            excludeNames.pop();
        }
        else
        {
            //if an artist doesn't exist, reset
            error_found = true;
            excludeNames.pop();
        }
    }
    collabs.clear_metadata();
    
    //if no errors are found, perform NOT command and print output
    if(not error_found)
    {
        print_results(NOT(get_artist(start), get_artist(end), 
        exclusions), output, start, end);
    }
}

/* BFS()
 * Purpose: handles the BFS command by performing a BFS traversal and returning
 the path found.
 * Arguments: takes the from artist and the to artist from which the path
 is derived.
 * Returns: a stack that holds the artists along the shortest path between
 the 2 artists.
*/
stack<Artist> SixDegrees::BFS(const Artist &from, const Artist &to){
    queue<Artist> visited;
    collabs.mark_vertex(from);
    visited.push(from);
    
    //while the queue of visited artists is not empty, continue to push each
    //shell onto the queue
    while(not visited.empty())
    {
        Artist currArtist = visited.front();
        //mark the current vertex as visited
        collabs.mark_vertex(currArtist);
        vector<Artist> currNeighbors = collabs.get_vertex_neighbors(currArtist);
        for(int i = 0; i < (int)(currNeighbors.size()); i++)
        {
            //set the predecessor so path can be found later
            collabs.set_predecessor(currNeighbors[i], currArtist);
            if(not collabs.is_marked(currNeighbors[i]))
            {
                collabs.mark_vertex(currNeighbors[i]);
                visited.push(currNeighbors[i]);
            }
            //once the artist is found, return the path 
            if(currNeighbors[i] == to)
            {
                return collabs.report_path(from, to);
            }
        }
        visited.pop();
    }
    //if no path is found, return the an empty stack
    stack<Artist> emptyStack;
    return emptyStack;
}

/* DFS()
 * Purpose: the shell function for the DFS command, which calls the recursive
 DFS function and then reports the path found by that funcion.
 * Arguments: takes a from and a to artist, from which the path is derived
 * Returns:
*/
stack<Artist> SixDegrees::DFS(Artist from, Artist to){
    //prepare the path 
    DFS(from, &from, nullptr, to);
    //return the path
    return collabs.report_path(from, to);
}

/* DFS()
 * Purpose: recursively travels across the graph to find a path from the from 
 artist to the to artist. 
 * Arguments: takes a from artist, pointers to the current artist and 
 predecessor to that artist, and a to artist.
 * Returns: nothing, but preps the graph to report a path in the shell function.
*/
void SixDegrees::DFS(Artist from, Artist *current, Artist *previous,
     Artist to){
    //mark the current vertex as visited
    collabs.mark_vertex(*current);
    if(previous != nullptr)
    {
        //set the predecessor so path can be found later
        collabs.set_predecessor(*current, *previous);
    }
    if(*current == to)
    {
        //base case: if vertex is found, end recursion
        return;
    }
    vector<Artist> currNeighbors = collabs.get_vertex_neighbors(*current);
    for(int i = 0; i < (int)(currNeighbors.size()); i++)
    {
        if(not collabs.is_marked(currNeighbors[i]))
        {
            //recurse with an unvisited neighbor of the current vertex
            DFS(from, &currNeighbors[i], current, to);
        }
    }
}

/* NOT()
 * Purpose: marks the exclusive vertices as visited, then calls BFS to find an
 * exclusive path
 * Arguments: takes a from artist, a to artist and a list of excluded artists.
 * Returns: the stack of artists that form the path from the from artist to the
 to artist
*/
stack<Artist> SixDegrees::NOT(const Artist &from, const Artist &to, 
    queue<Artist> exclusions){
    if(exclusions.front() == from)
    {
        stack<Artist> emptyStack;
        return emptyStack;
    }
    collabs.mark_vertex(exclusions.front());
    exclusions.pop();
    //mark each of the exclusions as visited
    while(not exclusions.empty())
    {
        //edge case: if the first artist is excluded!
        if(exclusions.front() == from)
        {
            stack<Artist> emptyStack;
            return emptyStack;
        }
        collabs.mark_vertex(exclusions.front());
        exclusions.pop();
    }
    //call bfs on the prepped graph
    return BFS(from, to);
}

/* get_artist()
 * Purpose: searches through the vector of artists to both ensure that the
 artist with the given name exists, and return that artist if it exists
 * Arguments: the string name corresponding to the artist being searched for
 * Returns: the artist with the given name
*/
Artist SixDegrees::get_artist(string name)
{
    //search the vector of artists for the artist that exists
    for(int i = 0; i < (int)artists.size(); i++)
    {
        if(artists[i].get_name()==name)
        {
            return artists[i];
        }
    }
    //if the artist does not exist, throw an error
    throw "\"" + name + "\" was not found in the dataset :(";
}

/* print_results()
 * Purpose: prints the path returned from the BFS, DFS and NOT commands. If no 
 path exists, it says so. 
 * Arguments: Takes the stack returned from report_path(), an output stream,
 and the string names of the start and end 
 * Returns: none, but prints to output
*/
void SixDegrees::print_results(stack<Artist> results, ostream &output, 
    string start, string end)
{
    //if the path is empty, print that a path does not exist
    if(results.empty())
    {
        output << "A path does not exist between \""<< start <<
        "\" and \"" << end << "\"." <<endl;
        return;
    }
    //if the path isnt empty, print each collaboration
    while(not results.empty())
    {
        Artist top = results.top();
        results.pop();
        if(results.empty())
        {
            break;
        }
        Artist next = results.top();
        output << "\"" << top <<"\" collaborated with \"" << next << "\" in \"" 
        << top.get_collaboration(next) << "\"." << endl;
    }
    output <<"***"<<endl;
}

/* error_check()
 * Purpose: ensures that an artist with the given name exists, and prints an 
 error if it doesn't
 * Arguments: takes the name of an artist, and an output stream to print the
 errors to
 * Returns: a bool for whether an error has been found
*/
bool SixDegrees::error_check(string name, ostream &output)
{
    //ensure that the artist exists
    try
    {
        get_artist(name);
    }
    catch(string e)
    {
        output << e << endl;
        return true;
    }
    return false;
}

/* error_check()
 * Purpose: ensures that 2 artists with the given name exists, and prints an 
 error if it doesn't
 * Arguments: takes the name of an artist, and an output stream to print the
 errors to
 * Returns: a bool for whether an error has been found
*/
bool SixDegrees::error_check(string name1, string name2, ostream &output)
{
    //ensure that the first artist exists
    bool error_found = false;
    try
    {
        get_artist(name1);
    }
    catch(string e)
    {
        output << e << endl;
        error_found = true;
    }
    //ensure that the second artist exists
    try
    {
        get_artist(name2);
    }
    catch(string e)
    {
        output << e << endl;
        error_found = true;
    }
    return error_found;
}

