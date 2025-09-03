# CPP05_EX02 - Inheritance, Abstract Classes, and Polymorphism

## 📚 Overview

This exercise (cpp05/ex02) introduces the most fundamental concepts of **Object-Oriented Programming**: **inheritance**, **abstract classes**, and **polymorphism**. It transforms the simple Form class into a sophisticated hierarchy that demonstrates how objects can share common behavior while implementing specific functionality.

---

## 🎯 Learning Objectives

By completing this exercise, you will understand:
- **Abstract classes** and **pure virtual functions**
- **Inheritance hierarchies** and **is-a relationships**
- **Polymorphism** and **virtual function dispatch**
- **The Template Method design pattern**
- **Virtual destructors** and proper cleanup
- **File I/O operations** in C++
- **Random number generation** in C++98

---

## 🔍 Key C++ Concepts Covered

### 1. **Abstract Classes and Pure Virtual Functions**

#### What Makes a Class Abstract?
```cpp
class AForm {
    // Pure virtual function - makes class abstract
    virtual void executeAction() const = 0;
};
```

#### Key Characteristics:
- **Cannot be instantiated**: `AForm form;` would cause a compilation error
- **Must be inherited**: Only derived classes can be instantiated
- **Interface definition**: Defines what derived classes must implement
- **Common functionality**: Can still have regular methods and data members

#### Why Use Abstract Classes?
```cpp
// Problem: Different forms need different execution logic
// Solution: Define common interface, specific implementations

class AForm {
public:
    // Common validation logic
    void execute(const Bureaucrat& executor) const {
        if (!_signed) throw FormNotSignedException();
        if (executor.getGrade() > _gradeToExecute) throw GradeTooLowException();
        executeAction();  // Delegate to specific implementation
    }
    
    // Each form type implements this differently
    virtual void executeAction() const = 0;
};
```

### 2. **Inheritance Hierarchy Design**

#### The Inheritance Tree:
```
        AForm (Abstract)
       /       |        \
ShrubberyForm  RobotForm  PardonForm
```

#### Class Relationships:
```cpp
class ShrubberyCreationForm : public AForm {
    // IS-A relationship: ShrubberyCreationForm IS-A AForm
    // HAS-A relationship: ShrubberyCreationForm HAS-A target string
};
```

#### Inheritance Benefits:
- **Code reuse**: Common functionality in base class
- **Polymorphism**: Treat different forms uniformly
- **Extensibility**: Easy to add new form types
- **Maintainability**: Changes to common logic affect all forms

### 3. **Virtual Functions and Polymorphism**

#### Virtual Function Mechanism:
```cpp
// Base class declares virtual function
class AForm {
public:
    virtual void executeAction() const = 0;
    virtual ~AForm();  // Virtual destructor essential!
};

// Derived classes override virtual function
class ShrubberyCreationForm : public AForm {
public:
    virtual void executeAction() const override;  // C++11 style
    // Or just: void executeAction() const;        // C++98 style
};
```

#### Runtime Polymorphism:
```cpp
AForm* forms[] = {
    new ShrubberyCreationForm("garden"),
    new RobotomyRequestForm("robot"),
    new PresidentialPardonForm("citizen")
};

for (int i = 0; i < 3; i++) {
    forms[i]->execute(bureaucrat);  // Calls correct executeAction() at runtime
}
```

#### Virtual Function Table (vtable):
- **Compile time**: Compiler creates vtable for each class with virtual functions
- **Runtime**: Object stores pointer to its class's vtable
- **Function call**: Looks up correct function in vtable based on actual object type

### 4. **The Template Method Design Pattern**

#### Pattern Structure:
```cpp
class AForm {
public:
    // Template method - defines algorithm skeleton
    void execute(const Bureaucrat& executor) const {
        // Step 1: Validate preconditions
        if (!_signed) throw FormNotSignedException();
        if (executor.getGrade() > _gradeToExecute) throw GradeTooLowException();
        
        // Step 2: Execute specific action (varies by subclass)
        executeAction();  // Pure virtual - must be implemented
    }
    
protected:
    // Hook method - implemented by subclasses
    virtual void executeAction() const = 0;
};
```

#### Pattern Benefits:
- **Consistent behavior**: All forms follow same validation process
- **Flexible implementation**: Each form can have unique execution logic
- **Open/Closed principle**: Open for extension, closed for modification
- **DRY principle**: Don't repeat validation logic

### 5. **Virtual Destructors**

#### Why Virtual Destructors are Essential:
```cpp
class AForm {
public:
    virtual ~AForm();  // MUST be virtual!
};

// Without virtual destructor:
AForm* form = new ShrubberyCreationForm("test");
delete form;  // Only calls ~AForm(), NOT ~ShrubberyCreationForm()
             // This causes resource leaks!

// With virtual destructor:
delete form;  // Calls ~ShrubberyCreationForm() then ~AForm()
             // Proper cleanup guaranteed!
```

#### Virtual Destructor Chain:
```cpp
// When deleting a ShrubberyCreationForm through AForm*:
// 1. ~ShrubberyCreationForm() called
// 2. ~AForm() called  
// 3. All resources properly cleaned up
```

### 6. **Constructor Delegation in Inheritance**

#### Base Class Constructor Calling:
```cpp
class ShrubberyCreationForm : public AForm {
public:
    ShrubberyCreationForm(const std::string& target) 
        : AForm("Shrubbery Creation Form", 145, 137),  // Call base constructor
          _target(target)                              // Initialize own members
    {
        // Constructor body
    }
};
```

#### Constructor Execution Order:
1. **Base class constructor** (`AForm`) runs first
2. **Derived class members** initialized
3. **Derived class constructor body** runs

#### Destructor Execution Order (Reverse):
1. **Derived class destructor body** runs
2. **Derived class members** destroyed
3. **Base class destructor** runs

### 7. **File I/O Operations**

#### File Writing Pattern:
```cpp
void ShrubberyCreationForm::executeAction() const {
    std::string filename = _target + "_shrubbery";
    std::ofstream file(filename.c_str());  // C++98 style
    
    if (!file.is_open()) {
        // Handle error - file couldn't be created
        return;
    }
    
    file << "ASCII art content" << std::endl;
    // file automatically closed when destructor runs
}
```

#### C++98 File I/O Considerations:
- **C-style strings**: Use `.c_str()` for filename
- **Automatic cleanup**: `ofstream` destructor closes file
- **Error checking**: Always check if file opened successfully
- **Resource safety**: RAII ensures proper file closing

### 8. **Random Number Generation (C++98)**

#### Basic Random Generation:
```cpp
#include <cstdlib>
#include <ctime>

void RobotomyRequestForm::executeAction() const {
    // Seed random number generator (do this once per program)
    srand(static_cast<unsigned int>(time(NULL)));
    
    // Generate random number 0 or 1 (50% chance each)
    if (rand() % 2 == 0) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Failure!" << std::endl;
    }
}
```

#### Random Generation Best Practices:
- **Seed once**: Usually in `main()` or first use
- **Thread safety**: `rand()` is not thread-safe
- **Quality**: `rand()` has limitations, but sufficient for simple cases

---

## 🛠️ Advanced Design Patterns

### 1. **The Template Method Pattern (Detailed)**

#### Intent:
Define the skeleton of an algorithm in a base class, letting subclasses override specific steps without changing the algorithm's structure.

#### Implementation in Our Exercise:
```cpp
// Algorithm skeleton in base class
void AForm::execute(const Bureaucrat& executor) const {
    validateSigned();      // Common step
    validateGrade();       // Common step  
    executeAction();       // Variable step (pure virtual)
}
```

#### Pattern Participants:
- **AbstractClass** (`AForm`): Defines template method and abstract operations
- **ConcreteClass** (`ShrubberyCreationForm`): Implements abstract operations

### 2. **The Strategy Pattern (Alternative Approach)**

#### What if we used Strategy instead of Template Method?
```cpp
// Alternative design (not used in this exercise)
class ExecutionStrategy {
public:
    virtual void execute(const std::string& target) = 0;
};

class AForm {
private:
    ExecutionStrategy* _strategy;
public:
    void execute(const Bureaucrat& executor) const {
        // validation...
        _strategy->execute(_target);  // Delegate to strategy
    }
};
```

#### Template Method vs Strategy:
- **Template Method**: Inheritance-based, compile-time binding
- **Strategy**: Composition-based, runtime strategy switching
- **Our choice**: Template Method fits better for fixed form types

### 3. **Factory Pattern (Future Extension)**

#### How you might extend this design:
```cpp
class FormFactory {
public:
    static AForm* createForm(const std::string& type, const std::string& target) {
        if (type == "shrubbery") return new ShrubberyCreationForm(target);
        if (type == "robotomy") return new RobotomyRequestForm(target);
        if (type == "pardon") return new PresidentialPardonForm(target);
        return nullptr;
    }
};
```

---

## 🧪 Testing Strategies for Inheritance

### 1. **Polymorphism Testing**
```cpp
// Test that base class pointers work correctly
AForm* forms[] = { /* different form types */ };
for (int i = 0; i < 3; i++) {
    bureaucrat.executeForm(*forms[i]);  // Should call correct method
}
```

### 2. **Abstract Class Testing**
```cpp
// This should NOT compile:
// AForm abstractForm;  // Compilation error - cannot instantiate abstract class
```

### 3. **Virtual Destructor Testing**
```cpp
// Ensure proper cleanup through base pointer
AForm* form = new ShrubberyCreationForm("test");
delete form;  // Should call derived destructor first
```

### 4. **Exception Hierarchy Testing**
```cpp
// Test that all forms throw same exception types
try {
    unsignedForm.execute(bureaucrat);
} catch (AForm::FormNotSignedException& e) {
    // Should catch regardless of actual form type
}
```

---

## 🏗️ Memory Management in Inheritance

### 1. **Object Slicing Problem**
```cpp
// PROBLEM: Object slicing
ShrubberyCreationForm shrub("garden");
AForm form = shrub;  // SLICES! Only AForm part copied, target lost!

// SOLUTION: Use pointers or references
AForm* form = &shrub;     // OK - no slicing
AForm& formRef = shrub;   // OK - no slicing
```

### 2. **Proper Cleanup Pattern**
```cpp
// Always use smart pointers in modern C++ (post-C++11)
// In C++98, manual cleanup:
AForm* form = new ShrubberyCreationForm("test");
try {
    form->execute(bureaucrat);
} catch (...) {
    delete form;  // Clean up even if exception thrown
    throw;        // Re-throw exception
}
delete form;      // Normal cleanup
```

### 3. **RAII with Inheritance**
```cpp
// Better pattern - use automatic objects when possible
{
    ShrubberyCreationForm shrub("test");
    bureaucrat.executeForm(shrub);
}  // Automatic cleanup - no memory leaks
```

---

## 🔄 Comparison with Previous Exercises

| Aspect | Ex00 | Ex01 | Ex02 |
|--------|------|------|------|
| **Classes** | Single | Collaboration | Hierarchy |
| **Relationships** | None | Association | Inheritance |
| **Polymorphism** | No | No | Yes |
| **Virtual Functions** | No | No | Yes |
| **Abstract Classes** | No | No | Yes |
| **Design Patterns** | None | Delegation | Template Method |
| **Complexity** | Basic OOP | Intermediate | Advanced |

---

## 🚀 Advanced C++ Features Preview

This exercise prepares you for:

### 1. **Multiple Inheritance**
```cpp
class DiamondForm : public AForm, public Trackable {
    // Multiple inheritance complications
};
```

### 2. **Interface Segregation**
```cpp
class Signable {
    virtual void beSigned(const Bureaucrat&) = 0;
};

class Executable {
    virtual void execute(const Bureaucrat&) = 0;
};
```

### 3. **Template-Based Polymorphism**
```cpp
template<typename FormType>
class FormProcessor {
    void process(FormType& form) { /* ... */ }
};
```

---

## 💡 Key Design Principles Demonstrated

### 1. **SOLID Principles**

#### Single Responsibility Principle (SRP):
- Each form class has one reason to change
- `AForm` handles validation, derived classes handle execution

#### Open/Closed Principle (OCP):
- Open for extension (new form types)
- Closed for modification (AForm doesn't change)

#### Liskov Substitution Principle (LSP):
- Any `AForm*` can point to any derived form
- Behavior remains consistent

#### Interface Segregation Principle (ISP):
- Forms only implement what they need
- No unused methods forced on clients

#### Dependency Inversion Principle (DIP):
- `Bureaucrat` depends on `AForm` abstraction
- Not on concrete form implementations

### 2. **Design Patterns**
- **Template Method**: Algorithm structure + flexible implementation
- **Polymorphism**: Runtime behavior selection
- **Virtual Constructor** (through factory): Dynamic object creation

---

## 🔍 Common Pitfalls and Solutions

### 1. **Forgetting Virtual Destructor**
```cpp
// WRONG
class AForm {
public:
    ~AForm();  // NOT virtual - causes leaks!
};

// CORRECT
class AForm {
public:
    virtual ~AForm();  // Virtual - proper cleanup
};
```

### 2. **Object Slicing**
```cpp
// WRONG
void processForm(AForm form) {  // Pass by value - slicing!
    form.execute(bureaucrat);
}

// CORRECT
void processForm(const AForm& form) {  // Pass by reference
    form.execute(bureaucrat);
}
```

### 3. **Pure Virtual in Constructor**
```cpp
// WRONG
class AForm {
public:
    AForm() {
        executeAction();  // NEVER call pure virtual from constructor!
    }
    virtual void executeAction() = 0;
};
```

---

## 📖 Related C++ Features

- **RTTI** (Runtime Type Information): `typeid`, `dynamic_cast`
- **Virtual inheritance**: Solving diamond problem
- **Abstract interfaces**: Pure virtual classes
- **Template specialization**: Compile-time polymorphism
- **Concepts** (C++20): Compile-time interface checking

---

## 🎯 Practical Applications

This inheritance pattern is commonly used in:

1. **GUI Frameworks**: Button, TextBox, etc. inherit from Widget
2. **Game Development**: Enemy, Player, NPC inherit from Entity
3. **File Systems**: File, Directory inherit from FileSystemObject
4. **Network Protocols**: TCP, UDP inherit from Protocol
5. **Document Processing**: PDF, Word, Excel inherit from Document

---

*This exercise introduces the cornerstone concepts of object-oriented programming. Master inheritance, virtual functions, and polymorphism here, as they form the foundation for all advanced C++ design patterns and architectural decisions.*
