````markdown
# CPP05_EX03 - Factory Pattern and Dynamic Object Creation

## 📚 Overview

This exercise (cpp05/ex03) introduces the **Factory Pattern** and **dynamic object creation**, demonstrating how to create objects at runtime based on string parameters. It builds upon inheritance and polymorphism from ex02 while introducing advanced design patterns for flexible object instantiation.

---

## 🎯 Learning Objectives

By completing this exercise, you will understand:
- **Factory Pattern** implementation and benefits
- **Function pointers** and **pointer-to-member functions**
- **Dynamic object creation** based on runtime parameters
- **String-based object instantiation**
- **Clean alternatives to excessive if/else chains**
- **Method lookup tables** and **dispatch mechanisms**
- **Exception handling** for invalid parameters
- **Memory management** in factory scenarios

---

## 🔍 Key C++ Concepts Covered

### 1. **The Factory Pattern**

#### What is the Factory Pattern?
The Factory Pattern is a **creational design pattern** that provides an interface for creating objects without specifying their exact classes. It encapsulates object creation logic and makes the code more flexible and maintainable.

#### Problem it Solves:
```cpp
// Without Factory Pattern - messy and hard to maintain
AForm* createForm(const std::string& type, const std::string& target) {
    if (type == "shrubbery creation") {
        return new ShrubberyCreationForm(target);
    }
    else if (type == "robotomy request") {
        return new RobotomyRequestForm(target);
    }
    else if (type == "presidential pardon") {
        return new PresidentialPardonForm(target);
    }
    else if (type == "future form type 1") {
        return new FutureForm1(target);
    }
    // ... potentially many more else-if statements
    else {
        return nullptr;
    }
}
```

#### Factory Pattern Solution:
```cpp
class Intern {
private:
    // Clean, table-driven approach
    AForm* (Intern::*formCreators[3])(const std::string&);
    const std::string formNames[3];
    
public:
    AForm* makeForm(const std::string& formName, const std::string& target);
};
```

#### Benefits of Factory Pattern:
- **Encapsulation**: Object creation logic is centralized
- **Extensibility**: Easy to add new form types
- **Maintainability**: Reduces code duplication
- **Flexibility**: Runtime object creation decisions
- **Single Responsibility**: Creator class handles only creation

### 2. **Function Pointers and Member Function Pointers**

#### Basic Function Pointers:
```cpp
// Function pointer syntax
int (*functionPtr)(int, int);

// Example usage
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

functionPtr = &add;      // Point to add function
int result = functionPtr(5, 3);  // Calls add(5, 3)
```

#### Member Function Pointers:
```cpp
// Member function pointer syntax
class MyClass {
public:
    int method(int x);
};

// Declaration
int (MyClass::*methodPtr)(int);

// Assignment
methodPtr = &MyClass::method;

// Usage
MyClass obj;
int result = (obj.*methodPtr)(42);  // Call through object
// or
MyClass* objPtr = &obj;
int result = (objPtr->*methodPtr)(42);  // Call through pointer
```

#### In Our Intern Implementation:
```cpp
class Intern {
private:
    // Array of member function pointers
    AForm* (Intern::*formCreators[3])(const std::string&);
    
    // Individual creator methods
    AForm* createShrubberyCreationForm(const std::string& target);
    AForm* createRobotomyRequestForm(const std::string& target);
    AForm* createPresidentialPardonForm(const std::string& target);
    
public:
    AForm* makeForm(const std::string& formName, const std::string& target) {
        // Initialize arrays (could be done in constructor)
        formCreators[0] = &Intern::createShrubberyCreationForm;
        formCreators[1] = &Intern::createRobotomyRequestForm;
        formCreators[2] = &Intern::createPresidentialPardonForm;
        
        // Use function pointer
        for (int i = 0; i < 3; i++) {
            if (formName == formNames[i]) {
                return (this->*formCreators[i])(target);
            }
        }
        throw FormNotFoundException();
    }
};
```

#### Why Use Function Pointers Here?
- **Eliminates if/else chains**: More elegant than multiple conditionals
- **Table-driven design**: Easy to extend with new form types
- **Performance**: Direct function calls without branching
- **Maintainability**: Adding new forms requires minimal code changes

### 3. **Dynamic Object Creation**

#### Runtime Type Selection:
```cpp
// Factory creates different types based on runtime string
AForm* form = intern.makeForm("robotomy request", "Bender");
// Type of 'form' determined at runtime, not compile time
```

#### Memory Management Considerations:
```cpp
// Factory returns raw pointer - caller responsible for cleanup
AForm* form = intern.makeForm("shrubbery creation", "garden");

// Use the form
bureaucrat.signForm(*form);
bureaucrat.executeForm(*form);

// Clean up
delete form;  // Caller must remember to delete!
```

#### Modern C++ Alternative (Post-C++11):
```cpp
// Better approach with smart pointers
std::unique_ptr<AForm> form = intern.makeForm("robotomy request", "Bender");
// Automatic cleanup when form goes out of scope
```

### 4. **String-Based Dispatch**

#### Pattern Matching Strategy:
```cpp
// Array of recognized form names
const std::string formNames[3] = {
    "shrubbery creation",
    "robotomy request", 
    "presidential pardon"
};

// Linear search through names
for (int i = 0; i < 3; i++) {
    if (formName == formNames[i]) {
        return (this->*formCreators[i])(target);
    }
}
```

#### Alternative Approaches:

##### 1. Hash Map Approach (C++98 with std::map):
```cpp
std::map<std::string, AForm* (Intern::*)(const std::string&)> creators;

// In constructor
creators["shrubbery creation"] = &Intern::createShrubberyCreationForm;
creators["robotomy request"] = &Intern::createRobotomyRequestForm;

// In makeForm
std::map<std::string, AForm* (Intern::*)(const std::string&)>::iterator it;
it = creators.find(formName);
if (it != creators.end()) {
    return (this->*(it->second))(target);
}
```

##### 2. Switch Statement (with enum):
```cpp
enum FormType { SHRUBBERY, ROBOTOMY, PARDON, UNKNOWN };

FormType getFormType(const std::string& name) {
    if (name == "shrubbery creation") return SHRUBBERY;
    if (name == "robotomy request") return ROBOTOMY;
    if (name == "presidential pardon") return PARDON;
    return UNKNOWN;
}

switch (getFormType(formName)) {
    case SHRUBBERY: return new ShrubberyCreationForm(target);
    case ROBOTOMY: return new RobotomyRequestForm(target);
    case PARDON: return new PresidentialPardonForm(target);
    default: throw FormNotFoundException();
}
```

#### Our Choice: Array-Based Lookup
- **Simplicity**: Easy to understand and maintain
- **C++98 Compatible**: No need for std::map or modern features
- **Performance**: O(n) linear search (acceptable for small n)
- **École 42 Requirement**: Avoids "excessive if/else structure"

### 5. **Exception Handling for Invalid Input**

#### Custom Exception Design:
```cpp
class FormNotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Form not found";
    }
};
```

#### Exception Throwing Strategy:
```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    // Try to find and create form
    for (int i = 0; i < 3; i++) {
        if (formName == formNames[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            return (this->*formCreators[i])(target);
        }
    }
    
    // Not found - provide helpful error message
    std::cout << "Error: Form \"" << formName << "\" does not exist" << std::endl;
    throw FormNotFoundException();
}
```

#### Exception Handling Best Practices:
- **Descriptive messages**: Clear error indication
- **Specific exceptions**: Different exception types for different errors
- **Early failure**: Fail fast when invalid input detected
- **Resource safety**: No memory leaks even when exceptions thrown

### 6. **Orthodox Canonical Form for Factory Classes**

#### Intern Class Design:
```cpp
class Intern {
public:
    Intern();                                    // Default constructor
    Intern(const Intern& other);                // Copy constructor
    Intern& operator=(const Intern& other);     // Assignment operator
    ~Intern();                                   // Destructor
    
    // Factory method
    AForm* makeForm(const std::string& formName, const std::string& target);
};
```

#### Implementation Considerations:
```cpp
// Default constructor - nothing special needed
Intern::Intern() {
    std::cout << "Intern default constructor called" << std::endl;
}

// Copy constructor - stateless class, simple copy
Intern::Intern(const Intern& other) {
    std::cout << "Intern copy constructor called" << std::endl;
    *this = other;
}

// Assignment operator - no state to copy
Intern& Intern::operator=(const Intern& other) {
    std::cout << "Intern copy assignment operator called" << std::endl;
    (void)other;  // Suppress unused parameter warning
    return *this;
}

// Destructor - no resources to clean up
Intern::~Intern() {
    std::cout << "Intern destructor called" << std::endl;
}
```

#### Why OCF is Simple Here:
- **Stateless class**: Intern has no member variables
- **Function pointers**: Could be static, don't represent object state
- **No resources**: No dynamic memory or file handles to manage
- **Value semantics**: Copying an intern creates identical functionality

---

## 🛠️ Advanced Design Patterns and Alternatives

### 1. **Registry Pattern (Advanced Factory)**

#### Concept:
Allow dynamic registration of new form types without modifying the factory code.

#### Implementation Example:
```cpp
class FormRegistry {
private:
    std::map<std::string, AForm* (*)(const std::string&)> creators;
    
public:
    template<typename T>
    void registerForm(const std::string& name) {
        creators[name] = [](const std::string& target) -> AForm* {
            return new T(target);
        };
    }
    
    AForm* createForm(const std::string& name, const std::string& target) {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return it->second(target);
        }
        throw FormNotFoundException();
    }
};
```

### 2. **Abstract Factory Pattern**

#### When to Use:
When you need to create families of related objects.

#### Example Extension:
```cpp
class FormFactory {
public:
    virtual AForm* createShrubbery(const std::string& target) = 0;
    virtual AForm* createRobotomy(const std::string& target) = 0;
    virtual AForm* createPardon(const std::string& target) = 0;
};

class StandardFormFactory : public FormFactory {
    // Standard implementation
};

class HighSecurityFormFactory : public FormFactory {
    // Enhanced security versions
};
```

### 3. **Builder Pattern (Alternative for Complex Objects)**

#### When Complex Construction Needed:
```cpp
class FormBuilder {
private:
    std::string type, target, classification;
    int signGrade, execGrade;
    
public:
    FormBuilder& setType(const std::string& t) { type = t; return *this; }
    FormBuilder& setTarget(const std::string& t) { target = t; return *this; }
    AForm* build();
};

// Usage
AForm* form = FormBuilder()
    .setType("robotomy request")
    .setTarget("Bender")
    .setClassification("confidential")
    .build();
```

---

## 🧪 Testing Strategies for Factory Pattern

### 1. **Factory Functionality Testing**
```cpp
// Test successful creation of all types
Intern intern;
AForm* shrub = intern.makeForm("shrubbery creation", "garden");
AForm* robot = intern.makeForm("robotomy request", "Bender");
AForm* pardon = intern.makeForm("presidential pardon", "Arthur");

// Verify correct types created
assert(dynamic_cast<ShrubberyCreationForm*>(shrub) != nullptr);
assert(dynamic_cast<RobotomyRequestForm*>(robot) != nullptr);
assert(dynamic_cast<PresidentialPardonForm*>(pardon) != nullptr);
```

### 2. **Error Handling Testing**
```cpp
// Test invalid form names
try {
    AForm* invalid = intern.makeForm("invalid form", "target");
    assert(false);  // Should not reach here
} catch (Intern::FormNotFoundException& e) {
    // Expected behavior
}
```

### 3. **Memory Management Testing**
```cpp
// Test proper cleanup
std::vector<AForm*> forms;
for (int i = 0; i < 100; i++) {
    forms.push_back(intern.makeForm("shrubbery creation", "test"));
}

// Clean up all forms
for (size_t i = 0; i < forms.size(); i++) {
    delete forms[i];
}
```

### 4. **Integration Testing**
```cpp
// Test full workflow: create -> sign -> execute
AForm* form = intern.makeForm("robotomy request", "Bender");
Bureaucrat boss("Boss", 1);
boss.signForm(*form);
boss.executeForm(*form);
delete form;
```

---

## 🏗️ Implementation Best Practices

### 1. **Const Correctness in Factory Methods**
```cpp
// Factory methods should be const if they don't modify factory state
class Intern {
    AForm* makeForm(const std::string& formName, const std::string& target) const;
    //                                                                     ^^^^^
    // However, our implementation uses member function pointers which 
    // may not work well with const methods in C++98
};
```

### 2. **Error Message Consistency**
```cpp
// Consistent error reporting
std::cout << "Intern creates " << formName << std::endl;  // Success
std::cout << "Error: Form \"" << formName << "\" does not exist" << std::endl;  // Failure
```

### 3. **Parameter Validation**
```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    // Validate inputs
    if (formName.empty()) {
        std::cout << "Error: Form name cannot be empty" << std::endl;
        throw FormNotFoundException();
    }
    
    if (target.empty()) {
        std::cout << "Warning: Target is empty" << std::endl;
        // Continue - empty target might be valid for some forms
    }
    
    // ... rest of implementation
}
```

### 4. **Extensibility Considerations**
```cpp
// Design for easy extension
class Intern {
private:
    static const int MAX_FORMS = 10;  // Allow for future expansion
    AForm* (Intern::*formCreators[MAX_FORMS])(const std::string&);
    std::string formNames[MAX_FORMS];
    int formCount;  // Track actual number of forms
    
    void initializeForms();  // Separate initialization method
};
```

---

## 🔄 Comparison with Previous Exercises

| Aspect | Ex00 | Ex01 | Ex02 | Ex03 |
|--------|------|------|------|------|
| **Design Pattern** | None | Delegation | Template Method | Factory |
| **Object Creation** | Direct | Direct | Direct | Dynamic |
| **Type Selection** | Compile-time | Compile-time | Compile-time | Runtime |
| **Extensibility** | Low | Medium | Medium | High |
| **Complexity** | Basic | Intermediate | Advanced | Expert |
| **String Processing** | None | Minimal | None | Central |
| **Lookup Mechanism** | None | None | None | Table-driven |

---

## 🚀 Advanced C++ Features Preview

This exercise prepares you for:

### 1. **Template Factories (C++11+)**
```cpp
template<typename T>
std::unique_ptr<AForm> createForm(const std::string& target) {
    return std::make_unique<T>(target);
}
```

### 2. **Lambda Functions (C++11+)**
```cpp
std::map<std::string, std::function<std::unique_ptr<AForm>(const std::string&)>> creators = {
    {"shrubbery", [](const std::string& target) { 
        return std::make_unique<ShrubberyCreationForm>(target); 
    }},
    {"robotomy", [](const std::string& target) { 
        return std::make_unique<RobotomyRequestForm>(target); 
    }}
};
```

### 3. **Variadic Templates (C++11+)**
```cpp
template<typename T, typename... Args>
std::unique_ptr<AForm> createForm(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}
```

### 4. **Reflection Systems (Advanced)**
```cpp
// Hypothetical reflection-based factory
AForm* form = FormFactory::create("RobotomyRequestForm", "Bender");
```

---

## 💡 Key Design Principles Demonstrated

### 1. **SOLID Principles**

#### Single Responsibility Principle (SRP):
- **Intern**: Only responsible for creating forms
- **Form classes**: Only responsible for their specific behavior
- **Bureaucrat**: Only responsible for signing/executing

#### Open/Closed Principle (OCP):
- **Open for extension**: Easy to add new form types
- **Closed for modification**: Intern class doesn't need changes for new forms

#### Dependency Inversion Principle (DIP):
- **Intern**: Depends on AForm abstraction, not concrete classes
- **Client code**: Uses Intern interface, not implementation details

### 2. **Gang of Four Patterns**
- **Factory Method**: Creates objects without specifying exact classes
- **Template Method**: (inherited from ex02) Defines algorithm skeleton
- **Strategy**: Function pointers act as strategies for object creation

### 3. **Clean Code Principles**
- **Meaningful names**: `makeForm`, `createShrubberyCreationForm`
- **Small functions**: Each creator method has single responsibility
- **No magic numbers**: Use constants for array sizes
- **Clear error messages**: Descriptive exception handling

---

## 🔍 Common Pitfalls and Solutions

### 1. **Memory Leaks in Factory Pattern**
```cpp
// PROBLEM: Caller forgets to delete
AForm* form = intern.makeForm("robotomy", "target");
// ... use form ...
// Forgot: delete form;  // MEMORY LEAK!

// SOLUTION: Clear documentation and consistent cleanup
{
    AForm* form = intern.makeForm("robotomy", "target");
    // ... use form ...
    delete form;  // Always clean up
}
```

### 2. **Exception Safety in Factory**
```cpp
// PROBLEM: Exception thrown after object created
AForm* Intern::makeForm(const std::string& name, const std::string& target) {
    AForm* form = createSpecificForm(target);  // Created
    doSomethingThatMightThrow();               // Exception! Memory leak!
    return form;
}

// SOLUTION: Use RAII or careful exception handling
AForm* Intern::makeForm(const std::string& name, const std::string& target) {
    std::auto_ptr<AForm> form(createSpecificForm(target));  // C++98 RAII
    doSomethingThatMightThrow();
    return form.release();  // Transfer ownership
}
```

### 3. **Case Sensitivity in String Matching**
```cpp
// PROBLEM: Case sensitivity issues
intern.makeForm("Robotomy Request", "target");  // Fails!
intern.makeForm("robotomy request", "target");  // Works

// SOLUTION: Case-insensitive comparison
bool compareIgnoreCase(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;
    for (size_t i = 0; i < a.length(); i++) {
        if (std::tolower(a[i]) != std::tolower(b[i])) return false;
    }
    return true;
}
```

### 4. **Function Pointer Array Initialization**
```cpp
// PROBLEM: Uninitialized function pointers
AForm* (Intern::*formCreators[3])(const std::string&);  // Uninitialized!

// SOLUTION: Initialize in constructor or at declaration
Intern::Intern() {
    formCreators[0] = &Intern::createShrubberyCreationForm;
    formCreators[1] = &Intern::createRobotomyRequestForm;
    formCreators[2] = &Intern::createPresidentialPardonForm;
}
```

---

## 📖 Related C++ Features and Patterns

### Design Patterns:
- **Abstract Factory**: Creating families of related objects
- **Builder**: Complex object construction
- **Prototype**: Cloning existing objects
- **Singleton**: Ensuring single factory instance

### C++ Features:
- **Function objects (functors)**: Alternative to function pointers
- **std::function**: Type-erased function wrappers (C++11+)
- **Lambda expressions**: Anonymous functions (C++11+)
- **Template metaprogramming**: Compile-time factories
- **CRTP**: Curiously Recurring Template Pattern for static polymorphism

### Modern Alternatives:
- **std::make_unique**: Safe object creation (C++14+)
- **std::shared_ptr**: Shared ownership semantics
- **std::variant**: Type-safe unions for object storage
- **Concepts**: Compile-time interface checking (C++20+)

---

## 🎯 Practical Applications

This factory pattern is commonly used in:

1. **Document Processing**: Creating different document types (PDF, Word, Excel)
2. **Game Development**: Spawning different enemy types, weapons, or items
3. **Network Programming**: Creating different protocol handlers (HTTP, FTP, SSH)
4. **GUI Frameworks**: Creating different widget types (Button, TextField, etc.)
5. **Plugin Systems**: Dynamic loading and creation of plugin objects
6. **Database Drivers**: Creating connections for different database types
7. **Compiler Design**: Creating different AST node types during parsing

---

## 🏆 Mastery Indicators

You've mastered this exercise when you can:

1. **Explain** why the factory pattern is better than if/else chains
2. **Implement** function pointer arrays for dispatch mechanisms
3. **Design** extensible factory systems that support new types easily
4. **Handle** invalid input gracefully with appropriate exceptions
5. **Manage** memory properly in dynamic object creation scenarios
6. **Identify** when to use factory pattern vs. other creational patterns
7. **Recognize** the trade-offs between different factory implementations

---

*This exercise introduces industrial-strength design patterns that form the backbone of extensible, maintainable software systems. Master the factory pattern here, and you'll recognize it everywhere in professional codebases.*

````
