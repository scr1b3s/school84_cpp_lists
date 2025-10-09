#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iterator>

class Span {
private:
    std::vector<int> _numbers;
    unsigned int _maxSize;

public:
    // Orthodox Canonical Form
    Span();                                    // Default constructor
    Span(unsigned int N);                      // Parameterized constructor
    Span(const Span& other);                   // Copy constructor
    Span& operator=(const Span& other);        // Assignment operator
    ~Span();                                   // Destructor

    // Core functionality
    void addNumber(int number);
    
    // Span calculation methods
    int shortestSpan() const;
    int longestSpan() const;
    
    // Range addition method (bonus functionality)
    template<typename Iterator>
    void addRange(Iterator begin, Iterator end);
    
    // Utility methods
    unsigned int size() const;
    unsigned int maxSize() const;
    bool isEmpty() const;
    bool isFull() const;
    
    // Exception classes
    class SpanFullException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    
    class SpanTooSmallException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    
    class SpanEmptyException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

// Template method implementation (must be in header for C++98)
template<typename Iterator>
void Span::addRange(Iterator begin, Iterator end) {
    // Calculate distance to check if we have enough space
    typename std::iterator_traits<Iterator>::difference_type distance = std::distance(begin, end);
    
    if (distance < 0) {
        throw std::invalid_argument("Invalid iterator range");
    }
    
    if (_numbers.size() + static_cast<unsigned int>(distance) > _maxSize) {
        throw SpanFullException();
    }
    
    // Add all elements from the range
    _numbers.insert(_numbers.end(), begin, end);
}

#endif
