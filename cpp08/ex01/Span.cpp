#include "Span.hpp"
#include <algorithm>
#include <climits>

// Constructor
Span::Span(unsigned int N) : _maxSize(N)
{
}

// Copy constructor
Span::Span(const Span &other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

// Assignment operator
Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

// Destructor
Span::~Span(void)
{
}

// Add single number
void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw SpanException();
	_numbers.push_back(number);
}

// Find shortest span
unsigned int Span::shortestSpan(void)
{
	if (_numbers.size() <= 1)
		throw SpanException();
	
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	
	unsigned int shortest = INT_MAX;
	for (size_t i = 0; i < sorted.size() - 1; i++)
	{
		unsigned int diff = sorted[i + 1] - sorted[i];
		if (diff < shortest)
			shortest = diff;
	}
	
	return shortest;
}

// Find longest span
unsigned int Span::longestSpan(void)
{
	if (_numbers.size() <= 1)
		throw SpanException();
	
	std::vector<int>::iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
	
	return *maxIt - *minIt;
}

// Getter for size
unsigned int Span::size(void) const
{
	return _numbers.size();
}

// Getter for max size
unsigned int Span::getMaxSize(void) const
{
	return _maxSize;
}
