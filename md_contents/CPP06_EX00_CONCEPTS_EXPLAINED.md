````markdown
# CPP06_EX00 - Static Classes and Type Conversion

## 📚 Overview

This exercise (cpp06/ex00) introduces **static class design patterns** and **comprehensive type conversion** mechanisms in C++. It demonstrates how to create utility classes that cannot be instantiated and focuses on robust string-to-scalar conversions with proper error handling for edge cases and special floating-point values.

---

## 🎯 Learning Objectives

By completing this exercise, you will understand:
- **Static class design patterns** and preventing instantiation
- **Comprehensive type detection** from string representations
- **C++ scalar type conversions** (char, int, float, double)
- **Floating-point special values** (NaN, infinity)
- **Robust input validation** and error handling
- **String parsing techniques** in C++98
- **Type casting** and **precision handling**
- **C standard library conversion functions**

---

## 🔍 Key C++ Concepts Covered

### 1. **Static Class Design Pattern**

#### What is a Static Class?
A static class is a design pattern where a class serves as a **namespace-like container** for related functionality without requiring instantiation. All methods are static, and the class cannot be instantiated.

#### Implementation Pattern:
```cpp
class ScalarConverter {
private:
    // Private constructors prevent instantiation
    ScalarConverter();                                    // Default constructor
    ScalarConverter(const ScalarConverter& other);       // Copy constructor
    ScalarConverter& operator=(const ScalarConverter&);  // Assignment operator
    ~ScalarConverter();                                  // Destructor

public:
    // Only static methods are public
    static void convert(const std::string& input);
};
```

#### Why Use Static Classes?
- **Utility functions**: When you need related functions grouped together
- **Stateless operations**: When no object state is needed
- **Prevention of instantiation**: When creating objects doesn't make sense
- **Namespace alternative**: Cleaner than global functions

#### Comparison with Alternatives:

| Approach | Pros | Cons |
|----------|------|------|
| **Static Class** | Type safety, clear intent, no instantiation | Slightly more verbose |
| **Namespace** | Simpler syntax | Less type safety, can be reopened |
| **Global Functions** | Simple | Pollutes global namespace |

### 2. **Comprehensive Type Detection**

#### String Analysis Strategy:
Our implementation uses a **multi-stage detection process**:

```cpp
// Detection pipeline
if (isPseudoLiteral(input))   { /* Handle special values */ }
else if (isChar(input))       { /* Handle char literals */ }
else if (isInt(input))        { /* Handle integer literals */ }
else if (isFloat(input))      { /* Handle float literals */ }
else if (isDouble(input))     { /* Handle double literals */ }
else                          { /* Invalid input */ }
```

#### Character Literal Detection:
```cpp
bool ScalarConverter::isChar(const std::string& input) {
    return (input.length() == 3 &&        // Exactly 3 characters
            input[0] == '\'' &&            // Starts with quote
            input[2] == '\'' &&            // Ends with quote
            input[1] >= 32 &&              // Printable ASCII range
            input[1] <= 126);              // Printable ASCII range
}
```

**Key considerations:**
- **Exact length**: Must be exactly `'x'` format
- **Printable range**: Only displayable ASCII characters
- **Quote validation**: Proper single quote enclosure

#### Integer Detection with Overflow Protection:
```cpp
bool ScalarConverter::isInt(const std::string& input) {
    // Basic format validation
    size_t start = (input[0] == '+' || input[0] == '-') ? 1 : 0;
    for (size_t i = start; i < input.length(); i++) {
        if (!std::isdigit(input[i])) return false;
    }
    
    // Overflow detection using long
    char* endptr;
    long value = std::strtol(input.c_str(), &endptr, 10);
    
    return (value >= std::numeric_limits<int>::min() && 
            value <= std::numeric_limits<int>::max());
}
```

**Advanced techniques:**
- **Sign handling**: Proper detection of +/- prefixes
- **Overflow protection**: Using `long` as intermediate type
- **Range validation**: Ensuring value fits in `int` range
- **End pointer validation**: Ensuring entire string was parsed

#### Float Literal Detection:
```cpp
bool ScalarConverter::isFloat(const std::string& input) {
    if (input.length() < 2 || input.back() != 'f') return false;
    
    std::string withoutF = input.substr(0, input.length() - 1);
    
    // Validate decimal number format
    bool hasDot = false, hasDigit = false;
    size_t start = (withoutF[0] == '+' || withoutF[0] == '-') ? 1 : 0;
    
    for (size_t i = start; i < withoutF.length(); i++) {
        if (withoutF[i] == '.') {
            if (hasDot) return false;  // Multiple dots
            hasDot = true;
        } else if (std::isdigit(withoutF[i])) {
            hasDigit = true;
        } else {
            return false;  // Invalid character
        }
    }
    
    return hasDigit;  // Must have at least one digit
}
```

**Float-specific validation:**
- **Suffix requirement**: Must end with 'f'
- **Decimal format**: Allows optional decimal point
- **Single dot rule**: Only one decimal point allowed
- **Digit requirement**: Must contain at least one digit

### 3. **Floating-Point Special Values**

#### Understanding IEEE 754 Special Values:

| Value | Float | Double | Meaning |
|-------|-------|--------|---------|
| **Positive Infinity** | `+inff` | `+inf` | Result of 1.0/0.0 |
| **Negative Infinity** | `-inff` | `-inf` | Result of -1.0/0.0 |
| **Not a Number** | `nanf` | `nan` | Result of 0.0/0.0 |

#### Implementation of Special Value Handling:
```cpp
bool ScalarConverter::isPseudoLiteral(const std::string& input) {
    return (input == "-inff" || input == "+inff" || input == "nanf" ||
            input == "-inf" || input == "+inf" || input == "nan");
}

void ScalarConverter::handlePseudoLiteral(const std::string& input) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    
    if (input == "-inff" || input == "-inf") {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
    // ... handle other cases
}
```

#### Why Special Values Matter:
- **Mathematical completeness**: Handle division by zero results
- **Robust calculations**: Prevent crashes from invalid operations
- **Standard compliance**: IEEE 754 floating-point standard
- **Real-world scenarios**: Common in scientific computing

### 4. **Type Casting and Conversion**

#### Static Cast Strategy:
```cpp
void ScalarConverter::convertFromInt(int value) {
    printChar(static_cast<double>(value));                    // int → double → char
    std::cout << "int: " << value << std::endl;               // Direct output
    std::cout << "float: " << static_cast<float>(value);      // int → float
    std::cout << "double: " << static_cast<double>(value);    // int → double
}
```

#### Conversion Hierarchy:
```
    char ←→ int ←→ float ←→ double
     ↑       ↑       ↑        ↑
   8-bit   32-bit  32-bit   64-bit
  ASCII    whole  decimal   decimal
```

#### Precision Considerations:
- **Narrowing conversions**: May lose precision (double → float)
- **Widening conversions**: Generally safe (int → double)
- **Character conversions**: ASCII value interpretation
- **Range checking**: Prevent overflow/underflow

### 5. **Robust Error Handling**

#### Multi-Level Validation:
```cpp
void ScalarConverter::printChar(double value, bool impossible) {
    if (impossible || std::isnan(value) || std::isinf(value) || 
        value < 0 || value > 127) {
        std::cout << "char: impossible" << std::endl;
    }
    else if (value <= 31 || value == 127) {
        std::cout << "char: Non displayable" << std::endl;
    }
    else {
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
    }
}
```

#### Error Categories:
1. **Impossible conversions**: NaN, infinity, out of range
2. **Non-displayable**: Control characters (0-31, 127)
3. **Format errors**: Invalid input syntax
4. **Overflow errors**: Values too large for target type

#### Error Message Design:
- **"impossible"**: Cannot be converted to target type
- **"Non displayable"**: Valid char value but not printable
- **Clear error messages**: Descriptive feedback for invalid input

### 6. **String Parsing in C++98**

#### C Standard Library Functions:
```cpp
// String to integer conversion
long value = std::strtol(input.c_str(), &endptr, 10);

// String to floating-point conversion
double value = std::atof(input.c_str());
float value = static_cast<float>(std::atof(input.c_str()));
```

#### Why These Functions?
- **C++98 compatibility**: Available in older standards
- **Error detection**: `strtol` provides end pointer for validation
- **Robust parsing**: Handle various number formats
- **Performance**: Optimized C library implementations

#### Modern Alternatives (Post-C++11):
```cpp
// C++11+ alternatives (not used in this exercise)
int value = std::stoi(input);           // String to int
float value = std::stof(input);         // String to float
double value = std::stod(input);        // String to double
```

---

## 🛠️ Advanced Implementation Patterns

### 1. **Template Method Pattern (Advanced)**

#### Could be extended with templates:
```cpp
// Theoretical template extension (not in this exercise)
template<typename T>
class TypeConverter {
public:
    static void convert(const std::string& input);
    
private:
    static bool isValidFormat(const std::string& input);
    static T parseValue(const std::string& input);
    static void displayResult(T value);
};
```

### 2. **Strategy Pattern Alternative**

#### Alternative design using function pointers:
```cpp
class ScalarConverter {
private:
    struct ConversionStrategy {
        bool (*detector)(const std::string&);
        void (*converter)(const std::string&);
    };
    
    static ConversionStrategy strategies[];
    
public:
    static void convert(const std::string& input);
};
```

### 3. **Error Handling Patterns**

#### Exception-Based Alternative:
```cpp
class ConversionException : public std::exception {
private:
    std::string message;
    
public:
    ConversionException(const std::string& msg) : message(msg) {}
    virtual const char* what() const throw() { return message.c_str(); }
};

// Usage
try {
    ScalarConverter::convert(input);
} catch (const ConversionException& e) {
    std::cout << "Conversion error: " << e.what() << std::endl;
}
```

---

## 🧪 Testing Strategies

### 1. **Boundary Value Testing**
```cpp
// Test edge cases
"0"           // Minimum displayable char (non-displayable)
"31"          // Boundary of non-displayable
"32"          // First displayable char (space)
"127"         // Last ASCII char (DEL, non-displayable)
"128"         // Beyond ASCII range
```

### 2. **Special Value Testing**
```cpp
// Test all pseudo-literals
"nanf"    → float: nanf, double: nan
"+inff"   → float: +inff, double: +inf
"-inf"    → float: -inff, double: -inf
```

### 3. **Format Validation Testing**
```cpp
// Valid formats
"'a'"     // Char literal
"42"      // Integer
"42.0f"   // Float
"42.0"    // Double

// Invalid formats
"abc"     // Random string
"42f"     // Missing decimal for float
"'ab'"    // Multi-character in quotes
```

### 4. **Precision Testing**
```cpp
// Test floating-point precision
"42.123456789f"   // Float precision limits
"42.123456789"    // Double precision
"3.14159265359"   // Pi precision
```

### 5. **Overflow Testing**
```cpp
// Test integer overflow
"2147483647"      // INT_MAX
"2147483648"      // INT_MAX + 1 (overflow)
"-2147483648"     // INT_MIN
"-2147483649"     // INT_MIN - 1 (underflow)
```

---

## 🏗️ Design Decisions and Trade-offs

### 1. **Static Class vs Namespace**

#### Our Choice: Static Class
**Pros:**
- **Type safety**: Clear class boundaries
- **Encapsulation**: Private helper methods
- **Instantiation prevention**: Explicit design intent

**Alternative: Namespace**
```cpp
namespace ScalarConverter {
    void convert(const std::string& input);
    
    // Helper functions would be exposed or in anonymous namespace
    bool isChar(const std::string& input);
    bool isInt(const std::string& input);
}
```

### 2. **Error Handling Strategy**

#### Our Choice: Return Codes + Console Output
**Pros:**
- **Simple implementation**: Direct output control
- **C++98 compatible**: No exception handling complexity
- **Clear feedback**: Immediate user feedback

**Alternative: Exception-Based**
- **Pros**: Better for library use, composable
- **Cons**: More complex, not required by subject

### 3. **Type Detection Order**

#### Our Choice: Pseudo → Char → Int → Float → Double
**Reasoning:**
- **Pseudo-literals first**: Avoid parsing as numbers
- **Most specific first**: Char has strictest format
- **Integer before float**: Avoid misclassifying integers
- **Double last**: Catch remaining decimal numbers

### 4. **Precision Handling**

#### Our Choice: Context-Sensitive Formatting
```cpp
// Display .0 for whole numbers
if (value == static_cast<int>(value))
    std::cout << std::fixed << std::setprecision(1) << value;
else
    std::cout << value;  // Default precision
```

---

## 🔄 Comparison with Previous Modules

| Aspect | CPP05 | CPP06/Ex00 |
|--------|--------|------------|
| **Focus** | OOP, Inheritance, Exceptions | Static Classes, Type Conversion |
| **Design Pattern** | Template Method, Factory | Static Utility Class |
| **Object Creation** | Dynamic instantiation | No instantiation |
| **Error Handling** | Custom exceptions | Error messages + validation |
| **Complexity** | Object relationships | String parsing + conversion |
| **Memory Management** | new/delete for objects | Stack-based, no dynamic allocation |

---

## 🚀 Advanced C++ Features Preview

This exercise prepares you for:

### 1. **C++11 Type Conversion Functions**
```cpp
// Modern alternatives to C functions
std::stoi(), std::stof(), std::stod()
std::to_string()  // Reverse conversion
```

### 2. **Template Metaprogramming**
```cpp
template<typename T>
constexpr bool is_scalar_v = std::is_arithmetic_v<T>;

template<typename T>
std::enable_if_t<is_scalar_v<T>, void> 
convert(const std::string& input) { /* ... */ }
```

### 3. **std::variant (C++17)**
```cpp
using ScalarValue = std::variant<char, int, float, double>;

ScalarValue parseScalar(const std::string& input) {
    // Return any of the four types
}
```

### 4. **Concepts (C++20)**
```cpp
template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
void convert(const std::string& input) { /* ... */ }
```

---

## 💡 Key Design Principles Demonstrated

### 1. **Single Responsibility Principle (SRP)**
- **ScalarConverter**: Only handles type conversion
- **Helper methods**: Each handles one type detection
- **Display methods**: Each formats one output type

### 2. **Don't Repeat Yourself (DRY)**
- **Common validation logic**: Reused across type detectors
- **Display helpers**: Centralized formatting logic
- **Error message patterns**: Consistent error reporting

### 3. **Fail Fast Principle**
- **Early validation**: Detect invalid input immediately
- **Specific error messages**: Clear feedback for failures
- **Boundary checking**: Prevent invalid conversions

### 4. **Defensive Programming**
- **Input validation**: Comprehensive format checking
- **Range checking**: Prevent overflow/underflow
- **Special value handling**: Robust floating-point handling

---

## 🔍 Common Pitfalls and Solutions

### 1. **Integer Overflow During Detection**
```cpp
// PROBLEM: Direct atoi() can overflow
int value = std::atoi(input.c_str());  // Undefined behavior on overflow

// SOLUTION: Use long as intermediate
long longValue = std::strtol(input.c_str(), &endptr, 10);
if (longValue < INT_MIN || longValue > INT_MAX) {
    // Handle overflow
}
```

### 2. **Floating-Point Comparison Issues**
```cpp
// PROBLEM: Direct equality comparison
if (value == static_cast<int>(value))  // May fail due to precision

// BETTER: Use epsilon comparison (for more complex cases)
const double epsilon = 1e-9;
if (std::abs(value - std::round(value)) < epsilon)
```

### 3. **Non-Displayable Character Confusion**
```cpp
// ASCII Control Characters (0-31, 127) are non-displayable
// Our implementation correctly identifies these:
if (value <= 31 || value == 127) {
    std::cout << "char: Non displayable" << std::endl;
}
```

### 4. **Pseudo-Literal Case Sensitivity**
```cpp
// PROBLEM: Case variations not handled
"NaNf", "NANF", "Inf"  // Not recognized

// SOLUTION: Stick to exact IEEE 754 representations
"nanf", "nan", "+inff", "-inf"  // Only these are valid
```

---

## 📖 Related C++ Features and Standards

### IEEE 754 Floating-Point Standard:
- **Binary representation**: How computers store floats/doubles
- **Special values**: NaN, infinity representations
- **Precision limits**: Single vs double precision ranges

### C Standard Library Functions:
- **String conversion**: `strtol()`, `atof()`, `atoi()`
- **Character classification**: `std::isdigit()`, `std::isprint()`
- **Floating-point utilities**: `std::isnan()`, `std::isinf()`

### C++ Type System:
- **Static casting**: Explicit type conversions
- **Numeric limits**: `std::numeric_limits<T>`
- **Type traits**: Foundation for template metaprogramming

---

## 🎯 Practical Applications

This conversion pattern is commonly used in:

1. **Configuration Systems**: Parsing config files with mixed types
2. **Command-Line Parsers**: Converting string arguments to appropriate types
3. **Serialization Libraries**: Converting between string and binary representations
4. **Database Interfaces**: Converting between SQL strings and C++ types
5. **Network Protocols**: Parsing text-based protocols (HTTP, JSON)
6. **Compiler/Interpreter Design**: Lexical analysis and type inference
7. **Scientific Computing**: Reading experimental data from text files

---

## 🏆 Mastery Indicators

You've mastered this exercise when you can:

1. **Explain** why static classes are used for utility functions
2. **Implement** robust string parsing with proper error handling
3. **Handle** floating-point special values correctly
4. **Design** comprehensive type detection algorithms
5. **Apply** appropriate casting strategies for type conversion
6. **Validate** input formats with proper boundary checking
7. **Choose** between different error handling strategies appropriately

---

*This exercise introduces fundamental concepts in type systems, string parsing, and utility class design. These patterns form the foundation for more advanced topics like serialization, reflection, and template metaprogramming in later modules.*

````
