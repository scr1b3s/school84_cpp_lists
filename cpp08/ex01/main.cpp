#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

void testBasicFunctionality() {
    std::cout << "=== Testing Basic Functionality ===" << std::endl;
    
    try {
        Span sp(5);
        
        std::cout << "Created span with max size: " << sp.maxSize() << std::endl;
        std::cout << "Initial size: " << sp.size() << std::endl;
        std::cout << "Is empty: " << (sp.isEmpty() ? "Yes" : "No") << std::endl;
        
        // Add some numbers
        sp.addNumber(5);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        std::cout << "After adding 5 numbers:" << std::endl;
        std::cout << "Size: " << sp.size() << std::endl;
        std::cout << "Is full: " << (sp.isFull() ? "Yes" : "No") << std::endl;
        
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void testExceptions() {
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    
    // Test SpanFullException
    std::cout << "Testing SpanFullException:" << std::endl;
    try {
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3); // This should throw
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    // Test SpanTooSmallException with empty span
    std::cout << "\nTesting SpanTooSmallException (empty span):" << std::endl;
    try {
        Span sp(5);
        sp.shortestSpan(); // Should throw
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    // Test SpanTooSmallException with one element
    std::cout << "\nTesting SpanTooSmallException (one element):" << std::endl;
    try {
        Span sp(5);
        sp.addNumber(42);
        sp.longestSpan(); // Should throw
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

void testCopyConstructorAndAssignment() {
    std::cout << "\n=== Testing Copy Constructor and Assignment ===" << std::endl;
    
    try {
        // Create original span
        Span original(5);
        original.addNumber(1);
        original.addNumber(10);
        original.addNumber(5);
        
        std::cout << "Original span - Size: " << original.size() << ", Shortest: " << original.shortestSpan() << ", Longest: " << original.longestSpan() << std::endl;
        
        // Test copy constructor
        Span copy1(original);
        std::cout << "Copy constructor - Size: " << copy1.size() << ", Shortest: " << copy1.shortestSpan() << ", Longest: " << copy1.longestSpan() << std::endl;
        
        // Test assignment operator
        Span copy2(10);
        copy2 = original;
        std::cout << "Assignment operator - Size: " << copy2.size() << ", Shortest: " << copy2.shortestSpan() << ", Longest: " << copy2.longestSpan() << std::endl;
        
        // Verify independence
        original.addNumber(20);
        std::cout << "After modifying original:" << std::endl;
        std::cout << "Original size: " << original.size() << std::endl;
        std::cout << "Copy1 size: " << copy1.size() << std::endl;
        std::cout << "Copy2 size: " << copy2.size() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void testRangeAddition() {
    std::cout << "\n=== Testing Range Addition ===" << std::endl;
    
    // Test with std::vector
    std::cout << "Testing with std::vector:" << std::endl;
    try {
        Span sp(10);
        
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5);
        
        sp.addRange(vec.begin(), vec.end());
        std::cout << "Added vector range, size: " << sp.size() << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test with std::list
    std::cout << "\nTesting with std::list:" << std::endl;
    try {
        Span sp(15);
        
        std::list<int> lst;
        lst.push_back(10);
        lst.push_back(30);
        lst.push_back(20);
        lst.push_back(40);
        
        sp.addRange(lst.begin(), lst.end());
        std::cout << "Added list range, size: " << sp.size() << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test range addition overflow
    std::cout << "\nTesting range addition overflow:" << std::endl;
    try {
        Span sp(3);
        sp.addNumber(1);
        
        std::vector<int> vec;
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5); // This should cause overflow
        
        sp.addRange(vec.begin(), vec.end());
        
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

void testLargeSpan() {
    std::cout << "\n=== Testing Large Span (10000 elements) ===" << std::endl;
    
    try {
        Span sp(10000);
        
        // Generate random numbers
        std::srand(static_cast<unsigned int>(std::time(0)));
        
        std::vector<int> randomNumbers;
        for (int i = 0; i < 10000; ++i) {
            randomNumbers.push_back(std::rand() % 100000);
        }
        
        std::cout << "Generated 10000 random numbers" << std::endl;
        
        // Add using range method for efficiency
        sp.addRange(randomNumbers.begin(), randomNumbers.end());
        
        std::cout << "Added to span, size: " << sp.size() << std::endl;
        std::cout << "Calculating spans..." << std::endl;
        
        int shortest = sp.shortestSpan();
        int longest = sp.longestSpan();
        
        std::cout << "Shortest span: " << shortest << std::endl;
        std::cout << "Longest span: " << longest << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Test with identical numbers
    std::cout << "Testing with identical numbers:" << std::endl;
    try {
        Span sp(5);
        sp.addNumber(42);
        sp.addNumber(42);
        sp.addNumber(42);
        
        std::cout << "Shortest span with identical numbers: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span with identical numbers: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test with negative numbers
    std::cout << "\nTesting with negative numbers:" << std::endl;
    try {
        Span sp(5);
        sp.addNumber(-10);
        sp.addNumber(-5);
        sp.addNumber(0);
        sp.addNumber(5);
        sp.addNumber(10);
        
        std::cout << "Shortest span with negatives: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span with negatives: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test with extreme values
    std::cout << "\nTesting with extreme values:" << std::endl;
    try {
        Span sp(3);
        sp.addNumber(-2147483648); // INT_MIN (approximately)
        sp.addNumber(0);
        sp.addNumber(2147483647);  // INT_MAX (approximately)
        
        std::cout << "Shortest span with extremes: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span with extremes: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void testSubjectExample() {
    std::cout << "\n=== Testing Subject Example ===" << std::endl;
    
    try {
        Span sp = Span(5);
        
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        std::cout << "Subject example results:" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== CPP08 Ex01 - Span Class Comprehensive Tests ===" << std::endl;
    
    try {
        testBasicFunctionality();
        testExceptions();
        testCopyConstructorAndAssignment();
        testRangeAddition();
        testLargeSpan();
        testEdgeCases();
        testSubjectExample();
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\nUnexpected exception during testing: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
