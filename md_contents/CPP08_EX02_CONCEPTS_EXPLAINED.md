# CPP08 Ex02 - MutantStack Iterator-Enabled Stack

## Overview
This exercise demonstrates advanced template programming by creating a stack container that maintains stack semantics while providing iterator access to its underlying elements, showcasing the power of inheritance and STL adapter customization.

## Key Concepts Learned

### 1. Template Class Inheritance
```cpp
template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
```
- **Template Inheritance**: Inherits from STL's std::stack template
- **Template Parameters**: T for element type, Container for underlying storage
- **Default Parameter**: Uses std::deque as default underlying container
- **Public Inheritance**: Maintains is-a relationship with std::stack

### 2. STL Adapter Customization
```cpp
typedef typename Container::iterator iterator;
typedef typename Container::const_iterator const_iterator;
```
- **Iterator Type Aliases**: Exposes underlying container's iterator types
- **STL Compatibility**: Follows STL naming conventions and patterns
- **Template Dependent Types**: Uses typename for dependent type resolution

### 3. Protected Member Access
```cpp
iterator begin() { return this->c.begin(); }
iterator end() { return this->c.end(); }
```
- **Protected Member Access**: Accesses std::stack's protected member 'c'
- **Iterator Interface**: Provides standard STL iterator interface
- **Encapsulation**: Maintains stack interface while adding iteration

## Advanced Template Programming

### Template Method Implementation
- **Header-Only**: All template methods implemented in header for C++98
- **Type Deduction**: Compiler resolves template types automatically
- **Multiple Specialization**: Works with different underlying containers

### Iterator Type System
```cpp
// All standard iterator types supported
typedef typename Container::reverse_iterator reverse_iterator;
typedef typename Container::const_reverse_iterator const_reverse_iterator;
```
- **Bidirectional Access**: Forward and reverse iteration
- **Const Correctness**: Separate const and non-const iterator types
- **STL Compliance**: Full STL iterator interface support

### Container Flexibility
- **std::deque**: Default container (efficient push/pop both ends)
- **std::vector**: Can be used for random access efficiency
- **std::list**: Could be used for constant time insertion/deletion
- **Template Parameter**: Any container meeting requirements

## Design Patterns Applied

### Adapter Pattern Enhancement
1. **STL Adapter**: std::stack is already an adapter pattern
2. **Feature Addition**: Adds iteration without breaking stack semantics
3. **Interface Extension**: Extends functionality while maintaining compatibility
4. **Transparent Enhancement**: Client code works with both interfaces

### Template Specialization Strategy
1. **Generic Implementation**: Works with any compliant container
2. **Type Safety**: Template ensures compile-time type checking
3. **Performance**: No runtime overhead for abstraction
4. **Flexibility**: Easy to change underlying container

## Implementation Details

### Orthodox Canonical Form
```cpp
MutantStack();                              // Default constructor
MutantStack(const MutantStack& other);      // Copy constructor
MutantStack& operator=(const MutantStack&); // Assignment operator
~MutantStack();                             // Destructor
```
- **Rule of Three**: Properly implements all required methods
- **Base Class Delegation**: Leverages std::stack's implementation
- **Resource Management**: Automatic through base class

### Iterator Implementation Strategy
```cpp
iterator begin() { return this->c.begin(); }
const_iterator begin() const { return this->c.begin(); }
```
- **Const Overloading**: Separate const and non-const versions
- **Direct Delegation**: Forwards to underlying container's iterators
- **Protected Access**: Uses std::stack's protected container member

### STL Algorithm Compatibility
- **std::find**: Can search through stack elements
- **std::count**: Can count occurrences in stack
- **std::for_each**: Can apply operations to all elements
- **Custom Algorithms**: Any algorithm accepting iterators works

## Practical Applications

### Stack with Inspection
- **Debug Capability**: Iterate through stack for debugging
- **Data Analysis**: Examine stack contents without modification
- **Serialization**: Iterate for saving/loading stack state
- **Algorithm Application**: Apply STL algorithms to stack data

### Performance Characteristics
- **Stack Operations**: O(1) for push/pop (unchanged from std::stack)
- **Iterator Operations**: O(1) for begin/end, O(n) for traversal
- **Memory Overhead**: No additional memory beyond base class
- **Compiler Optimization**: Template instantiation optimizes away abstractions

## Testing Scenarios Covered

### Core Functionality
- **Subject Example**: Exact replication of exercise requirements
- **std::list Comparison**: Demonstrates equivalent behavior
- **Iterator Operations**: Full forward/reverse iteration testing

### Advanced Features
- **STL Algorithm Integration**: Tests with std::find, std::count, modification
- **Copy Semantics**: Verifies proper copy constructor and assignment
- **Container Variations**: Tests with different underlying containers
- **Stack Operations**: Validates all standard stack functionality

### Edge Cases
- **Empty Stack**: Proper iterator behavior on empty containers
- **Single Element**: Iterator operations with minimal data
- **Large Data**: Performance with significant element counts
- **Const Correctness**: Proper const iterator behavior

## STL Integration Excellence

### Iterator Concept Compliance
```cpp
// All required iterator operations supported
++it; --it; *it; it == other; it != other;
```
- **Input Iterator**: Supports reading and forward movement
- **Output Iterator**: Supports writing (non-const iterators)
- **Forward Iterator**: Supports multiple passes
- **Bidirectional Iterator**: Supports reverse movement

### Algorithm Library Support
- **Searching**: std::find, std::search, std::binary_search (if sorted)
- **Counting**: std::count, std::count_if
- **Modification**: std::transform, std::for_each, std::replace
- **Sorting**: std::sort (changes stack semantics but possible)

### Container Adapter Benefits
- **Familiar Interface**: Maintains std::stack's well-known API
- **Extended Capability**: Adds iteration without breaking existing code
- **Template Flexibility**: Works with any suitable underlying container
- **Performance**: No performance penalty for added functionality

## Design Philosophy

### Principle of Least Surprise
1. **Stack Semantics**: Maintains expected stack behavior
2. **STL Conventions**: Follows established STL patterns
3. **Iterator Interface**: Standard iterator naming and behavior
4. **Template Usage**: Conventional template parameter patterns

### Separation of Concerns
1. **Stack Responsibility**: Maintains LIFO operations
2. **Iterator Responsibility**: Provides traversal capability
3. **Container Responsibility**: Handles actual data storage
4. **Template Responsibility**: Enables type flexibility

## Compilation and Testing

### Build Process
```bash
make        # Compile with École 42 flags
make test   # Build and run comprehensive tests
make clean  # Remove object files
make fclean # Remove all generated files
```

### École 42 Compliance
- **C++98 Standard**: Full compatibility with required standard
- **Template Syntax**: Uses C++98 template syntax throughout
- **Header Implementation**: Template methods in header as required
- **Orthodox Form**: Proper canonical class implementation

This exercise masterfully demonstrates how to extend STL containers through inheritance and template programming, creating a powerful hybrid that maintains type safety, performance, and STL compatibility while adding new functionality. The MutantStack shows how careful design can enhance existing abstractions without compromising their core benefits.
