#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>
#include "easyfind.hpp"

void testVector() {
    std::cout << "=== Testing with std::vector ===" << std::endl;
    
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    std::cout << "Vector contents: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test successful find
    try {
        std::vector<int>::iterator result = easyfind(vec, 3);
        std::cout << "Found value 3 at position: " << std::distance(vec.begin(), result) << std::endl;
        std::cout << "Value at found position: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test unsuccessful find
    try {
        std::vector<int>::iterator result = easyfind(vec, 10);
        std::cout << "Found value 10 at position: " << std::distance(vec.begin(), result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error for value 10: " << e.what() << std::endl;
    }
}

void testList() {
    std::cout << "\n=== Testing with std::list ===" << std::endl;
    
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    lst.push_back(50);
    
    std::cout << "List contents: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test successful find
    try {
        std::list<int>::iterator result = easyfind(lst, 30);
        std::cout << "Found value 30 in list" << std::endl;
        std::cout << "Value at found position: " << *result << std::endl;
        
        // Test iterator functionality
        ++result;
        if (result != lst.end()) {
            std::cout << "Next value after found element: " << *result << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test unsuccessful find
    try {
        std::list<int>::iterator result = easyfind(lst, 100);
        std::cout << "Found value 100: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error for value 100: " << e.what() << std::endl;
    }
}

void testDeque() {
    std::cout << "\n=== Testing with std::deque ===" << std::endl;
    
    std::deque<int> deq;
    deq.push_back(100);
    deq.push_back(200);
    deq.push_back(300);
    deq.push_front(50);  // Add to front
    
    std::cout << "Deque contents: ";
    for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test finding element at different positions
    try {
        std::deque<int>::iterator result = easyfind(deq, 50);
        std::cout << "Found value 50 at beginning" << std::endl;
        std::cout << "Value: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    try {
        std::deque<int>::iterator result = easyfind(deq, 300);
        std::cout << "Found value 300 at end" << std::endl;
        std::cout << "Value: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testEmptyContainers() {
    std::cout << "\n=== Testing with empty containers ===" << std::endl;
    
    std::vector<int> emptyVec;
    std::list<int> emptyList;
    
    std::cout << "Testing empty vector:" << std::endl;
    try {
        std::vector<int>::iterator result = easyfind(emptyVec, 1);
        std::cout << "Found value in empty vector: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error for empty vector: " << e.what() << std::endl;
    }
    
    std::cout << "Testing empty list:" << std::endl;
    try {
        std::list<int>::iterator result = easyfind(emptyList, 1);
        std::cout << "Found value in empty list: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error for empty list: " << e.what() << std::endl;
    }
}

void testDuplicateValues() {
    std::cout << "\n=== Testing with duplicate values ===" << std::endl;
    
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(2);  // Duplicate
    vec.push_back(4);
    vec.push_back(2);  // Another duplicate
    
    std::cout << "Vector with duplicates: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    try {
        std::vector<int>::iterator result = easyfind(vec, 2);
        int position = std::distance(vec.begin(), result);
        std::cout << "Found first occurrence of value 2 at position: " << position << std::endl;
        std::cout << "Value: " << *result << std::endl;
        
        // Verify it's the first occurrence
        if (position == 1) {
            std::cout << "Correctly found FIRST occurrence" << std::endl;
        } else {
            std::cout << "ERROR: Should have found first occurrence at position 1" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testLargeContainer() {
    std::cout << "\n=== Testing with large container ===" << std::endl;
    
    std::vector<int> largeVec;
    
    // Fill with values 0 to 999
    for (int i = 0; i < 1000; ++i) {
        largeVec.push_back(i);
    }
    
    std::cout << "Created vector with 1000 elements (0-999)" << std::endl;
    
    // Test finding element at beginning
    try {
        std::vector<int>::iterator result = easyfind(largeVec, 0);
        std::cout << "Found value 0 at position: " << std::distance(largeVec.begin(), result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test finding element in middle
    try {
        std::vector<int>::iterator result = easyfind(largeVec, 500);
        std::cout << "Found value 500 at position: " << std::distance(largeVec.begin(), result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test finding element at end
    try {
        std::vector<int>::iterator result = easyfind(largeVec, 999);
        std::cout << "Found value 999 at position: " << std::distance(largeVec.begin(), result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test non-existent element
    try {
        std::vector<int>::iterator result = easyfind(largeVec, 1000);
        std::cout << "Found value 1000: " << *result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error for value 1000: " << e.what() << std::endl;
    }
}

void testIteratorUsage() {
    std::cout << "\n=== Testing iterator usage ===" << std::endl;
    
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);
    vec.push_back(20);
    vec.push_back(25);
    
    try {
        std::vector<int>::iterator result = easyfind(vec, 15);
        std::cout << "Found value 15" << std::endl;
        
        // Test iterator operations
        std::cout << "Value at found position: " << *result << std::endl;
        
        // Move iterator forward
        ++result;
        if (result != vec.end()) {
            std::cout << "Next value: " << *result << std::endl;
        }
        
        // Move iterator backward
        --result;
        std::cout << "Back to found value: " << *result << std::endl;
        
        // Move to previous value
        --result;
        std::cout << "Previous value: " << *result << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== CPP08 Ex00 - Easy Find Function Template Tests ===" << std::endl;
    
    try {
        testVector();
        testList();
        testDeque();
        testEmptyContainers();
        testDuplicateValues();
        testLargeContainer();
        testIteratorUsage();
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\nUnexpected exception during testing: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
