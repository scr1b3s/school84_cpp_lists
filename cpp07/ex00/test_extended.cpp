#include <iostream>
#include <string>
#include "whatever.hpp"

int main( void ) {
    // Test with the provided example
    std::cout << "=== Original test case ===" << std::endl;
    int a = 2;
    int b = 3;

    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;

    // Additional tests
    std::cout << "\n=== Additional tests ===" << std::endl;
    
    // Test with equal values
    int x = 5, y = 5;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    ::swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    std::cout << "min(5, 5) = " << ::min(x, y) << " (should return second)" << std::endl;
    std::cout << "max(5, 5) = " << ::max(x, y) << " (should return second)" << std::endl;

    // Test with floats
    float f1 = 3.14f, f2 = 2.71f;
    std::cout << "\nFloat test:" << std::endl;
    std::cout << "Before swap: f1 = " << f1 << ", f2 = " << f2 << std::endl;
    ::swap(f1, f2);
    std::cout << "After swap: f1 = " << f1 << ", f2 = " << f2 << std::endl;
    std::cout << "min(" << f1 << ", " << f2 << ") = " << ::min(f1, f2) << std::endl;
    std::cout << "max(" << f1 << ", " << f2 << ") = " << ::max(f1, f2) << std::endl;

    // Test with characters
    char ch1 = 'z', ch2 = 'a';
    std::cout << "\nCharacter test:" << std::endl;
    std::cout << "Before swap: ch1 = " << ch1 << ", ch2 = " << ch2 << std::endl;
    ::swap(ch1, ch2);
    std::cout << "After swap: ch1 = " << ch1 << ", ch2 = " << ch2 << std::endl;
    std::cout << "min(" << ch1 << ", " << ch2 << ") = " << ::min(ch1, ch2) << std::endl;
    std::cout << "max(" << ch1 << ", " << ch2 << ") = " << ::max(ch1, ch2) << std::endl;

    return 0;
}
