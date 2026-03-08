#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main(void)
{
	// Test with vector
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	
	std::cout << "Vector test:" << std::endl;
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 10);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	// Test with list
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);
	lst.push_back(50);
	
	std::cout << "\nList test:" << std::endl;
	try
	{
		std::list<int>::iterator it = easyfind(lst, 30);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	try
	{
		std::list<int>::iterator it = easyfind(lst, 100);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	// Test with duplicate values (should find first)
	std::vector<int> dupVec;
	dupVec.push_back(5);
	dupVec.push_back(10);
	dupVec.push_back(5);
	dupVec.push_back(15);
	
	std::cout << "\nDuplicate test:" << std::endl;
	try
	{
		std::vector<int>::iterator it = easyfind(dupVec, 5);
		std::cout << "Found first 5 at position: " << (it - dupVec.begin()) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}
