#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <iostream>

template <typename T>
class Array
{
	private:
		T *_data;
		unsigned int _size;

	public:
		// Constructor with no parameter: Creates an empty array
		Array(void) : _data(NULL), _size(0)
		{
		}

		// Constructor with unsigned int n: Creates an array of n elements
		Array(unsigned int n) : _data(NULL), _size(n)
		{
			if (n > 0)
				_data = new T[n]();
		}

		// Copy constructor
		Array(const Array &other) : _data(NULL), _size(other._size)
		{
			if (_size > 0)
			{
				_data = new T[_size]();
				for (unsigned int i = 0; i < _size; i++)
					_data[i] = other._data[i];
			}
		}

		// Assignment operator
		Array &operator=(const Array &other)
		{
			if (this != &other)
			{
				delete[] _data;
				_size = other._size;
				if (_size > 0)
				{
					_data = new T[_size]();
					for (unsigned int i = 0; i < _size; i++)
						_data[i] = other._data[i];
				}
				else
					_data = NULL;
			}
			return *this;
		}

		// Destructor
		~Array(void)
		{
			delete[] _data;
		}

		// Subscript operator with bounds checking
		T &operator[](unsigned int index)
		{
			if (index >= _size)
				throw std::out_of_range("Index out of bounds");
			return _data[index];
		}

		// Const subscript operator with bounds checking
		const T &operator[](unsigned int index) const
		{
			if (index >= _size)
				throw std::out_of_range("Index out of bounds");
			return _data[index];
		}

		// Member function to get the size
		unsigned int size(void) const
		{
			return _size;
		}
};

#endif
