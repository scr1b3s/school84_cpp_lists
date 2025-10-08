#include <iostream>
#include <string>
#include "iter.hpp"

// Test functions for different types and scenarios

// Simple print function for integers
void printInt(int x) {
    std::cout << x << " ";
}

// Print function for strings
void printString(const std::string& str) {
    std::cout << "\"" << str << "\" ";
}

// Function that modifies elements (non-const)
void doubleValue(int& x) {
    x *= 2;
}

// Function that works with const elements
void printConstInt(const int& x) {
    std::cout << x << " ";
}

// Template function to demonstrate function template as parameter
template<typename T>
void printElement(const T& element) {
    std::cout << element << " ";
}

// Function to increment values
void increment(int& x) {
    x++;
}

// Function to print characters
void printChar(char c) {
    std::cout << c;
}

// Function to uppercase characters (modifying)
void toUppercase(char& c) {
    if (c >= 'a' && c <= 'z') {
        c = c - 'a' + 'A';
    }
}

int main() {
    std::cout << "=== CPP07 Ex01 - Iter Function Template Tests ===" << std::endl;

    // Test 1: Basic integer array with print function
    std::cout << "\n1. Integer array with print function:" << std::endl;
    int numbers[] = {1, 2, 3, 4, 5};
    int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
    
    std::cout << "Original array: ";
    ::iter(numbers, numbersSize, printInt);
    std::cout << std::endl;

    // Test 2: Modifying array elements
    std::cout << "\n2. Modifying array elements (doubling values):" << std::endl;
    ::iter(numbers, numbersSize, doubleValue);
    std::cout << "After doubling: ";
    ::iter(numbers, numbersSize, printInt);
    std::cout << std::endl;

    // Test 3: Using const reference function
    std::cout << "\n3. Using const reference function:" << std::endl;
    const int constNumbers[] = {10, 20, 30, 40, 50};
    int constSize = sizeof(constNumbers) / sizeof(constNumbers[0]);
    
    std::cout << "Const array: ";
    ::iter(constNumbers, constSize, printConstInt);
    std::cout << std::endl;

    // Test 4: String array
    std::cout << "\n4. String array:" << std::endl;
    std::string words[] = {"Hello", "World", "Template", "Programming"};
    int wordsSize = sizeof(words) / sizeof(words[0]);
    
    std::cout << "String array: ";
    ::iter(words, wordsSize, printString);
    std::cout << std::endl;

    // Test 5: Using template function as parameter
    std::cout << "\n5. Using template function as parameter:" << std::endl;
    float floats[] = {1.1f, 2.2f, 3.3f, 4.4f};
    int floatsSize = sizeof(floats) / sizeof(floats[0]);
    
    std::cout << "Float array: ";
    ::iter(floats, floatsSize, printElement<float>);
    std::cout << std::endl;

    // Test 6: Character array manipulation
    std::cout << "\n6. Character array manipulation:" << std::endl;
    char message[] = "hello world";
    int messageSize = sizeof(message) / sizeof(message[0]) - 1; // Exclude null terminator
    
    std::cout << "Original message: ";
    ::iter(message, messageSize, printChar);
    std::cout << std::endl;
    
    ::iter(message, messageSize, toUppercase);
    std::cout << "After uppercase: ";
    ::iter(message, messageSize, printChar);
    std::cout << std::endl;

    // Test 7: Increment operation
    std::cout << "\n7. Increment operation:" << std::endl;
    int values[] = {0, 1, 2, 3, 4};
    int valuesSize = sizeof(values) / sizeof(values[0]);
    
    std::cout << "Before increment: ";
    ::iter(values, valuesSize, printInt);
    std::cout << std::endl;
    
    ::iter(values, valuesSize, increment);
    std::cout << "After increment: ";
    ::iter(values, valuesSize, printInt);
    std::cout << std::endl;

    // Test 8: Template function with different types
    std::cout << "\n8. Template function with different types:" << std::endl;
    char chars[] = {'A', 'B', 'C', 'D'};
    int charsSize = sizeof(chars) / sizeof(chars[0]);
    
    std::cout << "Character array: ";
    ::iter(chars, charsSize, printElement<char>);
    std::cout << std::endl;

    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}
