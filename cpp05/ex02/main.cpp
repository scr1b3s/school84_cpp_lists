#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::cout << "=== ABSTRACT FORM AND CONCRETE FORMS TESTS ===" << std::endl;

	// Test 1: Create concrete forms
	std::cout << "\n--- Test 1: Create concrete forms ---" << std::endl;
	try
	{
		ShrubberyCreationForm shrub("garden");
		RobotomyRequestForm robot("Bender");
		PresidentialPardonForm pardon("Arthur Dent");
		
		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << pardon << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 2: Sign and execute ShrubberyCreationForm
	std::cout << "\n--- Test 2: Sign and execute ShrubberyCreationForm ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 100);
		ShrubberyCreationForm shrub("home");
		
		std::cout << "Before signing:" << std::endl;
		std::cout << alice << std::endl;
		std::cout << shrub << std::endl;
		
		alice.signForm(shrub);
		alice.executeForm(shrub);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 3: Try to execute unsigned form
	std::cout << "\n--- Test 3: Try to execute unsigned form ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 1);
		RobotomyRequestForm robot("Wall-E");
		
		std::cout << "Attempting to execute unsigned form:" << std::endl;
		bob.executeForm(robot);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 4: Sign but insufficient grade to execute
	std::cout << "\n--- Test 4: Sign but insufficient grade to execute ---" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 50);
		RobotomyRequestForm robot("C-3PO");
		
		charlie.signForm(robot);
		charlie.executeForm(robot);  // Charlie's grade (50) is not enough for execution (45)
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 5: Successful robotomy (multiple attempts to show randomness)
	std::cout << "\n--- Test 5: Successful robotomy execution (multiple attempts) ---" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		RobotomyRequestForm robot1("R2-D2");
		RobotomyRequestForm robot2("BB-8");
		RobotomyRequestForm robot3("WALL-E");
		
		dave.signForm(robot1);
		dave.executeForm(robot1);
		
		dave.signForm(robot2);
		dave.executeForm(robot2);
		
		dave.signForm(robot3);
		dave.executeForm(robot3);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 6: Presidential pardon (highest security form)
	std::cout << "\n--- Test 6: Presidential pardon ---" << std::endl;
	try
	{
		Bureaucrat president("Mr. President", 1);
		Bureaucrat secretary("Secretary", 10);
		PresidentialPardonForm pardon("Ford Prefect");
		
		std::cout << "Secretary attempts to sign and execute:" << std::endl;
		secretary.signForm(pardon);
		secretary.executeForm(pardon);
		
		std::cout << "\nPresident attempts to sign and execute:" << std::endl;
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 7: Copy constructor and assignment
	std::cout << "\n--- Test 7: Copy constructor and assignment ---" << std::endl;
	try
	{
		ShrubberyCreationForm original("original_garden");
		Bureaucrat signer("Signer", 1);
		
		signer.signForm(original);
		std::cout << "Original: " << original << std::endl;
		
		ShrubberyCreationForm copy(original);
		std::cout << "Copy: " << copy << std::endl;
		
		ShrubberyCreationForm assigned("assigned_garden");
		assigned = original;
		std::cout << "Assigned: " << assigned << std::endl;
		
		// Execute all forms
		signer.executeForm(original);
		signer.executeForm(copy);
		signer.executeForm(assigned);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 8: Polymorphism with base class pointers
	std::cout << "\n--- Test 8: Polymorphism with base class pointers ---" << std::endl;
	try
	{
		Bureaucrat admin("Admin", 1);
		
		// Create forms through base class pointers
		AForm* forms[] = {
			new ShrubberyCreationForm("poly_garden"),
			new RobotomyRequestForm("Poly-Robot"),
			new PresidentialPardonForm("Poly-Citizen")
		};
		
		// Process all forms polymorphically
		for (int i = 0; i < 3; i++)
		{
			std::cout << "\nProcessing form " << i + 1 << ":" << std::endl;
			std::cout << *forms[i] << std::endl;
			admin.signForm(*forms[i]);
			admin.executeForm(*forms[i]);
		}
		
		// Clean up
		for (int i = 0; i < 3; i++)
		{
			delete forms[i];
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 9: Grade boundary testing
	std::cout << "\n--- Test 9: Grade boundary testing ---" << std::endl;
	try
	{
		// Test exact grade requirements
		Bureaucrat shrubSigner("ShrubSigner", 145);    // Exact grade for signing
		Bureaucrat shrubExecutor("ShrubExecutor", 137); // Exact grade for execution
		
		ShrubberyCreationForm shrub("boundary_test");
		
		shrubSigner.signForm(shrub);
		shrubExecutor.executeForm(shrub);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== END OF TESTS ===" << std::endl;
	return 0;
}
