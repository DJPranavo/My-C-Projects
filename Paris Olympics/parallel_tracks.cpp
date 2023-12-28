#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cctype>


using std::string;
using namespace std;

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
	string line = "";
	string word = "";
	int county = 0;
	int countyyy = 0;

	ifstream filename(file);
	if(!filename.is_open()){
		throw std::invalid_argument("Cannot open file");
	}
	while(getline(filename, line) && !filename.eof()){
		if(line.empty()){
			throw std::domain_error("File missing data");
		}
		else{
			istringstream stream(line);
			while(!stream.eof()){
				if(county==3){
					getline(stream,word);	
				}
				else{
					getline(stream, word, ' ');
				}
				word = trim(word);
				if(word.size() == 0){
					throw std::domain_error("File contains invalid data (name)");
				}
				for(int i = 0; i<(int)word.size(); ++i){
					char z = word.at(i);
					if(county == 0){
						if(((int)z < 48  || (int)z > 57) && i == 0){
							throw std::domain_error("File contains invalid data (time)");
						}
					}
					else if(county == 3){
						if(word.size() == 1){
							throw std::domain_error("File contains invalid data (name)");
						}
						if(!((int)z >=97 && (int)z <= 122) && !((int)z >= 65 && (int)z <= 90)){
							if((int)z != 32){
								throw std::domain_error("File contains invalid data (name)");
							}
						}						
						
					}
					else if(county == 2){
						if(word.size() > 2){
							throw std::domain_error("File contains invalid data (number)");
						}
						if((int)z < 48 || (int)z > 57 ){
							throw std::domain_error("File contains invalid data (number)");
						}												
					}
					else if(county == 1){
						if(word.size() != 3){
							throw std::domain_error("File contains invalid data (country)");
						}
						if((int)z < 65 || (int)z > 90 ){
							throw std::domain_error("File contains invalid data (country)");
						}						
					}
					
				}
			
				if(county == 0){
					double num = stod(word);
					timeArray[countyyy] = num;
				}
				else if(county == 3){
					lastnameArray[countyyy] = word;
				}
				else if(county == 2){
					unsigned int num = stoi(word);
					numberArray[countyyy] = num;
				}
				else if(county == 1){
					countryArray[countyyy] = word;
				}
				county+=1;
			}
			stream.clear();
			word = "";
			county = 0;
		}
		countyyy +=1;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	for(unsigned int i = 0; i<SIZE; i++){
		ary[i] = 0.0;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an unsigned int arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	for(unsigned int i = 0; i<SIZE; i++){
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	for(unsigned int i = 0; i<SIZE; i++){
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	double new_array[SIZE];
	double woo;
	
	for(unsigned int i = 0; i<SIZE; i++){
		new_array[i] = timeArray[i];
	}
	
	for(unsigned int i = 0; i<SIZE; i++){
		for(unsigned int j = 0; j<SIZE - 1; j++){
			if(new_array[j+1] < new_array[j]){
				woo = new_array[j];
				new_array[j] = new_array[j+1];
				new_array[j+1] = woo;
			}
			
		}
		
	}

	for(unsigned int i = 0; i<SIZE; i++){
		for(unsigned int j = 0; j<SIZE; j++){
			if(new_array[i] == timeArray[j]){
				rankArray[j] = i+1;

			}
			
		}
		
	}
	
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, filenamed who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}