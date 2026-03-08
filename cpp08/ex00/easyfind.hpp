#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

class NotFoundException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return "Element not found in container";
		}
};

// easyfind: Find first occurrence of integer in container
// Throws NotFoundException if value not found
template <typename T>
typename T::iterator easyfind(T &container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw NotFoundException();
	return it;
}

#endif
