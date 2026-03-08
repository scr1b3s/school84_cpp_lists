#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

// iter: Function template that applies a function to each element of an array
// Supports both const and non-const function pointers/references
template <typename T, typename F>
void iter(T *array, int length, F function)
{
	for (int i = 0; i < length; i++)
	{
		function(array[i]);
	}
}

#endif
