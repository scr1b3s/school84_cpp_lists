# CPP05_EX01 - Advanced Exception Handling and Object Interaction

## 📚 Overview

This exercise (cpp05/ex01) builds upon the foundation from ex00 by introducing **class interaction** and **collaborative object design**. It demonstrates how multiple classes can work together while maintaining proper encapsulation and exception safety.

---

## 🎯 Learning Objectives

By completing this exercise, you will understand:
- **Object collaboration** and inter-class communication
- **Forward declarations** to resolve circular dependencies
- **Exception propagation** across class boundaries
- **Const member limitations** in assignment operators
- **Method delegation** and responsibility distribution
- **Complex testing scenarios** involving multiple objects

---

## 🔍 Key C++ Concepts Covered

### 1. **Class Interaction and Collaboration**

#### The Problem: Object Relationships
Real-world applications require objects to interact and collaborate. In this exercise, we have:
- **Bureaucrat**: Can sign forms
- **Form**: Can be signed by bureaucrats

#### Design Pattern: Collaborative Methods
```cpp
// Form provides the signing mechanism
void Form::beSigned(const Bureaucrat& bureaucrat);

// Bureaucrat provides the user interface
void Bureaucrat::signForm(Form& form);
```

#### Key Design Principles:
- **Single Responsibility**: Each class handles its own validation
- **Delegation**: Bureaucrat delegates actual signing to Form
- **Encapsulation**: Form controls its own state changes

### 2. **Forward Declarations**

#### The Circular Dependency Problem:
```cpp
// Bureaucrat.hpp needs to know about Form
// Form.hpp needs to know about Bureaucrat
// This creates a circular include dependency
```

#### Solution: Forward Declarations
```cpp
// In Bureaucrat.hpp
class Form; // Forward declaration
class Bureaucrat {
    void signForm(Form& form);  // Can use Form* or Form&
};

// In Form.hpp  
class Bureaucrat; // Forward declaration
class Form {
    void beSigned(const Bureaucrat& bureaucrat);  // Can use Bureaucrat&
};
```

#### When to Use Forward Declarations:
- **Parameters/Return types**: When you only need to pass objects around
- **Pointers/References**: When you don't need the complete type definition
- **Avoiding circular includes**: Breaking dependency cycles

#### When NOT to Use Forward Declarations:
- **Inheritance**: `class Derived : public Base` needs complete Base definition
- **Member objects**: `class A { B member; }` needs complete B definition
- **Template instantiation**: Templates need complete type information

### 3. **Exception Propagation and Handling**

#### Multi-Level Exception Handling:
```cpp
// Level 1: Form validates and throws
void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();  // Throw specific exception
    _signed = true;
}

// Level 2: Bureaucrat catches and handles
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);  // May throw
        std::cout << _name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << _name << " couldn't sign " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}
```

#### Exception Safety Patterns:
1. **Strong Exception Safety**: Operation either succeeds completely or has no effect
2. **Basic Exception Safety**: Objects remain in valid state after exception
3. **No-throw Guarantee**: Operation never throws (rare, usually destructors)

#### Our Implementation:
- **Form::beSigned()**: Strong safety - either signs or throws, no partial state
- **Bureaucrat::signForm()**: Basic safety - catches exceptions and reports them

### 4. **Const Correctness in Complex Scenarios**

#### Multiple Const Members Challenge:
```cpp
class Form {
private:
    const std::string   _name;           // Can't be reassigned
    bool               _signed;          // Can be reassigned  
    const int          _gradeToSign;     // Can't be reassigned
    const int          _gradeToExecute;  // Can't be reassigned
};
```

#### Assignment Operator Limitations:
```cpp
Form& Form::operator=(const Form& other) {
    if (this != &other) {
        // _name = other._name;           // ERROR: const member
        _signed = other._signed;          // OK: non-const member
        // _gradeToSign = other._gradeToSign;     // ERROR: const member
        // _gradeToExecute = other._gradeToExecute; // ERROR: const member
    }
    return *this;
}
```

#### Design Implications:
- **Const members limit assignability** but ensure immutability
- **Business logic**: Form requirements shouldn't change after creation
- **Copy vs Assignment**: Copy constructor can initialize const members, assignment cannot

### 5. **Method Parameter Design**

#### Parameter Passing Strategies:

```cpp
// Taking const reference - read-only access
void Form::beSigned(const Bureaucrat& bureaucrat);
// Why const&:
// - No copying (efficient)
// - Read-only (safety) 
// - No null pointer risk

// Taking non-const reference - allows modification
void Bureaucrat::signForm(Form& form);
// Why non-const&:
// - Form state will be modified
// - No copying (efficient)
// - Clear ownership semantics
```

#### Reference vs Pointer Guidelines:
- **Use references when**: Parameter must exist (no null), clear ownership
- **Use pointers when**: Parameter might be null, array semantics needed
- **Use const when**: No modification intended

### 6. **Exception Message Design**

#### Context-Sensitive Messages:
```cpp
// Constructor validation
if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();  // "grade is too high"

// Signing validation  
if (bureaucrat.getGrade() > _gradeToSign)
    throw GradeTooLowException();   // "grade is too low"
```

#### Message Strategy:
- **Generic messages**: Reusable across contexts
- **Context provided by caller**: Bureaucrat adds context in error output
- **User-friendly**: Clear without being overly technical

### 7. **Object State Management**

#### State Transitions:
```cpp
// Initial state
Form form("Tax Form", 50, 25);  // signed = false

// State change through method
form.beSigned(bureaucrat);      // signed = true (if successful)

// State is persistent
std::cout << form;              // Shows current signed status
```

#### Immutable vs Mutable State:
- **Immutable**: Name, grade requirements (business rules)
- **Mutable**: Signed status (workflow state)
- **Validation**: Ensure state changes are valid

---

## 🛠️ Implementation Patterns

### 1. **The Delegation Pattern**

```cpp
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);  // Delegate actual signing to Form
        // Handle success
    }
    catch (std::exception& e) {
        // Handle failure
    }
}
```

**Benefits:**
- **Clear responsibilities**: Form knows how to be signed, Bureaucrat knows how to report
- **Extensibility**: Easy to add new form types with different signing rules
- **Testing**: Can test signing logic independently of reporting logic

### 2. **The Two-Phase Operation Pattern**

```cpp
// Phase 1: Validation (may throw)
if (bureaucrat.getGrade() > _gradeToSign)
    throw GradeTooLowException();

// Phase 2: State modification (no exceptions)
_signed = true;
```

**Benefits:**
- **Exception safety**: Either succeeds completely or fails cleanly
- **Atomic operations**: No partial state changes
- **Predictable behavior**: Clear success/failure semantics

### 3. **The Observer Pattern (Simplified)**

```cpp
// Bureaucrat observes the result of signing attempt
form.beSigned(*this);  // Action
std::cout << _name << " signed " << form.getName();  // Reaction
```

**Benefits:**
- **Loose coupling**: Form doesn't need to know about output requirements
- **Flexible reporting**: Different bureaucrats could report differently
- **Separation of concerns**: Business logic separate from presentation

---

## 🏗️ Advanced Design Considerations

### 1. **Circular Dependency Management**

#### The Include Chain:
```cpp
// main.cpp
#include "Bureaucrat.hpp"  // Includes Form.hpp
#include "Form.hpp"        // Includes Bureaucrat.hpp
```

#### Resolution Strategy:
```cpp
// Bureaucrat.hpp
class Form;  // Forward declaration only
#include "Form.hpp"  // NOT here

// Bureaucrat.cpp  
#include "Bureaucrat.hpp"
#include "Form.hpp"  // Include implementation file
```

### 2. **Exception Hierarchy Design**

```cpp
// Both classes have similar exceptions
class Bureaucrat {
    class GradeTooHighException : public std::exception { };
    class GradeTooLowException : public std::exception { };
};

class Form {
    class GradeTooHighException : public std::exception { };
    class GradeTooLowException : public std::exception { };
};
```

#### Design Trade-offs:
- **Separate exceptions**: Clear ownership, specific context
- **Shared exceptions**: Less code duplication, but more coupling
- **École 42 choice**: Separate (follows encapsulation principle)

### 3. **Const Method Cascading**

```cpp
// Chain of const methods
void Bureaucrat::signForm(Form& form) {
    form.beSigned(*this);  // Calls non-const method
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
    bureaucrat.getGrade();  // Calls const method
}
```

**Design principle:** Operations that don't modify state should be const, operations that do modify state cannot be const.

---

## 🧪 Testing Strategies

### 1. **Interaction Testing**

```cpp
// Test successful collaboration
Bureaucrat alice("Alice", 30);
Form form("Form", 50, 25);
alice.signForm(form);  // Should succeed

// Test failed collaboration  
Bureaucrat bob("Bob", 100);
bob.signForm(form);    // Should fail gracefully
```

### 2. **State Consistency Testing**

```cpp
// Verify state changes
assert(form.getSigned() == false);  // Before
alice.signForm(form);
assert(form.getSigned() == true);   // After
```

### 3. **Exception Propagation Testing**

```cpp
// Test that exceptions are caught and handled
// (Not thrown up to main)
bureaucrat.signForm(form);  // Should not throw to caller
```

### 4. **Edge Case Testing**

```cpp
// Boundary conditions
Form minForm("Min", 1, 1);
Form maxForm("Max", 150, 150);
Bureaucrat topBureaucrat("Top", 1);
Bureaucrat bottomBureaucrat("Bottom", 150);

// Test all combinations
topBureaucrat.signForm(minForm);    // Should succeed
bottomBureaucrat.signForm(maxForm); // Should succeed  
bottomBureaucrat.signForm(minForm); // Should fail
```

---

## 🔄 Comparison with Ex00

| Aspect | Ex00 | Ex01 |
|--------|------|------|
| **Classes** | Single (Bureaucrat) | Multiple (Bureaucrat + Form) |
| **Interactions** | Self-contained | Inter-object communication |
| **Exceptions** | Single context | Multiple contexts |
| **Complexity** | Basic OOP | Collaborative design |
| **Dependencies** | None | Forward declarations |
| **Testing** | Unit tests | Integration tests |

---

## 💡 Key Takeaways

1. **Object collaboration requires careful interface design**
2. **Forward declarations solve circular dependency problems**
3. **Exception handling can span multiple classes**
4. **Const correctness becomes more complex with multiple classes**
5. **Delegation pattern improves code organization**
6. **Testing must cover both individual objects and their interactions**

---

## 🔮 Preparing for Future Exercises

This exercise introduces patterns that will be essential for:
- **Inheritance hierarchies** (Form → PresidentialPardonForm, etc.)
- **Abstract base classes** and **virtual functions**
- **Template-based exception handling**
- **Complex object lifecycles**
- **Design patterns** (Strategy, Factory, etc.)

---

## 📖 Related C++ Features

- **Friend classes** (alternative to public interfaces)
- **Nested classes** (alternative to separate exception classes)
- **Smart pointers** (modern C++ resource management)
- **SFINAE** (template metaprogramming for type safety)
- **Concepts** (C++20 constraint checking)

---

*This exercise demonstrates how properly designed classes can collaborate while maintaining strong encapsulation and clear responsibilities. Master these interaction patterns to build more complex object-oriented systems.*
