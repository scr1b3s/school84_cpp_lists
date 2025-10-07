#include "Functions.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

Base* generate(void)
{
	// Seed random number generator (should be done once in main, but for safety)
	static bool seeded = false;
	if (!seeded)
	{
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		seeded = true;
	}

	int choice = std::rand() % 3;
	
	switch (choice)
	{
		case 0:
			std::cout << "Generated: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated: B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generated: C" << std::endl;
			return new C();
		default:
			return new A(); // Fallback (should never happen)
	}
}

void identify(Base* p)
{
	if (p == NULL)
	{
		std::cout << "Error: NULL pointer" << std::endl;
		return;
	}

	// Use dynamic_cast to identify the type
	// dynamic_cast returns NULL if the cast fails
	
	if (dynamic_cast<A*>(p) != NULL)
	{
		std::cout << "A" << std::endl;
	}
	else if (dynamic_cast<B*>(p) != NULL)
	{
		std::cout << "B" << std::endl;
	}
	else if (dynamic_cast<C*>(p) != NULL)
	{
		std::cout << "C" << std::endl;
	}
	else
	{
		std::cout << "Unknown type" << std::endl;
	}
}

void identify(Base& p)
{
	// Cannot use pointers inside this function
	// Use dynamic_cast with references - throws exception if cast fails
	
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a; // Suppress unused variable warning
		std::cout << "A" << std::endl;
		return;
	}
	catch (const std::exception& e)
	{
		// Cast failed, try next type
	}
	
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b; // Suppress unused variable warning
		std::cout << "B" << std::endl;
		return;
	}
	catch (const std::exception& e)
	{
		// Cast failed, try next type
	}
	
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c; // Suppress unused variable warning
		std::cout << "C" << std::endl;
		return;
	}
	catch (const std::exception& e)
	{
		// Cast failed, unknown type
	}
	
	std::cout << "Unknown type" << std::endl;
}
