````markdown
# CPP07 Module - Templates and Generic Programming: Complete Capstone Guide

## 📚 Module Overview

**CPP07** introduces **templates and generic programming** in C++, covering the full spectrum from basic function templates to advanced class template design. This module demonstrates C++'s powerful template system and establishes the foundation for understanding the Standard Template Library (STL) and modern C++ programming.

---

## 🎯 Module Learning Objectives

By completing CPP07, you will master:
- **Template fundamentals** and syntax
- **Generic programming principles** and best practices
- **Function templates** with multiple parameter types
- **Class templates** and container design
- **Template instantiation** and compilation model
- **Memory management** in template contexts
- **Exception safety** in generic code
- **Template file organization** and best practices

---

## 📁 Exercise Progression and Interconnected Concepts

| Exercise | Focus | Key Concepts | Foundation For |
|----------|-------|-------------|----------------|
| **ex00** | Function Templates | Basic template syntax, type deduction | All subsequent template work |
| **ex01** | Function Pointers + Templates | Template function parameters, const-correctness | STL algorithms, function objects |
| **ex02** | Class Templates | Template classes, memory management, RAII | STL containers, advanced templates |

### **Progressive Complexity Architecture:**
```
Ex00: Template Basics → Ex01: Template Functions → Ex02: Template Classes
    ↓                      ↓                           ↓
Type System           Algorithm Patterns          Container Design
    ↓                      ↓                           ↓
Generic Functions     Function Objects            RAII & Exceptions
    ↓                      ↓                           ↓
STL Foundation        STL Algorithms             STL Containers
```

---

## 🔄 Exercise 00: Function Templates Foundation

### **Core Achievement: Generic Programming Introduction**

#### **Technical Mastery:**
```cpp
template<typename T>
void swap(T& a, T& b) {
    T temp = a; a = b; b = temp;
}

template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;  // Second if equal
}

template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;  // Second if equal
}
```

#### **Key Learning Outcomes:**
- **Template syntax**: `template<typename T>` declaration
- **Type deduction**: Compiler automatically determines T
- **Generic algorithms**: Same code works with different types
- **Type requirements**: Implicit constraints on T
- **Header-only implementation**: Templates must be in headers

#### **Real-World Foundation:**
```cpp
// Ex00 principles enable:
std::swap(a, b);           // Standard library equivalent
std::min(x, y);            // Standard library equivalent  
std::max(x, y);            // Standard library equivalent
std::sort(begin, end);     // Uses comparison operators
std::find(begin, end, val); // Uses equality operators
```

---

## 🔄 Exercise 01: Algorithm Templates and Function Objects

### **Core Achievement: Generic Algorithm Design**

#### **Technical Mastery:**
```cpp
template<typename T, typename Func>
void iter(T* array, int length, Func function) {
    for (int i = 0; i < length; i++) {
        function(array[i]);
    }
}
```

#### **Key Learning Outcomes:**
- **Multiple template parameters**: Independent type deduction
- **Function parameter templates**: Generic callable objects
- **Const-correctness**: Natural handling of const/non-const
- **Algorithm patterns**: Iterator-like behavior
- **Type flexibility**: Function pointers, template functions, functors

#### **Advanced Design Patterns:**
```cpp
// Pattern: Generic Algorithm + Customizable Operation
template<typename Container, typename Predicate>
bool all_of(const Container& c, Predicate pred) {
    for (const auto& element : c) {
        if (!pred(element)) return false;
    }
    return true;
}

// Usage flexibility:
iter(array, size, regularFunction);     // Function pointer
iter(array, size, templateFunc<int>);   // Template function
iter(array, size, [](int x) { /*...*/ }); // Lambda (C++11+)
```

#### **Real-World Foundation:**
```cpp
// Ex01 principles enable:
std::for_each(begin, end, function);    // STL algorithm equivalent
std::transform(begin, end, out, func);  // Transformation algorithms
std::find_if(begin, end, predicate);    // Conditional searching
std::count_if(begin, end, condition);   // Conditional counting
```

---

## 🔄 Exercise 02: Class Templates and Container Design

### **Core Achievement: Generic Container Implementation**

#### **Technical Mastery:**
```cpp
template<typename T>
class Array {
private:
    T* _elements;
    unsigned int _size;

public:
    Array();                              // Default constructor
    Array(unsigned int n);                // Parameterized constructor
    Array(const Array<T>& other);        // Copy constructor
    Array<T>& operator=(const Array<T>&); // Assignment operator
    ~Array();                             // Destructor
    
    T& operator[](unsigned int index);           // Non-const access
    const T& operator[](unsigned int index) const; // Const access
    unsigned int size() const;                   // Size accessor
};
```

#### **Key Learning Outcomes:**
- **Class template design**: Generic container architecture
- **Orthodox Canonical Form**: Template-aware RAII implementation
- **Memory management**: Dynamic allocation with templates
- **Exception safety**: Bounds checking and resource management
- **Const-correctness**: Template member function design
- **Template file organization**: .hpp/.tpp separation

#### **Advanced Container Concepts:**
```cpp
// Pattern: RAII + Exception Safety + Generic Types
template<typename T>
class SafeContainer {
    T* _data;
    size_t _size, _capacity;
    
public:
    // Strong exception safety guarantee
    void push_back(const T& element) {
        if (_size == _capacity) {
            T* newData = new T[_capacity * 2];  // Might throw
            for (size_t i = 0; i < _size; ++i) {
                newData[i] = _data[i];           // Might throw
            }
            delete[] _data;                      // Only after success
            _data = newData;
            _capacity *= 2;
        }
        _data[_size++] = element;
    }
};
```

#### **Real-World Foundation:**
```cpp
// Ex02 principles enable:
std::vector<T>         // Dynamic array container
std::array<T, N>       // Fixed-size array container
std::deque<T>          // Double-ended queue
std::list<T>           // Doubly-linked list
std::map<K, V>         // Associative container
std::unique_ptr<T>     // Smart pointer container
```

---

## 🔗 Interconnected Template Concepts Across Exercises

### 1. **Template Type System Evolution**

#### **Ex00: Basic Type Deduction**
```cpp
template<typename T>
T min(T a, T b) { return (a < b) ? a : b; }

// T deduced from arguments:
min(1, 2);         // T = int
min(1.5, 2.7);     // T = double
min("a", "b");     // T = const char*
```

#### **Ex01: Multi-Parameter Type Deduction**
```cpp
template<typename T, typename Func>
void iter(T* array, int length, Func function);

// Independent deduction:
// T from array type, Func from function type
iter(intArray, 5, printInt);        // T=int, Func=void(*)(int)
iter(stringArray, 3, printString);  // T=string, Func=void(*)(const string&)
```

#### **Ex02: Explicit Template Instantiation**
```cpp
template<typename T>
class Array { /*...*/ };

// Explicit type specification required:
Array<int> numbers(10);      // Must specify T=int
Array<string> words(5);      // Must specify T=string
```

### 2. **Memory Management Progression**

#### **Ex00: No Dynamic Memory**
```cpp
template<typename T>
void swap(T& a, T& b) {
    T temp = a;  // Stack-based temporary
    a = b;       // Assignment operations
    b = temp;    // No memory management needed
}
```

#### **Ex01: External Memory Management**
```cpp
template<typename T, typename Func>
void iter(T* array, int length, Func function) {
    // Works with externally managed arrays
    // No ownership or lifetime responsibility
    for (int i = 0; i < length; i++) {
        function(array[i]);  // Just processes elements
    }
}
```

#### **Ex02: Full Memory Ownership**
```cpp
template<typename T>
class Array {
    T* _elements;  // Owns dynamic memory
public:
    Array(unsigned int n) : _elements(new T[n]()), _size(n) {}
    ~Array() { delete[] _elements; }  // RAII cleanup
    
    // Deep copy semantics
    Array(const Array& other) { /* allocate and copy */ }
    Array& operator=(const Array& other) { /* reallocate and copy */ }
};
```

### 3. **Exception Safety Evolution**

#### **Ex00: Exception Neutral**
```cpp
template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;  // Uses T's operators
    // If T's operators throw, function propagates exception
    // No resources to clean up
}
```

#### **Ex01: Exception Transparent**
```cpp
template<typename T, typename Func>
void iter(T* array, int length, Func function) {
    for (int i = 0; i < length; i++) {
        function(array[i]);  // If function throws, loop stops
        // No resources owned, no cleanup needed
    }
}
```

#### **Ex02: Exception Safe**
```cpp
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        T* newElements = new T[other._size];  // Might throw
        for (unsigned int i = 0; i < other._size; i++) {
            newElements[i] = other._elements[i];  // Might throw
        }
        // Only modify object state after all operations succeed
        delete[] _elements;
        _elements = newElements;
        _size = other._size;
    }
    return *this;
}
```

### 4. **Const-Correctness Maturation**

#### **Ex00: Basic Const Handling**
```cpp
template<typename T>
T min(T a, T b) {  // Pass by value - const irrelevant for parameters
    return (a < b) ? a : b;
}
```

#### **Ex01: Const-Aware Templates**
```cpp
template<typename T, typename Func>
void iter(T* array, int length, Func function) {
    // T can be 'int' or 'const int'
    // Func must be compatible with T's const-ness
    for (int i = 0; i < length; i++) {
        function(array[i]);  // Automatic const propagation
    }
}
```

#### **Ex02: Complete Const Interface**
```cpp
template<typename T>
class Array {
public:
    T& operator[](unsigned int index) {              // Non-const object
        return _elements[index];                      // Returns mutable reference
    }
    
    const T& operator[](unsigned int index) const {  // Const object
        return _elements[index];                      // Returns const reference
    }
    
    unsigned int size() const {                       // Doesn't modify object
        return _size;
    }
};
```

---

## 🎨 Design Patterns and Principles Demonstrated

### 1. **Generic Programming Patterns**

#### **Algorithm + Policy Pattern (Ex01 Foundation):**
```cpp
// Algorithm: iteration
// Policy: what to do with each element
template<typename Container, typename Operation>
void for_each(Container& container, Operation op) {
    for (auto& element : container) {
        op(element);  // Policy determines behavior
    }
}

// Usage with different policies:
for_each(numbers, [](int& x) { x *= 2; });        // Doubling policy
for_each(words, [](string& s) { s += "!"; });     // Append policy
```

#### **Template Template Parameters (Advanced):**
```cpp
// Building on Ex02 principles:
template<typename T, template<typename> class Container = Array>
class GenericProcessor {
    Container<T> _data;
public:
    void process() { /* work with any container type */ }
};

GenericProcessor<int, Array> processor1;     // Uses our Array
GenericProcessor<int, std::vector> processor2; // Uses std::vector
```

### 2. **RAII and Resource Management Patterns**

#### **RAII Evolution Through Exercises:**
```cpp
// Ex00: No resources to manage
template<typename T>
void swap(T& a, T& b) { /* stack only */ }

// Ex01: Works with externally managed resources
template<typename T, typename Func>
void iter(T* array, int length, Func function) { /* uses external resources */ }

// Ex02: Full resource ownership
template<typename T>
class Array {
    T* _elements;  // Owned resource
public:
    Array(unsigned int n) : _elements(new T[n]()) {}    // Acquire
    ~Array() { delete[] _elements; }                     // Release
    // Copy operations ensure proper resource sharing
};
```

#### **Exception Safety Patterns:**
```cpp
// Strong Exception Safety (Ex02 principle):
template<typename T>
void reallocate(T*& data, size_t& size, size_t newSize) {
    T* newData = new T[newSize];  // Acquire new resource
    
    try {
        for (size_t i = 0; i < std::min(size, newSize); ++i) {
            newData[i] = data[i];  // Copy (might throw)
        }
    } catch (...) {
        delete[] newData;  // Clean up on failure
        throw;             // Re-throw exception
    }
    
    delete[] data;  // Release old resource only after success
    data = newData;
    size = newSize;
}
```

### 3. **Template Metaprogramming Foundations**

#### **Type Traits (Building on Our Work):**
```cpp
// Ex00 enables basic type manipulation:
template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

// Ex01 enables behavior customization:
template<typename T>
void process(T& value) {
    if (is_pointer<T>::value) {
        // Handle pointer types specially
    } else {
        // Handle regular types
    }
}
```

#### **SFINAE (Substitution Failure Is Not An Error):**
```cpp
// Advanced technique enabled by our template understanding:
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
process_number(T value) {
    // Only instantiated for integral types
    std::cout << "Processing integer: " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
process_number(T value) {
    // Only instantiated for floating point types
    std::cout << "Processing float: " << value << std::endl;
}
```

---

## 🧪 Comprehensive Testing Strategies Across Module

### 1. **Progressive Testing Complexity**

#### **Ex00: Basic Type Testing**
```cpp
void testBasicTypes() {
    // Primitive types
    int a = 1, b = 2;
    ::swap(a, b);
    assert(a == 2 && b == 1);
    
    // Object types
    std::string s1 = "hello", s2 = "world";
    std::string result = ::min(s1, s2);
    assert(result == "hello");  // Lexicographic comparison
}
```

#### **Ex01: Function Compatibility Testing**
```cpp
void testFunctionCompatibility() {
    int array[] = {1, 2, 3, 4, 5};
    
    // Function pointer
    ::iter(array, 5, printFunction);
    
    // Template function
    ::iter(array, 5, templateFunction<int>);
    
    // Const vs non-const
    const int constArray[] = {1, 2, 3};
    ::iter(constArray, 3, constFunction);  // Must use const-compatible function
}
```

#### **Ex02: Container Integrity Testing**
```cpp
void testContainerIntegrity() {
    Array<std::string> original(3);
    original[0] = "test";
    
    // Deep copy verification
    Array<std::string> copy(original);
    copy[0] = "modified";
    assert(original[0] == "test");      // Original unchanged
    assert(copy[0] == "modified");      // Copy changed
    
    // Exception safety
    try {
        original[10];  // Out of bounds
        assert(false); // Should not reach
    } catch (const std::exception&) {
        // Expected exception
    }
    
    // Object still valid after exception
    assert(original.size() == 3);
    assert(original[0] == "test");
}
```

### 2. **Integration Testing Across Exercises**

#### **Cross-Exercise Compatibility:**
```cpp
void integrationTest() {
    // Create container using Ex02
    Array<int> numbers(10);
    for (unsigned int i = 0; i < numbers.size(); i++) {
        numbers[i] = i;
    }
    
    // Process with Ex01 algorithm
    ::iter(&numbers[0], numbers.size(), [](int& x) { x *= 2; });
    
    // Verify with Ex00 functions
    assert(::max(numbers[0], numbers[1]) == numbers[1]);
    assert(::min(numbers[8], numbers[9]) == numbers[8]);
}
```

### 3. **Performance and Scalability Testing**

#### **Template Instantiation Performance:**
```cpp
void performanceTest() {
    const int SIZE = 100000;
    
    // Test Ex02 container performance
    Array<int> largeArray(SIZE);
    
    auto start = std::clock();
    
    // Fill array
    for (unsigned int i = 0; i < largeArray.size(); i++) {
        largeArray[i] = i;
    }
    
    // Process with Ex01 algorithm
    ::iter(&largeArray[0], largeArray.size(), [](int& x) { x *= 2; });
    
    auto end = std::clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Processed " << SIZE << " elements in " << duration << " seconds" << std::endl;
    
    // Verify template instantiation efficiency
    // Should be comparable to hand-written loops
}
```

---

## 🚀 Modern C++ Evolution and Future Applications

### **C++11 Enhancements:**

#### **Move Semantics (Ex02 Enhancement):**
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
        std::swap(_elements, other._elements);
        std::swap(_size, other._size);
        return *this;
    }
};
```

#### **Variadic Templates (Ex01 Enhancement):**
```cpp
template<typename Func, typename... Args>
void for_each_arg(Func f, Args&&... args) {
    (f(std::forward<Args>(args)), ...);  // C++17 fold expression
}

// Usage:
for_each_arg(print, 1, 2.5, "hello", std::string("world"));
```

#### **Lambda Integration (All Exercises):**
```cpp
// Enhanced versions work seamlessly with lambdas:
Array<int> numbers(5);
iter(&numbers[0], numbers.size(), [](int& x) { x *= 2; });

auto maxElement = [](const auto& a, const auto& b) { return max(a, b); };
```

### **C++14/17/20 Features:**

#### **Concepts (C++20):**
```cpp
template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

template<Comparable T>
T min(T a, T b) {
    return (a < b) ? a : b;
}
```

#### **Ranges (C++20):**
```cpp
// Our iter function concept evolved into:
std::ranges::for_each(container, function);
std::ranges::transform(input, output, function);
std::ranges::sort(container);
```

---

## 🏆 Complete Module Evaluation Preparation

### **Fundamental Concepts Mastery:**

#### **Template Mechanics:**
- [ ] **Template syntax**: `template<typename T>` vs `template<class T>`
- [ ] **Template instantiation**: When and how compiler generates code
- [ ] **Type deduction**: Automatic vs explicit template arguments
- [ ] **Template compilation**: Two-phase compilation model
- [ ] **Header requirements**: Why templates must be in headers

#### **Generic Programming Principles:**
- [ ] **Algorithm design**: Separation of algorithm from data type
- [ ] **Type requirements**: Implicit vs explicit constraints
- [ ] **Code reuse**: One template, multiple types
- [ ] **Performance**: Zero-cost abstraction concept
- [ ] **Flexibility**: Function objects, lambdas, function pointers

#### **Memory and Resource Management:**
- [ ] **RAII principles**: Constructor acquires, destructor releases
- [ ] **Exception safety**: Basic, strong, and no-throw guarantees
- [ ] **Deep vs shallow copy**: Implementation and consequences
- [ ] **Self-assignment**: Why and how to handle
- [ ] **Resource leaks**: Prevention through proper design

### **Implementation Skills:**

#### **Function Templates (Ex00):**
- [ ] **Basic template syntax**: Parameter declaration and usage
- [ ] **Type deduction**: How compiler determines template arguments
- [ ] **Global scope**: Using `::` to avoid conflicts
- [ ] **Type constraints**: What operations types must support
- [ ] **Template specialization**: Concept and basic examples

#### **Algorithm Templates (Ex01):**
- [ ] **Multiple template parameters**: Independent type deduction
- [ ] **Function parameter templates**: Accepting any callable
- [ ] **Const-correctness**: Natural propagation through templates
- [ ] **Iterator patterns**: Foundation for STL algorithms
- [ ] **Function object support**: Functors, lambdas, function pointers

#### **Class Templates (Ex02):**
- [ ] **Class template declaration**: Template class syntax
- [ ] **Orthodox Canonical Form**: Four essential methods for templates
- [ ] **Member function templates**: Implementation in .tpp files
- [ ] **Const member functions**: Multiple operator[] versions
- [ ] **Exception safety**: Bounds checking and resource management

### **Advanced Understanding:**

#### **Design Patterns:**
- [ ] **RAII**: Resource management through object lifetime
- [ ] **Template Template Parameters**: Higher-order templates
- [ ] **Policy-based design**: Customizable behavior through templates
- [ ] **SFINAE**: Basic understanding of substitution rules
- [ ] **Type traits**: Compile-time type information

#### **Performance Considerations:**
- [ ] **Template instantiation cost**: Code bloat vs flexibility
- [ ] **Inline optimization**: Template functions and performance
- [ ] **Memory layout**: Template classes and object size
- [ ] **Compilation time**: Template complexity impact
- [ ] **Zero-cost abstraction**: Runtime performance equivalence

#### **Modern Connections:**
- [ ] **STL foundation**: How our templates relate to standard library
- [ ] **Move semantics**: C++11 enhancements to template classes
- [ ] **Concepts**: C++20 template constraint mechanisms
- [ ] **Ranges**: Evolution of algorithm design patterns
- [ ] **Metaprogramming**: Compile-time computation foundations

### **Practical Applications:**

#### **Real-World Usage:**
- [ ] **Container design**: std::vector, std::array principles
- [ ] **Algorithm design**: std::for_each, std::transform patterns
- [ ] **Smart pointers**: std::unique_ptr, std::shared_ptr design
- [ ] **Function objects**: std::function, lambda integration
- [ ] **Type safety**: Compile-time error prevention

#### **Problem-Solving Skills:**
- [ ] **Template error diagnosis**: Understanding compilation errors
- [ ] **Type requirement analysis**: What constraints are needed
- [ ] **Exception safety design**: Handling failures gracefully
- [ ] **Performance optimization**: Template-specific techniques
- [ ] **Code organization**: Header/implementation separation

---

## 📖 Study Roadmap for Mastery

### **Week 1: Foundation Consolidation**
1. **Review Ex00**: Template syntax, type deduction, global scope
2. **Practice variations**: Different types, custom classes
3. **Understand compilation**: Why templates need headers
4. **Explore constraints**: What makes types compatible

### **Week 2: Algorithm Understanding**
1. **Review Ex01**: Function parameter templates, const-correctness
2. **Design alternatives**: Different approaches and trade-offs
3. **Integration practice**: Combining with Ex00 functions
4. **Real-world connections**: STL algorithm parallels

### **Week 3: Container Mastery**
1. **Review Ex02**: Class templates, memory management, RAII
2. **Exception safety**: Understanding all guarantee levels
3. **Performance analysis**: Template instantiation costs
4. **Advanced features**: Move semantics, modern improvements

### **Week 4: Integration and Advanced Topics**
1. **Cross-exercise integration**: Using all three together
2. **Design pattern recognition**: RAII, policy-based design
3. **Modern C++ preparation**: Concepts, ranges, metaprogramming
4. **Evaluation simulation**: Question practice and code review

---

*This comprehensive capstone guide provides complete coverage of template programming concepts, demonstrating how CPP07 establishes the foundation for advanced C++ programming and modern template metaprogramming techniques.*

````
