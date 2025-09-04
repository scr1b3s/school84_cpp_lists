#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <iostream>

struct Data
{
	int			id;
	std::string	name;
	double		value;
	bool		active;

	// Constructor for easy initialization
	Data();
	Data(int id, const std::string& name, double value, bool active);

	// Display method for testing
	void print() const;

	// Comparison operator for testing
	bool operator==(const Data& other) const;
};

#endif
