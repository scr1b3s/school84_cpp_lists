#include <iostream>
#include "iter.hpp"

// Test function for integers (non-const)
void printInt(int &value)
{
	std::cout << value << " ";
}

// Test function for integers (const)
void printConstInt(const int &value)
{
	std::cout << value << " ";
}

// Test function to increment (non-const)
void incrementInt(int &value)
{
	value++;
}

// Test function for strings (const)
void printString(const std::string &str)
{
	std::cout << str << " ";
}

int main(void)
{
	// Test with integers - const reference
	int intArray[] = {1, 2, 3, 4, 5};
	std::cout << "Original array: ";
	::iter(intArray, 5, printConstInt);
	std::cout << std::endl;
	
	// Test with incrementing integers (non-const reference)
	std::cout << "After increment: ";
	::iter(intArray, 5, incrementInt);
	::iter(intArray, 5, printConstInt);
	std::cout << std::endl;
	
	// Test with strings
	std::string strArray[] = {"Hello", "World", "From", "Template"};
	std::cout << "String array: ";
	::iter(strArray, 4, printString);
	std::cout << std::endl;
	
	// Test with doubles
	double doubleArray[] = {1.1, 2.2, 3.3};
	std::cout << "Double array: ";
	::iter(doubleArray, 3, printConstInt);
	std::cout << std::endl;
	
	return 0;
}
