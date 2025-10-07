#include "Functions.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
	std::cout << "=== TYPE IDENTIFICATION TESTS ===" << std::endl;

	// Seed random number generator
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Test 1: Basic generation and identification
	std::cout << "\n--- Test 1: Basic generation and identification ---" << std::endl;
	
	for (int i = 0; i < 6; i++)
	{
		std::cout << "\nIteration " << i + 1 << ":" << std::endl;
		Base* obj = generate();
		
		std::cout << "Identify by pointer: ";
		identify(obj);
		
		std::cout << "Identify by reference: ";
		identify(*obj);
		
		delete obj;
		std::cout << "Object deleted" << std::endl;
	}

	// Test 2: Manual object creation and identification
	std::cout << "\n--- Test 2: Manual object creation ---" << std::endl;
	
	std::cout << "\nCreating A object:" << std::endl;
	A* aObj = new A();
	Base* aBase = aObj;
	std::cout << "Identify A by pointer: ";
	identify(aBase);
	std::cout << "Identify A by reference: ";
	identify(*aBase);
	delete aObj;
	
	std::cout << "\nCreating B object:" << std::endl;
	B* bObj = new B();
	Base* bBase = bObj;
	std::cout << "Identify B by pointer: ";
	identify(bBase);
	std::cout << "Identify B by reference: ";
	identify(*bBase);
	delete bObj;
	
	std::cout << "\nCreating C object:" << std::endl;
	C* cObj = new C();
	Base* cBase = cObj;
	std::cout << "Identify C by pointer: ";
	identify(cBase);
	std::cout << "Identify C by reference: ";
	identify(*cBase);
	delete cObj;

	// Test 3: Array of objects
	std::cout << "\n--- Test 3: Array of objects ---" << std::endl;
	
	const int arraySize = 5;
	Base* objects[arraySize];
	
	std::cout << "\nGenerating " << arraySize << " objects:" << std::endl;
	for (int i = 0; i < arraySize; i++)
	{
		objects[i] = generate();
	}
	
	std::cout << "\nIdentifying all objects by pointer:" << std::endl;
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << "Object " << i + 1 << ": ";
		identify(objects[i]);
	}
	
	std::cout << "\nIdentifying all objects by reference:" << std::endl;
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << "Object " << i + 1 << ": ";
		identify(*objects[i]);
	}
	
	std::cout << "\nCleaning up array:" << std::endl;
	for (int i = 0; i < arraySize; i++)
	{
		delete objects[i];
	}

	// Test 4: Polymorphism demonstration
	std::cout << "\n--- Test 4: Polymorphism demonstration ---" << std::endl;
	
	std::vector<Base*> collection;
	
	// Manually add one of each type
	collection.push_back(new A());
	collection.push_back(new B());
	collection.push_back(new C());
	
	std::cout << "\nCollection contents:" << std::endl;
	for (size_t i = 0; i < collection.size(); i++)
	{
		std::cout << "Index " << i << " - Pointer: ";
		identify(collection[i]);
		std::cout << "Index " << i << " - Reference: ";
		identify(*collection[i]);
	}
	
	std::cout << "\nCleaning up collection:" << std::endl;
	for (size_t i = 0; i < collection.size(); i++)
	{
		delete collection[i];
	}

	// Test 5: Error handling
	std::cout << "\n--- Test 5: Error handling ---" << std::endl;
	
	std::cout << "\nTesting NULL pointer:" << std::endl;
	Base* nullPtr = NULL;
	identify(nullPtr);

	// Test 6: Performance test
	std::cout << "\n--- Test 6: Performance test ---" << std::endl;
	
	const int perfTestSize = 100;
	std::cout << "\nGenerating and identifying " << perfTestSize << " objects:" << std::endl;
	
	int countA = 0, countB = 0, countC = 0;
	
	for (int i = 0; i < perfTestSize; i++)
	{
		Base* obj = generate();
		
		// Count types (using pointer version for efficiency)
		if (dynamic_cast<A*>(obj) != NULL) countA++;
		else if (dynamic_cast<B*>(obj) != NULL) countB++;
		else if (dynamic_cast<C*>(obj) != NULL) countC++;
		
		delete obj;
	}
	
	std::cout << "Distribution - A: " << countA 
			  << ", B: " << countB 
			  << ", C: " << countC << std::endl;
	
	// Test 7: Base class direct instantiation (not allowed)
	std::cout << "\n--- Test 7: Base class behavior ---" << std::endl;
	std::cout << "Note: Base class has virtual destructor, so it's polymorphic" << std::endl;
	std::cout << "Base class cannot be instantiated directly (has virtual destructor)" << std::endl;

	std::cout << "\n=== ALL TESTS COMPLETED ===" << std::endl;
	return 0;
}
