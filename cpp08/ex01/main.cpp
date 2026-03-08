#include <iostream>
#include "Span.hpp"
#include <cstdlib>
#include <ctime>

int main(void)
{
	// Test basic example from subject
	std::cout << "=== Basic Test ===" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	
	// Test with empty span
	std::cout << "\n=== Exception Tests ===" << std::endl;
	Span empty = Span(5);
	try
	{
		empty.shortestSpan();
	}
	catch (const std::exception &e)
	{
		std::cout << "Empty span exception caught: " << e.what() << std::endl;
	}
	
	// Test with single element
	Span single = Span(5);
	single.addNumber(42);
	try
	{
		single.shortestSpan();
	}
	catch (const std::exception &e)
	{
		std::cout << "Single element exception caught: " << e.what() << std::endl;
	}
	
	// Test overflow
	Span full = Span(2);
	full.addNumber(1);
	full.addNumber(2);
	try
	{
		full.addNumber(3);
	}
	catch (const std::exception &e)
	{
		std::cout << "Overflow exception caught: " << e.what() << std::endl;
	}
	
	// Test with large dataset (10,000 numbers)
	std::cout << "\n=== Large Test (10,000 numbers) ===" << std::endl;
	Span large = Span(10000);
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		large.addNumber(rand() % 100000);
	}
	std::cout << "Added " << large.size() << " numbers" << std::endl;
	std::cout << "Shortest span: " << large.shortestSpan() << std::endl;
	std::cout << "Longest span: " << large.longestSpan() << std::endl;
	
	// Test with iterator range
	std::cout << "\n=== Iterator Range Test ===" << std::endl;
	Span iter = Span(10);
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	iter.addNumbers(arr, arr + 10);
	std::cout << "Added from iterator range: " << iter.size() << " elements" << std::endl;
	std::cout << "Shortest span: " << iter.shortestSpan() << std::endl;
	std::cout << "Longest span: " << iter.longestSpan() << std::endl;
	
	return 0;
}
