#ifndef ARRAY_TPP
#define ARRAY_TPP

// Default constructor - creates empty array
template<typename T>
Array<T>::Array() : _elements(0), _size(0) {
}

// Constructor with size - creates array of n elements initialized by default
template<typename T>
Array<T>::Array(unsigned int n) : _elements(0), _size(n) {
    if (n > 0) {
        _elements = new T[n]();  // Note the () for value initialization
        // Elements are default-initialized by new T[n]()
    }
}

// Copy constructor
template<typename T>
Array<T>::Array(const Array<T>& other) : _elements(0), _size(other._size) {
    if (_size > 0) {
        _elements = new T[_size];
        for (unsigned int i = 0; i < _size; i++) {
            _elements[i] = other._elements[i];
        }
    }
}

// Assignment operator
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {  // Self-assignment check
        // Clean up existing memory
        delete[] _elements;
        
        // Copy new data
        _size = other._size;
        if (_size > 0) {
            _elements = new T[_size];
            for (unsigned int i = 0; i < _size; i++) {
                _elements[i] = other._elements[i];
            }
        } else {
            _elements = 0;
        }
    }
    return *this;
}

// Destructor
template<typename T>
Array<T>::~Array() {
    delete[] _elements;
}

// Subscript operator (non-const version)
template<typename T>
T& Array<T>::operator[](unsigned int index) {
    if (index >= _size) {
        throw std::exception();
    }
    return _elements[index];
}

// Subscript operator (const version)
template<typename T>
const T& Array<T>::operator[](unsigned int index) const {
    if (index >= _size) {
        throw std::exception();
    }
    return _elements[index];
}

// Size member function
template<typename T>
unsigned int Array<T>::size() const {
    return _size;
}

#endif
