Easy find

Turn-in directory: ex00/
Files to turn in: Makefile, main.cpp, easyfind.{h, hpp}
and optional file: easyfind.tpp
Forbidden functions: None

A first easy exercise is the way to start off on the right foot.

Write a function template easyfind that accepts a type T. It takes two parameters: the first one is of type T, and the second one is an integer.

Assuming T is a container of integers, this function has to find the first occurrence of the second parameter in the first parameter.

If no occurrence is found, you can either throw an exception or return an error value of your choice. If you need some inspiration, analyze how standard containers behave.

Of course, implement and turn in your own tests to ensure everything works as expected.

! You don’t have to handle associative containers.
