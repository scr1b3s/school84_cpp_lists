#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <ctime>

class PmergeMe
{
	private:
		// Helper functions for vector
		void _mergeInsertVec(std::vector<int> &arr);
		void _insertionSortVec(std::vector<int> &arr, int n);
		
		// Helper functions for list
		void _mergeInsertList(std::list<int> &lst);
		void _insertionSortList(std::list<int> &lst, int n);
		
		// Helper to get median
		int _getMedian(std::vector<int> &arr, size_t start, size_t end);
		int _getMedianList(std::list<int> &lst, size_t start, size_t end);
		
	public:
		// Constructor
		PmergeMe(void);
		
		// Copy constructor
		PmergeMe(const PmergeMe &other);
		
		// Assignment operator
		PmergeMe &operator=(const PmergeMe &other);
		
		// Destructor
		~PmergeMe(void);
		
		// Sort using vector
		void sortVector(std::vector<int> &arr);
		
		// Sort using list
		void sortList(std::list<int> &lst);
		
		// Display vector
		static void displayVector(const std::vector<int> &arr, const std::string &label);
		
		// Display list
		static void displayList(const std::list<int> &lst, const std::string &label);
};

#endif
