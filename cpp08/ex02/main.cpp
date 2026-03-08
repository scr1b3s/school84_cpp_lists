#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main(void)
{
	// Test with MutantStack
	std::cout << "=== MutantStack Test ===" << std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	
	std::cout << "\nIterating MutantStack:" << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	
	// Create std::stack from MutantStack (shows compatibility)
	std::cout << "\nCreating std::stack from MutantStack:" << std::endl;
	std::stack<int> s(mstack);
	std::cout << "Stack size: " << s.size() << std::endl;
	
	// Test with list for comparison
	std::cout << "\n=== std::list Test (for comparison) ===" << std::endl;
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(17);
	std::cout << lst.back() << std::endl;
	lst.pop_back();
	std::cout << lst.size() << std::endl;
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);
	
	std::cout << "\nIterating std::list:" << std::endl;
	std::list<int>::iterator it2 = lst.begin();
	std::list<int>::iterator ite2 = lst.end();
	++it2;
	--it2;
	while (it2 != ite2)
	{
		std::cout << *it2 << std::endl;
		++it2;
	}
	
	// Test copy constructor
	std::cout << "\n=== Copy Constructor Test ===" << std::endl;
	MutantStack<int> mstack2(mstack);
	std::cout << "Copied stack size: " << mstack2.size() << std::endl;
	std::cout << "Original stack size: " << mstack.size() << std::endl;
	
	// Test with different type
	std::cout << "\n=== Double Stack Test ===" << std::endl;
	MutantStack<double> dstack;
	dstack.push(1.5);
	dstack.push(2.5);
	dstack.push(3.5);
	
	std::cout << "Double values:" << std::endl;
	for (MutantStack<double>::iterator dit = dstack.begin(); dit != dstack.end(); ++dit)
	{
		std::cout << *dit << std::endl;
	}
	
	return 0;
}
