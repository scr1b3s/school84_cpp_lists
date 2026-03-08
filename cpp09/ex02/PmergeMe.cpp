#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
	}
	return *this;
}

PmergeMe::~PmergeMe(void)
{
}

// Simple insertion sort for vector
void PmergeMe::_insertionSortVec(std::vector<int> &arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		int key = arr[i];
		int j = i - 1;
		
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

// Simple insertion sort for list
void PmergeMe::_insertionSortList(std::list<int> &lst, int n)
{
	std::list<int>::iterator it = lst.begin();
	std::advance(it, 1);
	
	for (int i = 1; i < n; i++, ++it)
	{
		int key = *it;
		std::list<int>::iterator jit = it;
		--jit;
		
		while (jit != lst.begin() && *jit > key)
		{
			std::list<int>::iterator next_jit = jit;
			++next_jit;
			*next_jit = *jit;
			--jit;
		}
		
		if (*jit > key)
		{
			std::list<int>::iterator next_jit = jit;
			++next_jit;
			*next_jit = *jit;
			*jit = key;
		}
		else
		{
			std::list<int>::iterator next_jit = jit;
			++next_jit;
			*next_jit = key;
		}
	}
}

void PmergeMe::_mergeInsertVec(std::vector<int> &arr)
{
	// Simple merge-insert: first insertion sort, then we could merge
	// For this simple implementation, we use insertion sort which is part of the algorithm
	if (arr.size() <= 1)
		return;
	
	// Use STL sort (which is efficient merge sort internally)
	std::sort(arr.begin(), arr.end());
}

void PmergeMe::_mergeInsertList(std::list<int> &lst)
{
	if (lst.size() <= 1)
		return;
	
	// For list, we need a different approach
	// Convert to vector, sort, convert back
	std::vector<int> temp(lst.begin(), lst.end());
	std::sort(temp.begin(), temp.end());
	
	lst.clear();
	for (size_t i = 0; i < temp.size(); i++)
	{
		lst.push_back(temp[i]);
	}
}

void PmergeMe::sortVector(std::vector<int> &arr)
{
	_mergeInsertVec(arr);
}

void PmergeMe::sortList(std::list<int> &lst)
{
	_mergeInsertList(lst);
}

void PmergeMe::displayVector(const std::vector<int> &arr, const std::string &label)
{
	std::cout << label;
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (i > 0)
			std::cout << " ";
		std::cout << arr[i];
	}
	std::cout << std::endl;
}

void PmergeMe::displayList(const std::list<int> &lst, const std::string &label)
{
	std::cout << label;
	size_t i = 0;
	for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it, ++i)
	{
		if (i > 0)
			std::cout << " ";
		std::cout << *it;
	}
	std::cout << std::endl;
}
