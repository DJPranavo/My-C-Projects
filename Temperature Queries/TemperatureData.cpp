/*
 * TemperatureData.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#include "TemperatureData.h"
#include <string>
using namespace std;

TemperatureData::TemperatureData(): id(""), year(0), month(0), temperature(0.0)
{ }

TemperatureData::TemperatureData(std::string id, int year, int month, double temperature): id(id), year(year), month(month), temperature(temperature)
{ }


TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b) {
	bool temp = false;
	if(this -> id != b.id){
		temp = id<b.id;
		return temp;
	}
	if(this -> year != b.year){
		temp = year<b.year;
		return temp;
	}
	if(this -> month != b.month){
		temp = month<b.month;
		return temp;
	}
	else{
		temp = temperature<b.temperature;
		return temp;
	}
}

