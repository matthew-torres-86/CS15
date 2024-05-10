/*
 * SixDegrees.h
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Matthew Torres, 4/21/2021
 *
 * Purpose: The interface for the SixDegrees class which contains declarations
 for its public and private member functions, as well as the CollabGraph and 
 vector of artists which are both used throughout the program.
 */
#ifndef _SIX_DEGREES_H_
#define _SIX_DEGREES_H_

#include "CollabGraph.h"
#include "Artist.h"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

class SixDegrees
{
public:
    SixDegrees();
    
    //public function called from main
    void run(istream &input, istream &command, ostream &output);
private:
    //functions for populating graph
    void populate(istream &input);
    void check_edges(Artist newArtist);
    
    
    
    //functions for running commands
    void command_loop(istream &command, ostream &output);
    stack<Artist> BFS(const Artist &from, const Artist &to);
    stack<Artist> DFS(Artist from, Artist to);
    void DFS(Artist from, Artist *current, Artist *previous, 
        Artist to);
    stack<Artist> NOT(const Artist &from, const Artist &to, 
        queue<Artist> exclusions);
    void get_exclusions(istream &command, ostream &output, string start, 
        string end);
    
    //other helper functions
    Artist get_artist(string name);
    void print_results(stack<Artist> results, ostream &output, string 
        start, string finish);
    bool error_check(string name, ostream &output);
    bool error_check(string name1, string name2, ostream &output);
    
    //member objects
    CollabGraph collabs;
    vector<Artist> artists;
};

#endif