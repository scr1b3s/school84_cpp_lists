Start with a few functions

Turn-in directory: ex00/
Files to turn in: Makefile, main.cpp, whatever.{h, hpp}
Forbidden functions: None

Implement the following function templates:

• swap: Swaps the values of two given parameters. Does not return anything.
• min: Compares the two values passed as parameters and returns the smallest one. If they are equal, it returns the second one.

• max: Compares the two values passed as parameters and returns the greatest one. If they are equal, it returns the second one.

These functions can be called with any type of argument. The only requirement is that the two arguments must have the same type and must support all the comparison operators.

! Templates must be defined in the header files.

Running the following code:

```cpp
int main( void ) {
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

return 0;

}
```

Should output:

```shell
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```