````markdown
# CPP07_EX02 - Array Class Template: Advanced Template Programming Concepts

## 📚 Overview

This exercise (cpp07/ex02) represents the culmination of template programming in CPP07, introducing **class templates**, **advanced memory management in templates**, **exception safety in generic code**, and **container design patterns**. It demonstrates how to create production-quality generic containers that are both safe and efficient.

---

## 🎯 Learning Objectives

By completing this exercise, you will master:
- **Class template design** and implementation
- **Template instantiation** for custom container classes
- **Memory management** in generic programming contexts
- **Exception safety** and **RAII principles** in templates
- **Orthodox Canonical Form** for template classes
- **Const-correctness** in template member functions
- **Bounds checking** and **safe container access**
- **Template file organization** (.hpp vs .tpp patterns)

---

## 🔍 Core C++ Concepts Covered

### 1. **Class Templates Deep Dive**

#### What are Class Templates?
**Class templates** are blueprints for creating classes that can work with different data types. They enable **generic container design** and **type-safe data structures** that adapt to any type at compile time.

#### Template Class vs Template Function:
```cpp
// Function template (Ex00/Ex01)
template<typename T>
void function(T param) { /* ... */ }

// Class template (Ex02)
template<typename T>
class Array {
    T* _elements;  // Type T used throughout the class
public:
    T& operator[](unsigned int index);  // Returns type T
};
```

#### Our Implementation Architecture:
```cpp
template<typename T>
class Array {
private:
    T* _elements;        // Dynamic array of type T
    unsigned int _size;  // Number of elements

public:
    Array();                              // Default constructor
    Array(unsigned int n);                // Parameterized constructor
    Array(const Array<T>& other);        // Copy constructor
    Array<T>& operator=(const Array<T>&); // Assignment operator
    ~Array();                             // Destructor
    
    T& operator[](unsigned int index);           // Non-const subscript
    const T& operator[](unsigned int index) const; // Const subscript
    unsigned int size() const;                   // Size accessor
};
```

### 2. **Template Instantiation for Classes**

#### How Class Template Instantiation Works:
```cpp
// Template definition (no code generated yet)
template<typename T>
class Array { /* ... */ };

// Template instantiation (code generated for specific types)
Array<int> intArray(10);     // Creates Array<int> class
Array<string> stringArray;   // Creates Array<string> class
Array<double> doubleArray;   // Creates Array<double> class
```

#### Generated Code Example:
```cpp
// When Array<int> is instantiated, compiler generates:
class Array_int {  // Conceptual - actual name is mangled
private:
    int* _elements;
    unsigned int _size;

public:
    Array_int();
    Array_int(unsigned int n);
    Array_int(const Array_int& other);
    Array_int& operator=(const Array_int& other);
    ~Array_int();
    
    int& operator[](unsigned int index);
    const int& operator[](unsigned int index) const;
    unsigned int size() const;
};

// Similar classes generated for Array<string>, Array<double>, etc.
```

#### Type Deduction in Class Templates:
```cpp
// C++98: Explicit type specification required
Array<int> numbers(5);        // Must specify <int>
Array<string> words(3);       // Must specify <string>

// C++17+: Class template argument deduction
// Array numbers(5);          // Would deduce Array<int> (not available in C++98)
```

### 3. **Memory Management in Template Classes**

#### Dynamic Memory Allocation Strategy:
```cpp
template<typename T>
Array<T>::Array(unsigned int n) : _elements(0), _size(n) {
    if (n > 0) {
        _elements = new T[n]();  // Value initialization
        // Creates n objects of type T, each default-initialized
    }
}
```

#### Why `new T[n]()` vs `new T[n]`:
```cpp
// Without parentheses: default initialization
int* array1 = new int[5];     // Uninitialized values (garbage)

// With parentheses: value initialization  
int* array2 = new int[5]();   // Zero-initialized values

// For our template:
T* elements = new T[n]();     // Each T() is default-constructed
// int: initialized to 0
// string: initialized to "" (empty string)
// double: initialized to 0.0
// Custom class: default constructor called
```

#### Memory Layout Analysis:
```cpp
Array<int> intArray(3);
// Memory layout:
// intArray object:
//   _elements -> [int][int][int]  (heap allocation)
//   _size = 3                     (stack, part of object)

Array<string> stringArray(2);
// Memory layout:
// stringArray object:
//   _elements -> [string][string]  (heap allocation)
//   _size = 2                      (stack, part of object)
// Each string object may have its own heap allocation for character data
```

#### Template Memory Management Challenges:
```cpp
template<typename T>
Array<T>::~Array() {
    delete[] _elements;  // Must work for any type T
    // For int: simple memory deallocation
    // For string: calls string destructor for each element, then deallocates
    // For custom class: calls custom destructor for each element
}
```

### 4. **Orthodox Canonical Form in Templates**

#### The Four Essential Methods:
```cpp
template<typename T>
class Array {
public:
    // 1. Default Constructor
    Array() : _elements(0), _size(0) {
        // Creates empty array
    }
    
    // 2. Copy Constructor
    Array(const Array<T>& other) : _elements(0), _size(other._size) {
        if (_size > 0) {
            _elements = new T[_size];
            for (unsigned int i = 0; i < _size; i++) {
                _elements[i] = other._elements[i];  // Uses T's assignment operator
            }
        }
    }
    
    // 3. Assignment Operator
    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {  // Self-assignment check
            delete[] _elements;  // Clean up existing resources
            
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
    
    // 4. Destructor
    ~Array() {
        delete[] _elements;
    }
};
```

#### Deep Copy vs Shallow Copy in Templates:
```cpp
// Shallow copy (WRONG):
template<typename T>
Array<T>::Array(const Array<T>& other) : _elements(other._elements), _size(other._size) {
    // Problem: Both objects point to same memory
    // When one destructor runs, it deletes the memory
    // When second destructor runs, it tries to delete already-deleted memory
}

// Deep copy (CORRECT):
template<typename T>
Array<T>::Array(const Array<T>& other) : _elements(0), _size(other._size) {
    if (_size > 0) {
        _elements = new T[_size];           // Allocate new memory
        for (unsigned int i = 0; i < _size; i++) {
            _elements[i] = other._elements[i];  // Copy each element
        }
    }
    // Now each object owns its own memory
}
```

### 5. **Exception Safety in Template Classes**

#### Exception Safety Levels:
1. **Basic guarantee**: No resource leaks, object in valid state
2. **Strong guarantee**: Either succeeds completely or has no effect
3. **No-throw guarantee**: Never throws exceptions

#### Our Implementation's Exception Safety:
```cpp
template<typename T>
T& Array<T>::operator[](unsigned int index) {
    if (index >= _size) {
        throw std::exception();  // Basic guarantee: no resource leaks
    }
    return _elements[index];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        // Strong guarantee implementation:
        T* newElements = 0;
        if (other._size > 0) {
            newElements = new T[other._size];  // Might throw
            for (unsigned int i = 0; i < other._size; i++) {
                newElements[i] = other._elements[i];  // Might throw
            }
        }
        
        // If we reach here, all operations succeeded
        delete[] _elements;        // Now safe to clean up
        _elements = newElements;
        _size = other._size;
    }
    return *this;
}
```

#### Exception Safety with Templates:
```cpp
class ThrowingClass {
public:
    ThrowingClass() { /* might throw */ }
    ThrowingClass(const ThrowingClass&) { /* might throw */ }
    ThrowingClass& operator=(const ThrowingClass&) { /* might throw */ }
};

Array<ThrowingClass> problematicArray(10);  // Constructor might throw
Array<ThrowingClass> copy(problematicArray); // Copy constructor might throw
copy = problematicArray;                     // Assignment might throw

// Our Array template must handle T's exceptions gracefully
```

### 6. **Const-Correctness in Templates**

#### Const Member Functions:
```cpp
template<typename T>
class Array {
public:
    // Non-const version: allows modification
    T& operator[](unsigned int index) {
        if (index >= _size) throw std::exception();
        return _elements[index];  // Returns modifiable reference
    }
    
    // Const version: read-only access
    const T& operator[](unsigned int index) const {
        if (index >= _size) throw std::exception();
        return _elements[index];  // Returns const reference
    }
    
    // Size accessor: const because it doesn't modify object
    unsigned int size() const {
        return _size;  // Can't modify _size in const function
    }
};
```

#### Const-Correctness Usage:
```cpp
void demonstrateConstCorrectness() {
    Array<int> mutableArray(5);
    const Array<int> constArray(mutableArray);  // Const copy
    
    // Non-const array:
    mutableArray[0] = 42;           // OK: calls non-const operator[]
    int value1 = mutableArray[0];   // OK: calls non-const operator[]
    
    // Const array:
    // constArray[0] = 42;          // ERROR: calls const operator[], returns const int&
    int value2 = constArray[0];     // OK: calls const operator[]
    
    // Size access:
    unsigned int size1 = mutableArray.size();  // OK: const method
    unsigned int size2 = constArray.size();    // OK: const method
}
```

### 7. **Template File Organization Patterns**

#### Traditional Approach (.hpp only):
```cpp
// Array.hpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

template<typename T>
class Array {
    // Declaration
public:
    Array();
    // ... other declarations
};

// Implementation in same file
template<typename T>
Array<T>::Array() : _elements(0), _size(0) {
    // Implementation
}

#endif
```

#### Separated Approach (.hpp + .tpp):
```cpp
// Array.hpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

template<typename T>
class Array {
    // Declaration only
};

#include "Array.tpp"  // Include implementation
#endif

// Array.tpp
#ifndef ARRAY_TPP
#define ARRAY_TPP

template<typename T>
Array<T>::Array() : _elements(0), _size(0) {
    // Implementation
}

#endif
```

#### Why .tpp Files?
- **Separation of concerns**: Interface vs implementation
- **Readability**: Cleaner header files
- **Maintainability**: Easier to modify implementation
- **Convention**: Standard practice in template-heavy codebases
- **Still header-only**: .tpp is included in .hpp, not compiled separately

---

## 🛠️ Advanced Template Programming Techniques

### 1. **Type Requirements and Constraints**

#### Implicit Requirements for Type T:
```cpp
template<typename T>
class Array {
    // T must support:
    // 1. Default construction: T() in new T[n]()
    // 2. Copy construction: T(const T&) in copy operations
    // 3. Assignment: T& operator=(const T&) in copy operations
    // 4. Destruction: ~T() in delete[] operations
};
```

#### Testing Type Requirements:
```cpp
// Valid types:
class GoodType {
public:
    GoodType() {}                                    // Default constructor
    GoodType(const GoodType&) {}                     // Copy constructor
    GoodType& operator=(const GoodType&) { return *this; } // Assignment
    ~GoodType() {}                                   // Destructor
};

Array<GoodType> goodArray(10);  // ✅ Works

// Invalid types:
class BadType {
private:
    BadType() {}  // Private default constructor
public:
    // Missing copy operations
};

// Array<BadType> badArray(10);  // ❌ Compilation error
```

### 2. **Template Specialization Possibilities**

While not required for this exercise, our design enables specialization:

#### Full Specialization Example:
```cpp
// General template
template<typename T>
class Array { /* ... */ };

// Specialization for bool (hypothetical)
template<>
class Array<bool> {
private:
    unsigned char* _data;  // Packed storage
    unsigned int _size;
    
public:
    // Specialized implementation for space efficiency
    class reference {  // Proxy class for bit access
        // ...
    };
    
    reference operator[](unsigned int index);
    // ... specialized methods
};
```

#### Partial Specialization Example:
```cpp
// Specialization for pointer types
template<typename T>
class Array<T*> {
private:
    T** _elements;
    unsigned int _size;
    
public:
    // Specialized behavior for pointer arrays
    // Maybe automatic null checking, etc.
};
```

### 3. **Template Metaprogramming Foundations**

Our Array template demonstrates basic metaprogramming concepts:

#### Compile-Time Type Information:
```cpp
template<typename T>
void analyzeType() {
    Array<T> array(1);
    
    // Type information available at compile time
    std::cout << "sizeof(T): " << sizeof(T) << std::endl;
    std::cout << "Array element size: " << sizeof(array[0]) << std::endl;
    
    // Behavior depends on T's properties
    array[0] = T();  // Uses T's default constructor
}
```

#### Type-Dependent Behavior:
```cpp
// Different behavior for different types (conceptual)
template<typename T>
void optimizedCopy(T* dest, const T* src, unsigned int count) {
    // For simple types: could use memcpy
    // For complex types: must use copy constructor
    for (unsigned int i = 0; i < count; i++) {
        dest[i] = src[i];  // Uses T's assignment operator
    }
}
```

---

## 🧪 Testing Strategies for Template Classes

### 1. **Type Compatibility Testing**

#### Testing with Different Type Categories:
```cpp
void testTypeCategories() {
    // Primitive types
    Array<int> intArray(5);
    Array<double> doubleArray(3);
    Array<char> charArray(10);
    
    // Object types
    Array<std::string> stringArray(2);
    
    // Pointer types (advanced)
    Array<int*> pointerArray(4);
    
    // Each type tests different code paths in the template
}
```

#### Testing Type-Specific Behavior:
```cpp
void testStringSpecificBehavior() {
    Array<std::string> stringArray(3);
    
    // Test string assignment
    stringArray[0] = "Hello";
    stringArray[1] = "Template";
    stringArray[2] = "World";
    
    // Test string copy semantics
    Array<std::string> copy(stringArray);
    copy[0] = "Modified";  // Should not affect original
    
    assert(stringArray[0] == "Hello");    // Original unchanged
    assert(copy[0] == "Modified");        // Copy changed
}
```

### 2. **Memory Management Testing**

#### Testing for Memory Leaks:
```cpp
void memoryLeakTest() {
    // Create many arrays to test for leaks
    for (int i = 0; i < 10000; i++) {
        Array<std::string> temp(100);
        
        // Initialize with data
        for (unsigned int j = 0; j < temp.size(); j++) {
            temp[j] = "Test string";
        }
        
        // Test copy operations
        Array<std::string> copy(temp);
        Array<std::string> assigned(50);
        assigned = temp;
        
        // Objects destroyed here - testing destructors
    }
    // If no crash, likely no major memory leaks
}
```

#### Testing Exception Safety:
```cpp
class ThrowOnCopy {
    static int copyCount;
public:
    ThrowOnCopy() {}
    ThrowOnCopy(const ThrowOnCopy&) {
        if (++copyCount > 5) throw std::runtime_error("Copy failed");
    }
};

void exceptionSafetyTest() {
    try {
        Array<ThrowOnCopy> array(10);  // Might throw during construction
        Array<ThrowOnCopy> copy(array); // Might throw during copy
    } catch (const std::exception&) {
        // Exception occurred - verify no memory leaks
        // In production code, would use tools like valgrind
    }
}
```

### 3. **Boundary Testing**

#### Edge Case Testing:
```cpp
void boundaryTesting() {
    // Zero-size arrays
    Array<int> empty;
    assert(empty.size() == 0);
    
    // Large arrays
    Array<int> large(10000);
    large[0] = 1;
    large[9999] = 2;
    assert(large[0] == 1);
    assert(large[9999] == 2);
    
    // Exception boundaries
    Array<int> test(5);
    try {
        test[5];  // Should throw
        assert(false);  // Should not reach here
    } catch (const std::exception&) {
        // Expected exception
    }
}
```

---

## 💡 Design Patterns in Template Classes

### 1. **RAII (Resource Acquisition Is Initialization)**

#### RAII Implementation:
```cpp
template<typename T>
class Array {
    T* _elements;
    
public:
    Array(unsigned int n) : _elements(n > 0 ? new T[n]() : 0), _size(n) {
        // Resource acquired in constructor
    }
    
    ~Array() {
        delete[] _elements;  // Resource released in destructor
        // Automatic cleanup when object goes out of scope
    }
};

void demonstrateRAII() {
    {
        Array<int> array(1000);  // Resource acquired
        // Use array...
    }  // array destructor called automatically, resource released
    
    // No manual cleanup needed!
}
```

### 2. **Copy-and-Swap Idiom (Advanced)**

While not implemented in our basic version, here's how it could be done:

```cpp
template<typename T>
class Array {
public:
    Array<T>& operator=(Array<T> other) {  // Pass by value!
        swap(other);  // Swap with temporary
        return *this;
        // other destructor cleans up old data
    }
    
private:
    void swap(Array<T>& other) {
        std::swap(_elements, other._elements);
        std::swap(_size, other._size);
    }
};
```

### 3. **Template Template Parameters (Advanced Concept)**

Our design could be extended for policy-based design:

```cpp
template<typename T, template<typename> class Allocator = std::allocator>
class Array {
    Allocator<T> _allocator;
    T* _elements;
    
    // Use policy for allocation strategy
};
```

---

## 🚀 Modern C++ Evolution

### C++11 Improvements:
```cpp
template<typename T>
class Array {
public:
    // Move constructor
    Array(Array<T>&& other) noexcept 
        : _elements(other._elements), _size(other._size) {
        other._elements = nullptr;
        other._size = 0;
    }
    
    // Move assignment
    Array<T>& operator=(Array<T>&& other) noexcept {
        if (this != &other) {
            delete[] _elements;
            _elements = other._elements;
            _size = other._size;
            other._elements = nullptr;
            other._size = 0;
        }
        return *this;
    }
    
    // Initializer list constructor
    Array(std::initializer_list<T> init) 
        : _elements(nullptr), _size(init.size()) {
        if (_size > 0) {
            _elements = new T[_size];
            std::copy(init.begin(), init.end(), _elements);
        }
    }
};

// Usage:
Array<int> array{1, 2, 3, 4, 5};  // Initializer list
Array<int> moved = std::move(array);  // Move construction
```

### C++17 Features:
```cpp
// Class template argument deduction
Array array(5);  // Deduces Array<int> if used with int operations

// if constexpr for type-dependent behavior
template<typename T>
void optimizedCopy(T* dest, const T* src, size_t count) {
    if constexpr (std::is_trivially_copyable_v<T>) {
        std::memcpy(dest, src, count * sizeof(T));
    } else {
        for (size_t i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    }
}
```

---

## 🏆 Evaluation Preparation - Key Concepts

### **Core Understanding Questions:**
- [ ] **Template instantiation**: How compiler generates code for each type
- [ ] **Memory management**: Why `new[]`/`delete[]` and exception safety
- [ ] **Orthodox Canonical Form**: Four essential methods and their purposes
- [ ] **Const-correctness**: Two operator[] versions and const methods
- [ ] **Deep vs shallow copy**: Implementation and importance
- [ ] **Exception safety**: Bounds checking and strong guarantees

### **Implementation Details:**
- [ ] **Default initialization**: `new T[n]()` vs `new T[n]`
- [ ] **Self-assignment**: Why check `this != &other`
- [ ] **Bounds checking**: Index validation and exception throwing
- [ ] **Template file organization**: .hpp/.tpp separation rationale
- [ ] **Type requirements**: What T must support for Array<T> to work

### **Advanced Topics:**
- [ ] **RAII principles**: Automatic resource management
- [ ] **Exception safety levels**: Basic, strong, no-throw guarantees
- [ ] **Template specialization**: How design enables customization
- [ ] **Performance implications**: Template instantiation costs
- [ ] **Modern evolution**: C++11/17 improvements to this pattern

---

*This comprehensive guide covers all aspects of class template design, providing the knowledge needed to understand and implement production-quality generic containers in C++.*

````
