#include "PmergeMe.hpp"
#include <cstdlib>
#include <sstream>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	std::vector<int> vecData;
	std::list<int> listData;
	
	// Parse arguments as integers
	for (int i = 1; i < argc; i++)
	{
		int num = std::atoi(argv[i]);
		
		// Check if conversion was successful and value is positive
		if (num <= 0 || (num == 0 && argv[i][0] != '0'))
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		
		vecData.push_back(num);
		listData.push_back(num);
	}
	
	// Display unsorted
	PmergeMe::displayVector(vecData, "Before: ");
	
	// Create copy for list display
	std::list<int> listDataCopy(listData.begin(), listData.end());
	
	// Measure time and sort vector
	clock_t startVec = clock();
	PmergeMe pmVec;
	pmVec.sortVector(vecData);
	clock_t endVec = clock();
	double timeVec = (double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000; // microseconds
	
	// Measure time and sort list
	clock_t startList = clock();
	PmergeMe pmList;
	pmList.sortList(listData);
	clock_t endList = clock();
	double timeList = (double)(endList - startList) / CLOCKS_PER_SEC * 1000000; // microseconds
	
	// Display sorted (after vector sort)
	PmergeMe::displayVector(vecData, "After:\n");
	
	// Display timing information
	std::cout << "Time to process a range of " << vecData.size() << " elements with std::vector : " 
	          << std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << listData.size() << " elements with std::list : " 
	          << std::fixed << std::setprecision(5) << timeList << " us" << std::endl;
	
	return 0;
}
