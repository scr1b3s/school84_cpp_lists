````markdown
# CPP07_EX00 - Function Templates and Generic Programming

## 📚 Overview

This exercise (cpp07/ex00) introduces **function templates**, the foundation of **generic programming** in C++. It demonstrates how to write type-independent code that can work with any data type, providing the building blocks for creating reusable, efficient, and type-safe generic algorithms.

---

## 🎯 Learning Objectives

By completing this exercise, you will understand:
- **Function template syntax** and declaration
- **Template instantiation** and type deduction
- **Generic programming principles** and benefits
- **Type requirements** and constraints for templates
- **Template specialization** concepts
- **Header-only template implementation**
- **Namespace resolution** with templates
- **Template compilation model** and linking

---

## 🔍 Key C++ Concepts Covered

### 1. **Function Templates Deep Dive**

#### What are Function Templates?
**Function templates** are blueprints for creating functions that can operate on different data types. They enable **generic programming** by allowing you to write a single function definition that works with multiple types.

#### Template Syntax:
```cpp
template<typename T>
return_type function_name(parameters_with_T) {
    // Function implementation using type T
}
```

#### Our Implementation:
```cpp
template<typename T>
void swap(T& a, T& b) {
    T temp = a;    // Create temporary of type T
    a = b;         // Assign b to a
    b = temp;      // Assign temp to b
}

template<typename T>
T min(T a, T b) {
    if (a < b)     // Requires T to support < operator
        return a;
    return b;      // Return second if equal (per requirement)
}

template<typename T>
T max(T a, T b) {
    if (a > b)     // Requires T to support > operator
        return a;
    return b;      // Return second if equal (per requirement)
}
```

#### Template vs Regular Functions:

| Aspect | Regular Function | Function Template |
|--------|------------------|-------------------|
| **Type Specificity** | Fixed types | Generic types |
| **Code Reuse** | One per type | One for all types |
| **Performance** | Direct call | Instantiated per type |
| **Compilation** | Once | Per type used |
| **Type Safety** | Static | Static (after instantiation) |

### 2. **Template Instantiation Process**

#### Automatic Type Deduction:
```cpp
int a = 5, b = 10;
::swap(a, b);  // Compiler deduces T = int, creates swap<int>

std::string s1 = "hello", s2 = "world";
::swap(s1, s2);  // Compiler deduces T = std::string, creates swap<std::string>
```

#### Compilation Process:
```cpp
// Step 1: Template definition (no code generated yet)
template<typename T>
void swap(T& a, T& b) { /* ... */ }

// Step 2: Template instantiation (code generated for each type)
// When swap(int&, int&) is called:
void swap<int>(int& a, int& b) {
    int temp = a;  // T replaced with int
    a = b;
    b = temp;
}

// When swap(std::string&, std::string&) is called:
void swap<std::string>(std::string& a, std::string& b) {
    std::string temp = a;  // T replaced with std::string
    a = b;
    b = temp;
}
```

#### Template Instantiation Rules:
1. **On-demand instantiation**: Code generated only when template is used
2. **Per-type instantiation**: Separate function created for each type
3. **Identical instantiations**: Compiler merges identical instantiations
4. **Link-time optimization**: Unused instantiations may be removed

### 3. **Type Requirements and Constraints**

#### Implicit Requirements:
Our templates require types to support certain operations:

```cpp
template<typename T>
void swap(T& a, T& b) {
    T temp = a;    // Requires: T has copy constructor
    a = b;         // Requires: T has copy assignment operator
    b = temp;      // Requires: T has copy assignment operator
}

template<typename T>
T min(T a, T b) {
    if (a < b)     // Requires: T has operator< defined
        return a;  // Requires: T has copy constructor
    return b;      // Requires: T has copy constructor
}
```

#### Type Compatibility Examples:

##### ✅ **Compatible Types:**
```cpp
// Built-in types
int, float, double, char
// Reason: Have copy operations and comparison operators

// std::string
std::string s1, s2;
// Reason: Has copy constructor, assignment, and comparison operators

// Custom types with proper operators
class Point {
    int x, y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}  // Copy constructor
    Point& operator=(const Point& other) {                 // Assignment operator
        x = other.x; y = other.y; return *this;
    }
    bool operator<(const Point& other) const {             // Comparison operator
        return (x + y) < (other.x + other.y);
    }
    bool operator>(const Point& other) const {             // Comparison operator
        return (x + y) > (other.x + other.y);
    }
};
```

##### ❌ **Incompatible Types:**
```cpp
// Arrays (no copy assignment)
int arr1[5], arr2[5];
// swap(arr1, arr2);  // ERROR: Cannot assign arrays

// Types without comparison operators
struct NoCompare {
    int value;
    // No operator< or operator> defined
};
// min(NoCompare{1}, NoCompare{2});  // ERROR: No operator< found

// Types with only const methods
class ReadOnly {
    int value;
public:
    ReadOnly(int v) : value(v) {}
    // No copy assignment operator
    ReadOnly& operator=(const ReadOnly&) = delete;
};
// swap(ReadOnly{1}, ReadOnly{2});  // ERROR: No assignment operator
```

### 4. **Template Compilation Model**

#### Header-Only Implementation:
Templates must be defined in header files because:

```cpp
// why_headers_only.cpp - WRONG APPROACH
// template_functions.h
template<typename T>
void swap(T& a, T& b);  // Declaration only

// template_functions.cpp  
template<typename T>
void swap(T& a, T& b) {  // Definition in .cpp file
    T temp = a; a = b; b = temp;
}

// main.cpp
#include "template_functions.h"
int main() {
    int a = 1, b = 2;
    swap(a, b);  // ERROR: No definition available for swap<int>
}
```

#### Correct Header-Only Approach:
```cpp
// whatever.hpp - CORRECT APPROACH
#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template<typename T>
void swap(T& a, T& b) {  // Definition in header
    T temp = a;
    a = b;
    b = temp;
}

#endif

// main.cpp
#include "whatever.hpp"
int main() {
    int a = 1, b = 2;
    swap(a, b);  // OK: Definition available for instantiation
}
```

#### Compilation Process Detailed:
```cpp
// Phase 1: Template parsing (syntax checking only)
template<typename T>
void swap(T& a, T& b) {
    T temp = a;  // Parsed but not compiled
    a = b;       // Syntax checked but no code generated
    b = temp;
}

// Phase 2: Template instantiation (when used)
int x = 5, y = 10;
swap(x, y);  // Triggers instantiation of swap<int>

// Compiler generates:
void swap<int>(int& a, int& b) {
    int temp = a;  // Now compiled with T = int
    a = b;
    b = temp;
}
```

### 5. **Namespace Resolution with Templates**

#### Global Scope Resolution:
```cpp
// main.cpp
#include <algorithm>  // Contains std::swap, std::min, std::max
#include "whatever.hpp"

int main() {
    int a = 2, b = 3;
    
    // Using our template functions (global scope)
    ::swap(a, b);      // Calls our swap<int>
    ::min(a, b);       // Calls our min<int>
    ::max(a, b);       // Calls our max<int>
    
    // Using standard library functions
    std::swap(a, b);   // Calls std::swap<int>
    std::min(a, b);    // Calls std::min<int>
    std::max(a, b);    // Calls std::max<int>
    
    // Without explicit scope (potential ambiguity)
    // swap(a, b);     // Could be ambiguous if both are visible
}
```

#### Why Use Global Scope (`::`) ?
1. **Explicit selection**: Clear which function is being called
2. **Avoid conflicts**: Prevents ambiguity with standard library
3. **École 42 requirement**: Demonstrates understanding of scope resolution
4. **Testing specificity**: Ensures we're testing our implementation

### 6. **Advanced Template Concepts**

#### Template Argument Deduction:
```cpp
template<typename T>
void func(T param) { /* ... */ }

// Deduction examples
func(42);        // T deduced as int
func(3.14f);     // T deduced as float
func("hello");   // T deduced as const char*

std::string s = "world";
func(s);         // T deduced as std::string
```

#### Template Specialization (Advanced):
```cpp
// Primary template
template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

// Explicit specialization for const char*
template<>
const char* min<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) < 0) ? a : b;  // Use strcmp for C-strings
}
```

#### Function Template Overloading:
```cpp
// Different parameter patterns
template<typename T>
void process(T value) { /* Version 1 */ }

template<typename T>
void process(T* pointer) { /* Version 2 - for pointers */ }

template<typename T>
void process(T& reference) { /* Version 3 - for references */ }

// Compiler selects best match based on argument type
```

---

## 🛠️ Practical Applications and Real-World Usage

### 1. **Standard Library Examples**

Our templates are similar to standard library functions:

#### std::swap (C++98):
```cpp
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

#### std::min/std::max (C++98):
```cpp
template<typename T>
const T& min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

template<typename T>
const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
}
```

#### Modern Improvements (C++11+):
```cpp
// Perfect forwarding and move semantics
template<typename T>
void swap(T& a, T& b) noexcept {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// Initializer list support
template<typename T>
constexpr const T& min(std::initializer_list<T> ilist) {
    return *std::min_element(ilist.begin(), ilist.end());
}
```

### 2. **Generic Algorithms**

#### Sorting Algorithm Template:
```cpp
template<typename T>
void bubble_sort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                ::swap(arr[j], arr[j + 1]);  // Using our template!
            }
        }
    }
}

// Usage
int numbers[] = {64, 34, 25, 12, 22, 11, 90};
bubble_sort(numbers, 7);

std::string words[] = {"banana", "apple", "cherry"};
bubble_sort(words, 3);
```

#### Generic Container Operations:
```cpp
template<typename T>
T find_maximum(const T container[], int size) {
    T maximum = container[0];
    for (int i = 1; i < size; i++) {
        maximum = ::max(maximum, container[i]);  // Using our template!
    }
    return maximum;
}
```

### 3. **Mathematical Operations**

#### Generic Mathematical Functions:
```cpp
template<typename T>
T absolute_value(T value) {
    return (value < T(0)) ? -value : value;
}

template<typename T>
T power(T base, int exponent) {
    T result = T(1);
    for (int i = 0; i < exponent; i++) {
        result = result * base;
    }
    return result;
}

template<typename T>
T interpolate(T start, T end, double factor) {
    return start + (end - start) * factor;
}
```

### 4. **Data Structure Templates**

#### Generic Stack Implementation:
```cpp
template<typename T>
class Stack {
private:
    T* data;
    int capacity;
    int top_index;

public:
    Stack(int size) : capacity(size), top_index(-1) {
        data = new T[capacity];
    }
    
    ~Stack() { delete[] data; }
    
    void push(const T& item) {
        if (top_index < capacity - 1) {
            data[++top_index] = item;
        }
    }
    
    T pop() {
        if (top_index >= 0) {
            return data[top_index--];
        }
        return T();  // Default constructed value
    }
    
    T& top() { return data[top_index]; }
    bool empty() const { return top_index == -1; }
};

// Usage
Stack<int> int_stack(100);
Stack<std::string> string_stack(50);
```

---

## 🧪 Advanced Testing Strategies

### 1. **Type Compatibility Testing**

#### Testing with Different Categories:
```cpp
void test_primitive_types() {
    // Integer types
    int a = 5, b = 10;
    ::swap(a, b);
    assert(a == 10 && b == 5);
    
    // Floating point types
    double x = 3.14, y = 2.71;
    assert(::min(x, y) == 2.71);
    assert(::max(x, y) == 3.14);
    
    // Character types
    char c1 = 'z', c2 = 'a';
    ::swap(c1, c2);
    assert(c1 == 'a' && c2 == 'z');
}

void test_complex_types() {
    // String objects
    std::string s1 = "zebra", s2 = "apple";
    assert(::min(s1, s2) == "apple");  // Lexicographic comparison
    
    // Custom objects (if properly implemented)
    Point p1(1, 2), p2(3, 4);
    Point smaller = ::min(p1, p2);  // Uses Point::operator<
}
```

### 2. **Edge Case Testing**

#### Equal Values Testing:
```cpp
void test_equal_values() {
    int a = 42, b = 42;
    
    // Test that second value is returned for equal inputs
    int min_result = ::min(a, b);
    int max_result = ::max(a, b);
    
    // Both should return b (second parameter)
    assert(&min_result == &b || min_result == b);
    assert(&max_result == &b || max_result == b);
}
```

#### Boundary Value Testing:
```cpp
void test_boundary_values() {
    // Maximum/minimum values for int
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    
    assert(::min(max_int, min_int) == min_int);
    assert(::max(max_int, min_int) == max_int);
    
    // Floating point edge cases
    float pos_inf = std::numeric_limits<float>::infinity();
    float neg_inf = -std::numeric_limits<float>::infinity();
    
    assert(::min(pos_inf, neg_inf) == neg_inf);
    assert(::max(pos_inf, neg_inf) == pos_inf);
}
```

### 3. **Performance Testing**

#### Template Instantiation Cost:
```cpp
void performance_test() {
    const int iterations = 1000000;
    
    // Test with integers
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        int a = i, b = i + 1;
        ::swap(a, b);
        volatile int result = ::min(a, b);  // Prevent optimization
    }
    clock_t end = clock();
    
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Template performance: " << duration << " seconds" << std::endl;
}
```

### 4. **Compilation Testing**

#### Type Constraint Verification:
```cpp
// This should compile
void test_valid_types() {
    int a = 1, b = 2;
    ::swap(a, b);  // ✅ int has copy operations
    
    std::string s1 = "a", s2 = "b";
    ::min(s1, s2);  // ✅ std::string has operator<
}

// These should NOT compile (test by uncommenting)
void test_invalid_types() {
    // struct NoCompare { int x; };
    // NoCompare nc1{1}, nc2{2};
    // ::min(nc1, nc2);  // ❌ No operator< defined
    
    // int arr1[5], arr2[5];
    // ::swap(arr1, arr2);  // ❌ Arrays not assignable
}
```

---

## 🔧 Common Pitfalls and Solutions

### 1. **Template Definition Location**

#### ❌ **Wrong: Definition in .cpp file**
```cpp
// template.h
template<typename T>
void my_function(T param);

// template.cpp
template<typename T>
void my_function(T param) {  // Definition separated from declaration
    // Implementation
}

// main.cpp
#include "template.h"
int main() {
    my_function(42);  // LINKER ERROR: Undefined reference
}
```

#### ✅ **Correct: Definition in header**
```cpp
// template.h
template<typename T>
void my_function(T param) {  // Definition in header
    // Implementation
}

// main.cpp
#include "template.h"
int main() {
    my_function(42);  // OK: Definition available for instantiation
}
```

### 2. **Type Deduction Issues**

#### ❌ **Ambiguous Type Deduction**
```cpp
template<typename T>
void func(T a, T b) { /* ... */ }

int main() {
    func(1, 2.5);  // ERROR: Cannot deduce T (int vs double)
}
```

#### ✅ **Explicit Type Specification**
```cpp
int main() {
    func<double>(1, 2.5);  // OK: Explicitly specify T = double
    // Or convert parameters to same type
    func(1.0, 2.5);       // OK: Both are double
}
```

### 3. **Parameter Passing Issues**

#### ❌ **Inefficient for Large Objects**
```cpp
template<typename T>
T min(T a, T b) {  // Pass by value - copies large objects
    return (a < b) ? a : b;
}

std::string large_string(10000, 'x');
std::string result = min(large_string, "small");  // Unnecessary copying
```

#### ✅ **Efficient Reference Passing**
```cpp
template<typename T>
const T& min(const T& a, const T& b) {  // Pass by const reference
    return (a < b) ? a : b;
}

// Or for our specific exercise requirements:
template<typename T>
T min(T a, T b) {  // As required by subject (simple types expected)
    return (a < b) ? a : b;
}
```

### 4. **Comparison Operator Requirements**

#### ❌ **Missing Required Operators**
```cpp
class MyClass {
    int value;
public:
    MyClass(int v) : value(v) {}
    // Missing operator< and operator>
};

MyClass a(1), b(2);
// min(a, b);  // ERROR: No operator< found
```

#### ✅ **Complete Operator Implementation**
```cpp
class MyClass {
    int value;
public:
    MyClass(int v) : value(v) {}
    
    bool operator<(const MyClass& other) const {
        return value < other.value;
    }
    
    bool operator>(const MyClass& other) const {
        return value > other.value;
    }
    
    // Optional: implement all comparison operators
    bool operator==(const MyClass& other) const { return value == other.value; }
    bool operator!=(const MyClass& other) const { return !(*this == other); }
    bool operator<=(const MyClass& other) const { return !(other < *this); }
    bool operator>=(const MyClass& other) const { return !(*this < other); }
};
```

---

## 💡 Design Principles Demonstrated

### 1. **Generic Programming Principles**

#### **Type Independence:**
```cpp
// Same algorithm works for all comparable types
template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;  // Logic independent of specific type
}
```

#### **Code Reuse:**
```cpp
// One definition serves multiple types
::min(1, 2);              // Uses min<int>
::min(1.5, 2.7);          // Uses min<double>
::min("abc", "def");      // Uses min<const char*>
```

#### **Type Safety:**
```cpp
// Compile-time type checking
::min(1, 2);     // OK: Both int
::min(1, 2.5);   // ERROR: Type mismatch (int vs double)
```

### 2. **Interface Design Principles**

#### **Minimal Requirements:**
Templates should require only what they need:
```cpp
template<typename T>
void swap(T& a, T& b) {
    // Only requires: copy constructor, copy assignment
    T temp = a; a = b; b = temp;
}

template<typename T>
T min(T a, T b) {
    // Only requires: copy constructor, operator<
    return (a < b) ? a : b;
}
```

#### **Consistent Interface:**
```cpp
// All functions follow same naming and parameter conventions
::swap(a, b);    // void return, reference parameters
::min(a, b);     // T return, value parameters
::max(a, b);     // T return, value parameters
```

### 3. **Performance Considerations**

#### **Zero-Cost Abstraction:**
Templates provide abstraction without runtime overhead:
```cpp
// Template version
template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

// After instantiation for int, equivalent to:
void swap_int(int& a, int& b) { int temp = a; a = b; b = temp; }

// No function call overhead, same performance as hand-written version
```

#### **Compile-Time Optimization:**
```cpp
// Compiler can inline template instantiations
int a = 1, b = 2;
::swap(a, b);

// May be optimized to:
// int temp = a; a = b; b = temp;  // Direct code, no function call
```

---

## 🚀 Modern C++ Evolution

### Template Features in Later Standards:

#### **C++11 Additions:**
```cpp
// Variadic templates
template<typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first;
    if (sizeof...(args) > 0) {
        std::cout << ", ";
        print(args...);
    }
}

// Auto return type deduction
template<typename T, typename U>
auto min(T a, U b) -> decltype(a < b ? a : b) {
    return (a < b) ? a : b;
}
```

#### **C++14 Improvements:**
```cpp
// Return type deduction
template<typename T, typename U>
auto min(T a, U b) {  // No need for -> decltype
    return (a < b) ? a : b;
}

// Variable templates
template<typename T>
constexpr T pi = T(3.1415926535897932385);
```

#### **C++17 Features:**
```cpp
// if constexpr for conditional compilation
template<typename T>
void process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // Integer-specific code
    } else if constexpr (std::is_floating_point_v<T>) {
        // Float-specific code
    }
}

// Class template argument deduction
std::pair p{1, 2.5};  // Deduces std::pair<int, double>
```

#### **C++20 Concepts:**
```cpp
// Constrain templates with concepts
template<std::totally_ordered T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

// Custom concepts
template<typename T>
concept Swappable = requires(T a, T b) {
    { std::swap(a, b) } -> std::same_as<void>;
};

template<Swappable T>
void my_swap(T& a, T& b) {
    std::swap(a, b);
}
```

---

## 🏆 Evaluation Preparation - Complete Checklist

### **Core Concepts Understanding:**
- [ ] **Template syntax**: `template<typename T>` declaration
- [ ] **Instantiation process**: How compiler generates code for each type
- [ ] **Type deduction**: How compiler determines template parameters
- [ ] **Header requirements**: Why templates must be in headers
- [ ] **Namespace resolution**: Purpose of `::` operator

### **Implementation Details:**
- [ ] **swap() function**: Reference parameters, temporary variable
- [ ] **min() function**: Value parameters, returns second if equal
- [ ] **max() function**: Value parameters, returns second if equal
- [ ] **Type requirements**: What operations types must support
- [ ] **Global scope**: Using `::` to call our functions specifically

### **Testing Knowledge:**
- [ ] **Multiple types**: int, float, char, std::string compatibility
- [ ] **Equal values**: Correct behavior when parameters are equal
- [ ] **Edge cases**: Boundary values, special float values
- [ ] **Performance**: Understanding of zero-cost abstraction

### **Advanced Understanding:**
- [ ] **Compilation model**: Two-phase compilation process
- [ ] **Template specialization**: How to customize for specific types
- [ ] **Type constraints**: Implicit requirements vs explicit constraints
- [ ] **Modern evolution**: How templates evolved in newer C++ standards

### **Code Quality:**
- [ ] **École 42 compliance**: Proper naming, formatting, compilation flags
- [ ] **Header guards**: Protection against multiple inclusion
- [ ] **No memory issues**: Templates work with stack objects
- [ ] **Error handling**: Compile-time error detection

---

*This comprehensive guide covers all fundamental aspects of function templates in C++. Master these concepts to understand the foundation of generic programming and prepare for more advanced template features in subsequent exercises.*

````
