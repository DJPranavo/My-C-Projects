#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node(): data(TemperatureData()), next(nullptr)
{ } 

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature): data(TemperatureData(id, year, month, temperature)), next(nullptr) 
{ }

bool Node::operator<(const Node& b) {
	return this->data < b.data;
}
