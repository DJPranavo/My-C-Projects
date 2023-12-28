#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if (10<=a && a<=b && b<10000) {
		return true;
    }
	
	return false;
}

char classify_mv_range_type(int number) { 
    bool valley = false;
	bool mountain = false;
	int up = 0;
	int down = 0;
	int left = number;
	int right = 0;
	int slicer = 1;
	int count = 0;
	
	while(left>0){
		left/=10;
		count+=1;
	}
	
	for (int i = 1; i<count; i++){
		slicer = slicer*10;
	}
	
	left = number/slicer;
	number = number%slicer;
	slicer/=10;
	
	while(slicer > 0){
		right = number/slicer;
		if((valley == false) && (mountain == false)){
			if(right > left){
				mountain = true;
			}
			else if(right < left){
				valley = true;
			}
		}
		if(right < left){
			down+=1;
			up = 0;
		}
		else if(right > left){
			up += 1;
			down = 0;
		}
		if(down > 1 || up > 1){
			return 'N';
		}
		if(left == right){
			return 'N';
		}

		
		left = right;
		number %= slicer;
		slicer/=10;
	}
	
	if(valley == true){
		return 'V';
	}
	else if(mountain == true){
		return 'M';
	}
	
return 0;
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int valleycnt = 0;
	int mountaincnt = 0;
	
	for (int i=a; i<=b; i++) {
	char Digit = classify_mv_range_type(i);
		if(Digit == 'V'){
			valleycnt+=1;
		}
		else if(Digit =='M'){
			mountaincnt+=1;
		}
	}
	
	cout << "There are "<< mountaincnt << " mountain ranges and " << valleycnt << " valley ranges between " << a << " and " << b << "." << endl;

}
