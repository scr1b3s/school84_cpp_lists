#include "Bureaucrat.hpp"

int main()
{
	std::cout << "=== BUREAUCRAT TESTS ===" << std::endl;

	// Test 1: Valid bureaucrat creation
	std::cout << "\n--- Test 1: Valid bureaucrat creation ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 75);
		std::cout << bob << std::endl;
		std::cout << "Name: " << bob.getName() << std::endl;
		std::cout << "Grade: " << bob.getGrade() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 2: Grade too high exception
	std::cout << "\n--- Test 2: Grade too high exception ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 0);
		std::cout << alice << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 3: Grade too low exception
	std::cout << "\n--- Test 3: Grade too low exception ---" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 151);
		std::cout << charlie << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 4: Increment grade
	std::cout << "\n--- Test 4: Increment grade ---" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 5);
		std::cout << "Before increment: " << dave << std::endl;
		dave.incrementGrade();
		std::cout << "After increment: " << dave << std::endl;
		dave.incrementGrade();
		std::cout << "After second increment: " << dave << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 5: Decrement grade
	std::cout << "\n--- Test 5: Decrement grade ---" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 148);
		std::cout << "Before decrement: " << eve << std::endl;
		eve.decrementGrade();
		std::cout << "After decrement: " << eve << std::endl;
		eve.decrementGrade();
		std::cout << "After second decrement: " << eve << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 6: Increment grade too much
	std::cout << "\n--- Test 6: Increment grade too much ---" << std::endl;
	try
	{
		Bureaucrat frank("Frank", 1);
		std::cout << "Before increment: " << frank << std::endl;
		frank.incrementGrade();
		std::cout << "After increment: " << frank << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 7: Decrement grade too much
	std::cout << "\n--- Test 7: Decrement grade too much ---" << std::endl;
	try
	{
		Bureaucrat grace("Grace", 150);
		std::cout << "Before decrement: " << grace << std::endl;
		grace.decrementGrade();
		std::cout << "After decrement: " << grace << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 8: Copy constructor and assignment
	std::cout << "\n--- Test 8: Copy constructor and assignment ---" << std::endl;
	try
	{
		Bureaucrat henry("Henry", 42);
		std::cout << "Original: " << henry << std::endl;
		
		Bureaucrat henryCopy(henry);
		std::cout << "Copy: " << henryCopy << std::endl;
		
		Bureaucrat iris("Iris", 100);
		std::cout << "Before assignment: " << iris << std::endl;
		iris = henry;
		std::cout << "After assignment: " << iris << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== END OF TESTS ===" << std::endl;
	return 0;
}
