# CPP05 - Exception Handling and Advanced OOP Concepts

## 📚 Overview

This exercise (cpp05/ex00) introduces **Exception Handling** in C++, a crucial mechanism for managing runtime errors gracefully. It builds upon previous OOP concepts while introducing new advanced features.

---

## 🎯 Learning Objectives

By completing this exercise, you will understand:
- Exception handling mechanisms (`try`, `catch`, `throw`)
- Custom exception classes
- Exception inheritance from `std::exception`
- Orthodox Canonical Form (OCF) implementation
- Const correctness in class design
- Operator overloading for output streams

---

## 🔍 Key C++ Concepts Covered

### 1. **Exception Handling**

#### What are Exceptions?
Exceptions are a C++ mechanism to handle runtime errors elegantly, allowing programs to respond to exceptional circumstances during execution.

#### Exception Syntax
```cpp
try {
    // Code that might throw an exception
    Bureaucrat bob("Bob", 0);  // This will throw
}
catch (std::exception& e) {
    // Handle the exception
    std::cout << "Error: " << e.what() << std::endl;
}
```

#### Key Components:
- **`try` block**: Contains code that might throw exceptions
- **`catch` block**: Handles specific exception types
- **`throw` statement**: Throws an exception when error occurs

### 2. **Custom Exception Classes**

#### Why Custom Exceptions?
- Provide specific error information
- Allow different handling for different error types
- Maintain type safety

#### Implementation Pattern:
```cpp
class MyException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Custom error message";
    }
};
```

#### In Our Exercise:
```cpp
class GradeTooHighException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Grade is too high! (minimum grade is 1)";
    }
};
```

**Key Points:**
- Inherit from `std::exception` for standard compatibility
- Override `what()` method to provide error description
- Use `throw()` specifier (C++98 style) to indicate no exceptions thrown
- Exception classes don't need Orthodox Canonical Form (as stated in subject)

### 3. **Orthodox Canonical Form (OCF)**

#### The Four Required Methods:
1. **Default Constructor**: `Class()`
2. **Copy Constructor**: `Class(const Class& other)`
3. **Assignment Operator**: `Class& operator=(const Class& other)`
4. **Destructor**: `~Class()`

#### Implementation in Bureaucrat:
```cpp
// 1. Default Constructor
Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {
    // Initialize with safe defaults
}

// 2. Copy Constructor
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {
    // Member-wise copy using initialization list
}

// 3. Assignment Operator
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {  // Self-assignment check
        _grade = other._grade;  // _name is const, can't be reassigned
    }
    return *this;  // Return reference for chaining
}

// 4. Destructor
Bureaucrat::~Bureaucrat() {
    // Cleanup resources (none needed here)
}
```

#### Important OCF Considerations:
- **Self-assignment check**: Prevents `obj = obj` issues
- **Return reference**: Allows chaining `a = b = c`
- **Const members**: Cannot be reassigned in assignment operator

### 4. **Const Correctness**

#### Const Member Variables:
```cpp
private:
    const std::string _name;  // Cannot be modified after construction
    int _grade;               // Can be modified
```

#### Const Member Functions:
```cpp
const std::string& getName() const;  // Promise not to modify object
int getGrade() const;                // Promise not to modify object
```

#### Benefits:
- **Interface clarity**: Shows which methods modify the object
- **Compiler enforcement**: Prevents accidental modifications
- **Optimization**: Compiler can optimize const operations

### 5. **Operator Overloading**

#### Stream Insertion Operator (`<<`):
```cpp
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat) {
    out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return out;  // Return stream for chaining
}
```

#### Key Points:
- **Global function**: Not a member function
- **Reference parameters**: Avoid copying stream objects
- **Return reference**: Enables chaining `cout << obj1 << obj2`
- **Const parameter**: Object shouldn't be modified during output

### 6. **Initialization Lists**

#### Why Use Initialization Lists?
```cpp
// Preferred: Initialization List
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade) {
    // Constructor body
}

// Avoid: Assignment in body
Bureaucrat::Bureaucrat(const std::string& name, int grade) {
    _name = name;    // Error! _name is const
    _grade = grade;  // This would work, but less efficient
}
```

#### Benefits:
- **Required for const members**: Only way to initialize const variables
- **More efficient**: Direct initialization vs. default + assignment
- **Required for references**: References must be initialized

### 7. **Exception Safety and RAII**

#### Exception Safety Levels:
1. **Basic Guarantee**: No resource leaks, object in valid state
2. **Strong Guarantee**: Either succeeds completely or has no effect
3. **No-throw Guarantee**: Never throws exceptions

#### In Our Implementation:
```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
    if (grade < 1)
        throw GradeTooHighException();  // _name already initialized
    if (grade > 150)
        throw GradeTooLowException();   // _name already initialized
    _grade = grade;  // Only set if validation passes
}
```

---

## 🛠️ Implementation Details

### Class Design Decisions

#### 1. **Grade Validation Strategy**:
- Validate in constructor and modification methods
- Throw specific exceptions for different error conditions
- Use consistent validation logic across all methods

#### 2. **Const Name Design**:
- Name cannot change after creation (business logic requirement)
- Reflects real-world scenario where employee names are fixed
- Challenges assignment operator implementation

#### 3. **Grade Increment/Decrement Logic**:
```cpp
void incrementGrade() {
    if (_grade <= 1)          // Check BEFORE modification
        throw GradeTooHighException();
    _grade--;                 // Lower number = higher grade
}
```

### Memory Management

#### Stack vs Heap Objects:
```cpp
// Stack allocation (automatic cleanup)
Bureaucrat bob("Bob", 75);

// Heap allocation (manual cleanup required)
Bureaucrat* alice = new Bureaucrat("Alice", 50);
delete alice;  // Must delete manually
```

#### Exception Safety:
- Stack objects automatically cleaned up when exceptions thrown
- RAII principle: Resource Acquisition Is Initialization

---

## 🧪 Testing Strategy

### Test Categories Implemented:

1. **Valid Object Creation**: Normal cases
2. **Boundary Testing**: Grades 1 and 150
3. **Exception Testing**: Invalid grades (0, 151)
4. **Functionality Testing**: Increment/decrement operations
5. **Exception Propagation**: Out-of-bounds operations
6. **Copy Semantics**: Copy constructor and assignment
7. **Output Formatting**: Stream operator verification

### Exception Testing Pattern:
```cpp
try {
    // Code that should throw
    Bureaucrat invalid("Invalid", 0);
    // If we reach here, test failed
}
catch (std::exception& e) {
    // Expected path - test passed
    std::cout << "Exception caught: " << e.what() << std::endl;
}
```

---

## 🏗️ Build System (Makefile)

### École 42 Standards:
- **Compiler**: `c++` (usually g++)
- **Flags**: `-Wall -Wextra -Werror -std=c++98`
- **C++98 Standard**: Ensures compatibility with older systems

### Makefile Features:
```makefile
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Object file organization
OBJDIR = obj
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Dependency handling
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
    @$(CXX) $(CXXFLAGS) -c $< -o $@
```

---

## 🎨 Code Style and Best Practices

### École 42 Conventions:
- **Member Variables**: Prefix with underscore (`_name`, `_grade`)
- **Function Names**: camelCase (`getName`, `incrementGrade`)
- **Class Names**: PascalCase (`Bureaucrat`, `GradeTooHighException`)
- **Const Correctness**: Mark everything const that can be const

### Exception Best Practices:
- **Catch by reference**: `catch (std::exception& e)` not `catch (std::exception e)`
- **Specific exceptions**: Create meaningful exception types
- **Exception safety**: Ensure objects remain in valid state
- **Documentation**: Clear error messages in `what()` methods

---

## 🔄 Advanced Concepts Preview

This exercise prepares you for:
- **Exception hierarchies** (next exercises)
- **Template exception handling**
- **RAII and smart pointers**
- **Exception specifications** (deprecated in modern C++)
- **std::exception_ptr** (C++11+)

---

## 💡 Key Takeaways

1. **Exceptions provide elegant error handling** compared to error codes
2. **Custom exceptions enable type-safe error handling**
3. **Orthodox Canonical Form ensures proper object lifecycle**
4. **Const correctness improves code safety and clarity**
5. **Operator overloading enhances object usability**
6. **Exception safety is crucial for robust programs**

---

## 📖 Related C++ Features

- **std::exception hierarchy**
- **RAII (Resource Acquisition Is Initialization)**
- **Exception specifications** (throw() in C++98)
- **Stack unwinding**
- **Exception propagation**
- **noexcept** (C++11 replacement for throw())

---

*This document covers the fundamental concepts needed to understand and implement exception handling in C++. Master these concepts before proceeding to more complex exception scenarios in subsequent exercises.*
