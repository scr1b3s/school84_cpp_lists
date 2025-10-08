#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <iostream>

template<typename T>
class Array {
private:
    T* _elements;
    unsigned int _size;

public:
    // Default constructor - creates empty array
    Array();
    
    // Constructor with size - creates array of n elements initialized by default
    Array(unsigned int n);
    
    // Copy constructor
    Array(const Array<T>& other);
    
    // Assignment operator
    Array<T>& operator=(const Array<T>& other);
    
    // Destructor
    ~Array();
    
    // Subscript operator (const and non-const versions)
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    
    // Size member function
    unsigned int size() const;
};

#include "Array.tpp"

#endif
