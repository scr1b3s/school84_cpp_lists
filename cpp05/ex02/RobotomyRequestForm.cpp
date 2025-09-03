#include "RobotomyRequestForm.hpp"

// Orthodox Canonical Form
RobotomyRequestForm::RobotomyRequestForm() : AForm("Robotomy Request Form", 72, 45), _target("default")
{
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) 
	: AForm("Robotomy Request Form", 72, 45), _target(target)
{
	std::cout << "RobotomyRequestForm parametric constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
	: AForm(other), _target(other._target)
{
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	std::cout << "RobotomyRequestForm assignment operator called" << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

// Getter
const std::string& RobotomyRequestForm::getTarget() const
{
	return _target;
}

// Virtual function implementation
void RobotomyRequestForm::executeAction() const
{
	std::cout << "* DRILLING NOISES * BZZZZZZT * WHIRRRRR * CLANK *" << std::endl;
	
	// Seed the random number generator with current time
	srand(static_cast<unsigned int>(time(NULL)));
	
	// 50% chance of success
	if (rand() % 2 == 0)
	{
		std::cout << _target << " has been robotomized successfully!" << std::endl;
	}
	else
	{
		std::cout << "Robotomy of " << _target << " has failed!" << std::endl;
	}
}
