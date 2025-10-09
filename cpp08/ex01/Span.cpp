#include "Span.hpp"
#include <algorithm>
#include <limits>

// Orthodox Canonical Form implementation

Span::Span() : _maxSize(0) {
    // Default constructor creates span with 0 capacity
}

Span::Span(unsigned int N) : _maxSize(N) {
    // Reserve space for efficiency
    _numbers.reserve(N);
}

Span::Span(const Span& other) : _numbers(other._numbers), _maxSize(other._maxSize) {
    // Copy constructor
}

Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _numbers = other._numbers;
        _maxSize = other._maxSize;
    }
    return *this;
}

Span::~Span() {
    // Destructor - vector handles its own cleanup
}

// Core functionality implementation

void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize) {
        throw SpanFullException();
    }
    _numbers.push_back(number);
}

int Span::shortestSpan() const {
    if (_numbers.size() < 2) {
        throw SpanTooSmallException();
    }
    
    // Create a sorted copy to find adjacent differences efficiently
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());
    
    int minSpan = std::numeric_limits<int>::max();
    
    // Find minimum difference between adjacent elements
    for (size_t i = 1; i < sorted.size(); ++i) {
        int span = sorted[i] - sorted[i - 1];
        if (span < minSpan) {
            minSpan = span;
        }
    }
    
    return minSpan;
}

int Span::longestSpan() const {
    if (_numbers.size() < 2) {
        throw SpanTooSmallException();
    }
    
    // Find min and max elements
    std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
    
    return *maxIt - *minIt;
}

// Utility methods implementation

unsigned int Span::size() const {
    return _numbers.size();
}

unsigned int Span::maxSize() const {
    return _maxSize;
}

bool Span::isEmpty() const {
    return _numbers.empty();
}

bool Span::isFull() const {
    return _numbers.size() >= _maxSize;
}

// Exception implementations

const char* Span::SpanFullException::what() const throw() {
    return "Span is full - cannot add more numbers";
}

const char* Span::SpanTooSmallException::what() const throw() {
    return "Span contains less than 2 numbers - cannot calculate span";
}

const char* Span::SpanEmptyException::what() const throw() {
    return "Span is empty";
}
