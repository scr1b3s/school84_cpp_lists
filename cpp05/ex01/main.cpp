#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "=== BUREAUCRAT AND FORM TESTS ===" << std::endl;

	// Test 1: Valid form creation
	std::cout << "\n--- Test 1: Valid form creation ---" << std::endl;
	try
	{
		Form taxForm("Tax Form", 50, 25);
		std::cout << taxForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 2: Form with grade too high
	std::cout << "\n--- Test 2: Form with grade too high ---" << std::endl;
	try
	{
		Form invalidForm("Invalid Form", 0, 50);
		std::cout << invalidForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 3: Form with grade too low
	std::cout << "\n--- Test 3: Form with grade too low ---" << std::endl;
	try
	{
		Form invalidForm("Invalid Form", 50, 151);
		std::cout << invalidForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 4: Successful form signing
	std::cout << "\n--- Test 4: Successful form signing ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 30);
		Form importantForm("Important Form", 50, 25);
		
		std::cout << "Before signing:" << std::endl;
		std::cout << alice << std::endl;
		std::cout << importantForm << std::endl;
		
		alice.signForm(importantForm);
		
		std::cout << "After signing:" << std::endl;
		std::cout << importantForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 5: Failed form signing (bureaucrat grade too low)
	std::cout << "\n--- Test 5: Failed form signing (bureaucrat grade too low) ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 100);
		Form vipForm("VIP Form", 50, 25);
		
		std::cout << "Before signing attempt:" << std::endl;
		std::cout << bob << std::endl;
		std::cout << vipForm << std::endl;
		
		bob.signForm(vipForm);
		
		std::cout << "After signing attempt:" << std::endl;
		std::cout << vipForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 6: Multiple signing attempts
	std::cout << "\n--- Test 6: Multiple signing attempts ---" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 1);
		Bureaucrat dave("Dave", 150);
		Form restrictedForm("Restricted Form", 10, 5);
		
		std::cout << "Initial state:" << std::endl;
		std::cout << restrictedForm << std::endl;
		
		dave.signForm(restrictedForm);  // Should fail
		charlie.signForm(restrictedForm);  // Should succeed
		charlie.signForm(restrictedForm);  // Should succeed again (already signed)
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 7: Copy constructor and assignment for Form
	std::cout << "\n--- Test 7: Copy constructor and assignment for Form ---" << std::endl;
	try
	{
		Form original("Original Form", 75, 50);
		Bureaucrat signer("Signer", 50);
		
		std::cout << "Original form: " << original << std::endl;
		
		signer.signForm(original);
		std::cout << "After signing: " << original << std::endl;
		
		Form copy(original);
		std::cout << "Copy: " << copy << std::endl;
		
		Form assigned("Assigned Form", 100, 100);
		std::cout << "Before assignment: " << assigned << std::endl;
		assigned = original;
		std::cout << "After assignment: " << assigned << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 8: Edge cases - boundary grades
	std::cout << "\n--- Test 8: Edge cases - boundary grades ---" << std::endl;
	try
	{
		Form minForm("Min Form", 1, 1);
		Form maxForm("Max Form", 150, 150);
		Bureaucrat topBureaucrat("Top", 1);
		Bureaucrat bottomBureaucrat("Bottom", 150);
		
		std::cout << "Min form: " << minForm << std::endl;
		std::cout << "Max form: " << maxForm << std::endl;
		
		topBureaucrat.signForm(minForm);
		topBureaucrat.signForm(maxForm);
		bottomBureaucrat.signForm(maxForm);
		bottomBureaucrat.signForm(minForm);  // Should fail
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== END OF TESTS ===" << std::endl;
	return 0;
}
