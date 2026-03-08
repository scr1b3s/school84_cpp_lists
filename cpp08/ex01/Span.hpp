#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <iostream>

class SpanException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return "Span Exception";
		}
};

class Span
{
	private:
		unsigned int _maxSize;
		std::vector<int> _numbers;
		
		// Private default constructor
		Span(void);
		
	public:
		// Constructor
		Span(unsigned int N);
		
		// Copy constructor
		Span(const Span &other);
		
		// Assignment operator
		Span &operator=(const Span &other);
		
		// Destructor
		~Span(void);
		
		// Add single number
		void addNumber(int number);
		
		// Add numbers from iterator range
		template <typename Iterator>
		void addNumbers(Iterator begin, Iterator end)
		{
			for (Iterator it = begin; it != end; ++it)
			{
				addNumber(*it);
			}
		}
		
		// Find shortest span
		unsigned int shortestSpan(void);
		
		// Find longest span
		unsigned int longestSpan(void);
		
		// Getter for size
		unsigned int size(void) const;
		
		// Getter for max size
		unsigned int getMaxSize(void) const;
};

#endif
