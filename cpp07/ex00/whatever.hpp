#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// swap: Swaps the values of two given parameters
template <typename T>
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

// min: Returns the smallest of two values
// If equal, returns the second one
template <typename T>
T min(T a, T b)
{
	return (b < a) ? b : a;
}

// max: Returns the greatest of two values
// If equal, returns the second one
template <typename T>
T max(T a, T b)
{
	return (b > a) ? b : a;
}

#endif
