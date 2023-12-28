/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.text
content: The text file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cctype>

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    // TODO: create arrays needed
	// TOTO: prep all arrays
    // TODO: prompt until both the file and the contained data are valid
    // TODO: determine ranking, notice the rank array receives the results
    // TODO: Output results
	// catch (...) -> catches every error (hehehehehe)
	
	double time[SIZE];
	unsigned int rank[SIZE];
	unsigned int jersey[SIZE];
	string country[SIZE];
	string name[SIZE];
	
	prep_unsigned_int_array(rank);
	prep_unsigned_int_array(jersey);
	prep_double_array(time);
	prep_string_array(country);
	prep_string_array(name);
	
    string filename = "";
	bool good = false;
	
	while(!good){
		cout << "Enter file name: ";
		cin >> filename;
		try{
			get_runner_data(filename, time, country, jersey, name);
			good = true;
		}
		catch(std::invalid_argument& g){
			cout << "Invalid File: " << g.what() << endl;
		}
		catch (std::domain_error& g){
			cout << "Invalid File: " << g.what() << endl;
		}
	}
	
	get_ranking(time, rank);
	print_results(time, country, name, rank);
    return 0;
}

