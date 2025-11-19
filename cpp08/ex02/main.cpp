#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "MutantStack.hpp"

void testSubjectExample() {
    std::cout << "=== Testing Subject Example ===" << std::endl;
    
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Top element: " << mstack.top() << std::endl;
    
    mstack.pop();
    
    std::cout << "Size after pop: " << mstack.size() << std::endl;
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Stack contents (using iterators):" << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    ++it;
    --it;
    while (it != ite) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

void testComparisonWithList() {
    std::cout << "\n=== Comparing MutantStack with std::list ===" << std::endl;
    
    // Using MutantStack
    std::cout << "Using MutantStack:" << std::endl;
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Top element: " << mstack.top() << std::endl;
    
    mstack.pop();
    
    std::cout << "Size after pop: " << mstack.size() << std::endl;
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "MutantStack contents: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Using std::list for comparison
    std::cout << "\nUsing std::list:" << std::endl;
    std::list<int> lst;
    
    lst.push_back(5);
    lst.push_back(17);
    
    std::cout << "Back element: " << lst.back() << std::endl;
    
    lst.pop_back();
    
    std::cout << "Size after pop_back: " << lst.size() << std::endl;
    
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    
    std::cout << "List contents: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testIteratorFunctionality() {
    std::cout << "\n=== Testing Iterator Functionality ===" << std::endl;
    
    MutantStack<int> mstack;
    
    // Add some elements
    for (int i = 1; i <= 10; ++i) {
        mstack.push(i * 10);
    }
    
    std::cout << "Stack size: " << mstack.size() << std::endl;
    
    // Test forward iteration
    std::cout << "Forward iteration: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test reverse iteration
    std::cout << "Reverse iteration: ";
    for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
    
    // Test const iteration
    const MutantStack<int>& const_ref = mstack;
    std::cout << "Const forward iteration: ";
    for (MutantStack<int>::const_iterator cit = const_ref.begin(); cit != const_ref.end(); ++cit) {
        std::cout << *cit << " ";
    }
    std::cout << std::endl;
    
    // Test const reverse iteration
    std::cout << "Const reverse iteration: ";
    for (MutantStack<int>::const_reverse_iterator crit = const_ref.rbegin(); crit != const_ref.rend(); ++crit) {
        std::cout << *crit << " ";
    }
    std::cout << std::endl;
}

void testIteratorOperations() {
    std::cout << "\n=== Testing Iterator Operations ===" << std::endl;
    
    MutantStack<int> mstack;
    
    for (int i = 1; i <= 5; ++i) {
        mstack.push(i);
    }
    
    std::cout << "Stack contents: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test iterator arithmetic
    MutantStack<int>::iterator it = mstack.begin();
    std::cout << "First element: " << *it << std::endl;
    
    ++it;
    std::cout << "Second element: " << *it << std::endl;
    
    --it;
    std::cout << "Back to first: " << *it << std::endl;
    
    // Test iterator modification
    std::cout << "Modifying elements through iterators:" << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        *it *= 10;
    }
    
    std::cout << "Modified stack: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testSTLAlgorithms() {
    std::cout << "\n=== Testing STL Algorithms ===" << std::endl;
    
    MutantStack<int> mstack;
    
    mstack.push(3);
    mstack.push(1);
    mstack.push(4);
    mstack.push(1);
    mstack.push(5);
    mstack.push(9);
    mstack.push(2);
    
    std::cout << "Original stack: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test std::find
    MutantStack<int>::iterator found = std::find(mstack.begin(), mstack.end(), 5);
    if (found != mstack.end()) {
        std::cout << "Found value 5 in stack" << std::endl;
    }
    
    // Test std::count
    int count = std::count(mstack.begin(), mstack.end(), 1);
    std::cout << "Number of 1s in stack: " << count << std::endl;
    
    // Test std::for_each (with function object)
    std::cout << "Doubling all values: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        *it *= 2;
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "\n=== Testing Copy Constructor and Assignment ===" << std::endl;
    
    MutantStack<int> original;
    
    original.push(10);
    original.push(20);
    original.push(30);
    
    std::cout << "Original stack: ";
    for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test copy constructor
    MutantStack<int> copy1(original);
    std::cout << "Copy constructor result: ";
    for (MutantStack<int>::iterator it = copy1.begin(); it != copy1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test assignment operator
    MutantStack<int> copy2;
    copy2 = original;
    std::cout << "Assignment operator result: ";
    for (MutantStack<int>::iterator it = copy2.begin(); it != copy2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test independence
    original.push(40);
    std::cout << "After modifying original:" << std::endl;
    std::cout << "Original size: " << original.size() << std::endl;
    std::cout << "Copy1 size: " << copy1.size() << std::endl;
    std::cout << "Copy2 size: " << copy2.size() << std::endl;
}

void testDifferentContainers() {
    std::cout << "\n=== Testing Different Underlying Containers ===" << std::endl;
    
    // Default (deque)
    std::cout << "Using default container (deque):" << std::endl;
    MutantStack<int> default_stack;
    default_stack.push(1);
    default_stack.push(2);
    default_stack.push(3);
    
    std::cout << "Contents: ";
    for (MutantStack<int>::iterator it = default_stack.begin(); it != default_stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // With vector
    std::cout << "Using vector container:" << std::endl;
    MutantStack<int, std::vector<int> > vector_stack;
    vector_stack.push(10);
    vector_stack.push(20);
    vector_stack.push(30);
    
    std::cout << "Contents: ";
    for (MutantStack<int, std::vector<int> >::iterator it = vector_stack.begin(); it != vector_stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testStackOperations() {
    std::cout << "\n=== Testing Stack Operations ===" << std::endl;
    
    MutantStack<int> mstack;
    
    std::cout << "Initial empty: " << (mstack.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Initial size: " << mstack.size() << std::endl;
    
    // Push operations
    std::cout << "Pushing elements 1, 2, 3, 4, 5" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        mstack.push(i);
        std::cout << "Pushed " << i << ", size now: " << mstack.size() << ", top: " << mstack.top() << std::endl;
    }
    
    // Pop operations
    std::cout << "Popping elements:" << std::endl;
    while (!mstack.empty()) {
        std::cout << "Popping " << mstack.top() << ", size before: " << mstack.size();
        mstack.pop();
        std::cout << ", size after: " << mstack.size() << std::endl;
    }
    
    std::cout << "Final empty: " << (mstack.empty() ? "Yes" : "No") << std::endl;
}

int main() {
    std::cout << "=== CPP08 Ex02 - MutantStack Comprehensive Tests ===" << std::endl;
    
    try {
        testSubjectExample();
        testComparisonWithList();
        testIteratorFunctionality();
        testIteratorOperations();
        testSTLAlgorithms();
        testCopyAndAssignment();
        testDifferentContainers();
        testStackOperations();
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\nUnexpected exception during testing: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
