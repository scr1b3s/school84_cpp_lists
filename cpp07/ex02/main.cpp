#include <iostream>
#include <string>
#include "Array.hpp"

// Test function to demonstrate default initialization
void testDefaultInitialization() {
    std::cout << "=== Testing Default Initialization ===" << std::endl;
    
    // Test the tip from subject: int * a = new int(); then display *a
    std::cout << "Testing new int() default initialization:" << std::endl;
    int* a = new int();
    std::cout << "*a = " << *a << " (should be 0)" << std::endl;
    delete a;
    
    // Test with our Array
    std::cout << "\nTesting Array<int> default initialization:" << std::endl;
    Array<int> intArray(5);
    std::cout << "Array<int>(5) elements: ";
    for (unsigned int i = 0; i < intArray.size(); i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << "(should be all zeros)" << std::endl;
    
    std::cout << "\nTesting Array<std::string> default initialization:" << std::endl;
    Array<std::string> stringArray(3);
    std::cout << "Array<std::string>(3) elements: ";
    for (unsigned int i = 0; i < stringArray.size(); i++) {
        std::cout << "\"" << stringArray[i] << "\" ";
    }
    std::cout << "(should be empty strings)" << std::endl;
}

void testConstructors() {
    std::cout << "\n=== Testing Constructors ===" << std::endl;
    
    // Test default constructor
    std::cout << "1. Default constructor:" << std::endl;
    Array<int> emptyArray;
    std::cout << "Empty array size: " << emptyArray.size() << std::endl;
    
    // Test parameterized constructor
    std::cout << "\n2. Parameterized constructor:" << std::endl;
    Array<int> intArray(10);
    std::cout << "Array<int>(10) size: " << intArray.size() << std::endl;
    
    // Initialize some values
    for (unsigned int i = 0; i < intArray.size(); i++) {
        intArray[i] = i * 10;
    }
    
    std::cout << "Values: ";
    for (unsigned int i = 0; i < intArray.size(); i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    
    // Test copy constructor
    std::cout << "\n3. Copy constructor:" << std::endl;
    Array<int> copiedArray(intArray);
    std::cout << "Copied array size: " << copiedArray.size() << std::endl;
    std::cout << "Copied values: ";
    for (unsigned int i = 0; i < copiedArray.size(); i++) {
        std::cout << copiedArray[i] << " ";
    }
    std::cout << std::endl;
    
    // Modify original to test deep copy
    std::cout << "\n4. Testing deep copy (modifying original):" << std::endl;
    intArray[0] = 999;
    std::cout << "Original[0] after modification: " << intArray[0] << std::endl;
    std::cout << "Copied[0] after original modification: " << copiedArray[0] << std::endl;
    std::cout << "(Should be different - proves deep copy)" << std::endl;
}

void testAssignmentOperator() {
    std::cout << "\n=== Testing Assignment Operator ===" << std::endl;
    
    Array<int> array1(5);
    Array<int> array2(3);
    
    // Initialize arrays
    for (unsigned int i = 0; i < array1.size(); i++) {
        array1[i] = i + 1;
    }
    
    for (unsigned int i = 0; i < array2.size(); i++) {
        array2[i] = (i + 1) * 100;
    }
    
    std::cout << "Before assignment:" << std::endl;
    std::cout << "Array1 (size " << array1.size() << "): ";
    for (unsigned int i = 0; i < array1.size(); i++) {
        std::cout << array1[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Array2 (size " << array2.size() << "): ";
    for (unsigned int i = 0; i < array2.size(); i++) {
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;
    
    // Test assignment
    array2 = array1;
    
    std::cout << "\nAfter array2 = array1:" << std::endl;
    std::cout << "Array1 (size " << array1.size() << "): ";
    for (unsigned int i = 0; i < array1.size(); i++) {
        std::cout << array1[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Array2 (size " << array2.size() << "): ";
    for (unsigned int i = 0; i < array2.size(); i++) {
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;
    
    // Test deep copy in assignment
    std::cout << "\nTesting deep copy in assignment:" << std::endl;
    array1[0] = 777;
    std::cout << "Array1[0] after modification: " << array1[0] << std::endl;
    std::cout << "Array2[0] after array1 modification: " << array2[0] << std::endl;
    std::cout << "(Should be different - proves deep copy)" << std::endl;
    
    // Test self-assignment
    std::cout << "\nTesting self-assignment:" << std::endl;
    array1 = array1;
    std::cout << "Array1 size after self-assignment: " << array1.size() << std::endl;
    std::cout << "Array1[0] after self-assignment: " << array1[0] << std::endl;
    std::cout << "(Should be unchanged)" << std::endl;
}

void testSubscriptOperator() {
    std::cout << "\n=== Testing Subscript Operator ===" << std::endl;
    
    Array<std::string> stringArray(4);
    
    // Test writing through subscript operator
    stringArray[0] = "Hello";
    stringArray[1] = "World";
    stringArray[2] = "Template";
    stringArray[3] = "Programming";
    
    std::cout << "String array contents:" << std::endl;
    for (unsigned int i = 0; i < stringArray.size(); i++) {
        std::cout << "stringArray[" << i << "] = \"" << stringArray[i] << "\"" << std::endl;
    }
    
    // Test const version
    const Array<std::string>& constRef = stringArray;
    std::cout << "\nAccessing through const reference:" << std::endl;
    std::cout << "constRef[1] = \"" << constRef[1] << "\"" << std::endl;
}

void testExceptions() {
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    
    Array<int> testArray(5);
    
    // Test valid access
    std::cout << "Testing valid access:" << std::endl;
    try {
        testArray[0] = 42;
        testArray[4] = 84;
        std::cout << "testArray[0] = " << testArray[0] << std::endl;
        std::cout << "testArray[4] = " << testArray[4] << std::endl;
        std::cout << "Valid access successful" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
    
    // Test out of bounds access
    std::cout << "\nTesting out of bounds access:" << std::endl;
    try {
        std::cout << "Attempting to access testArray[5] (size is 5)..." << std::endl;
        int value = testArray[5];  // Should throw exception
        std::cout << "ERROR: Should have thrown exception! Got value: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught correctly: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "Attempting to access testArray[100]..." << std::endl;
        int value = testArray[100];  // Should throw exception
        std::cout << "ERROR: Should have thrown exception! Got value: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught correctly: " << e.what() << std::endl;
    }
    
    // Test with empty array
    std::cout << "\nTesting with empty array:" << std::endl;
    Array<int> emptyArray;
    try {
        std::cout << "Attempting to access emptyArray[0] (size is 0)..." << std::endl;
        int value = emptyArray[0];  // Should throw exception
        std::cout << "ERROR: Should have thrown exception! Got value: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught correctly: " << e.what() << std::endl;
    }
}

void testDifferentTypes() {
    std::cout << "\n=== Testing Different Types ===" << std::endl;
    
    // Test with int
    std::cout << "1. Testing with int:" << std::endl;
    Array<int> intArray(3);
    intArray[0] = 10;
    intArray[1] = 20;
    intArray[2] = 30;
    std::cout << "Int array: ";
    for (unsigned int i = 0; i < intArray.size(); i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    
    // Test with double
    std::cout << "\n2. Testing with double:" << std::endl;
    Array<double> doubleArray(3);
    doubleArray[0] = 3.14;
    doubleArray[1] = 2.71;
    doubleArray[2] = 1.41;
    std::cout << "Double array: ";
    for (unsigned int i = 0; i < doubleArray.size(); i++) {
        std::cout << doubleArray[i] << " ";
    }
    std::cout << std::endl;
    
    // Test with char
    std::cout << "\n3. Testing with char:" << std::endl;
    Array<char> charArray(5);
    charArray[0] = 'H';
    charArray[1] = 'e';
    charArray[2] = 'l';
    charArray[3] = 'l';
    charArray[4] = 'o';
    std::cout << "Char array: ";
    for (unsigned int i = 0; i < charArray.size(); i++) {
        std::cout << charArray[i];
    }
    std::cout << std::endl;
    
    // Test with string
    std::cout << "\n4. Testing with std::string:" << std::endl;
    Array<std::string> stringArray(2);
    stringArray[0] = "Template";
    stringArray[1] = "Mastery";
    std::cout << "String array: ";
    for (unsigned int i = 0; i < stringArray.size(); i++) {
        std::cout << "\"" << stringArray[i] << "\" ";
    }
    std::cout << std::endl;
}

void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Test zero-size array
    std::cout << "1. Zero-size array:" << std::endl;
    Array<int> zeroArray(0);
    std::cout << "Zero array size: " << zeroArray.size() << std::endl;
    
    // Test large array
    std::cout << "\n2. Large array:" << std::endl;
    Array<int> largeArray(1000);
    std::cout << "Large array size: " << largeArray.size() << std::endl;
    largeArray[0] = 1;
    largeArray[999] = 999;
    std::cout << "largeArray[0] = " << largeArray[0] << std::endl;
    std::cout << "largeArray[999] = " << largeArray[999] << std::endl;
    
    // Test multiple assignments
    std::cout << "\n3. Multiple assignments:" << std::endl;
    Array<int> a(2), b(3), c(4);
    a[0] = 1; a[1] = 2;
    b[0] = 10; b[1] = 20; b[2] = 30;
    c[0] = 100; c[1] = 200; c[2] = 300; c[3] = 400;
    
    std::cout << "Before assignments:" << std::endl;
    std::cout << "a size: " << a.size() << ", b size: " << b.size() << ", c size: " << c.size() << std::endl;
    
    a = b = c;  // Chain assignment
    
    std::cout << "After a = b = c:" << std::endl;
    std::cout << "a size: " << a.size() << ", b size: " << b.size() << ", c size: " << c.size() << std::endl;
    std::cout << "All should be size 4 with same values" << std::endl;
}

int main() {
    std::cout << "=== CPP07 Ex02 - Array Class Template Tests ===" << std::endl;
    
    try {
        testDefaultInitialization();
        testConstructors();
        testAssignmentOperator();
        testSubscriptOperator();
        testExceptions();
        testDifferentTypes();
        testEdgeCases();
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\nUnexpected exception during testing: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
