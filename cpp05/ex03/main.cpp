#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	std::cout << "=== INTERN TESTS ===" << std::endl;

	// Test 1: Basic Intern functionality
	std::cout << "\n--- Test 1: Basic Intern functionality ---" << std::endl;
	try
	{
		Intern someRandomIntern;
		AForm* rrf;
		
		// Test robotomy request form creation (as shown in subject)
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf)
		{
			std::cout << *rrf << std::endl;
			delete rrf;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 2: Create all form types
	std::cout << "\n--- Test 2: Create all form types ---" << std::endl;
	try
	{
		Intern intern;
		AForm* forms[3];
		
		forms[0] = intern.makeForm("shrubbery creation", "garden");
		forms[1] = intern.makeForm("robotomy request", "Wall-E");
		forms[2] = intern.makeForm("presidential pardon", "Arthur Dent");
		
		for (int i = 0; i < 3; i++)
		{
			if (forms[i])
			{
				std::cout << *forms[i] << std::endl;
				delete forms[i];
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 3: Invalid form name
	std::cout << "\n--- Test 3: Invalid form name ---" << std::endl;
	try
	{
		Intern intern;
		AForm* invalidForm = intern.makeForm("invalid form", "target");
		if (invalidForm)
		{
			delete invalidForm;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 4: Complete workflow with Intern-created forms
	std::cout << "\n--- Test 4: Complete workflow with Intern-created forms ---" << std::endl;
	try
	{
		Intern intern;
		Bureaucrat boss("Boss", 1);
		
		// Create a form using intern
		AForm* form = intern.makeForm("presidential pardon", "Ford Prefect");
		if (form)
		{
			std::cout << "\nBefore signing:" << std::endl;
			std::cout << *form << std::endl;
			
			// Sign and execute the form
			boss.signForm(*form);
			boss.executeForm(*form);
			
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 5: Multiple interns and form creation
	std::cout << "\n--- Test 5: Multiple interns and form creation ---" << std::endl;
	try
	{
		Intern intern1;
		Intern intern2;
		Bureaucrat admin("Admin", 1);
		
		AForm* shrub = intern1.makeForm("shrubbery creation", "park");
		AForm* robot = intern2.makeForm("robotomy request", "R2-D2");
		
		if (shrub && robot)
		{
			admin.signForm(*shrub);
			admin.signForm(*robot);
			admin.executeForm(*shrub);
			admin.executeForm(*robot);
			
			delete shrub;
			delete robot;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test 6: Edge cases - empty strings
	std::cout << "\n--- Test 6: Edge cases - empty strings ---" << std::endl;
	try
	{
		Intern intern;
		AForm* emptyForm = intern.makeForm("", "target");
		AForm* emptyTarget = intern.makeForm("robotomy request", "");
		
		if (emptyForm) delete emptyForm;
		if (emptyTarget) 
		{
			std::cout << *emptyTarget << std::endl;
			delete emptyTarget;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== END OF TESTS ===" << std::endl;
	return 0;
}
