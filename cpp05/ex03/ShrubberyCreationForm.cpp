#include "ShrubberyCreationForm.hpp"

// Orthodox Canonical Form
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery Creation Form", 145, 137), _target("default")
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) 
	: AForm("Shrubbery Creation Form", 145, 137), _target(target)
{
	std::cout << "ShrubberyCreationForm parametric constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target)
{
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	std::cout << "ShrubberyCreationForm assignment operator called" << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

// Getter
const std::string& ShrubberyCreationForm::getTarget() const
{
	return _target;
}

// Virtual function implementation
void ShrubberyCreationForm::executeAction() const
{
	std::string filename = _target + "_shrubbery";
	std::ofstream file(filename.c_str());
	
	if (!file.is_open())
	{
		std::cout << "Error: Could not create file " << filename << std::endl;
		return;
	}
	
	file << "       ^" << std::endl;
	file << "      ^^^" << std::endl;
	file << "     ^^^^^" << std::endl;
	file << "    ^^^^^^^" << std::endl;
	file << "   ^^^^^^^^^" << std::endl;
	file << "  ^^^^^^^^^^^" << std::endl;
	file << " ^^^^^^^^^^^^^" << std::endl;
	file << "^^^^^^^^^^^^^^^" << std::endl;
	file << "       |||" << std::endl;
	file << "       |||" << std::endl;
	file << std::endl;
	file << "      /\\" << std::endl;
	file << "     /  \\" << std::endl;
	file << "    /____\\" << std::endl;
	file << "   /      \\" << std::endl;
	file << "  /        \\" << std::endl;
	file << " /__________\\" << std::endl;
	file << "      ||" << std::endl;
	file << "      ||" << std::endl;
	file << std::endl;
	file << "    🌲🌳🌲" << std::endl;
	file << "   🌳🌲🌳🌲" << std::endl;
	file << "  🌲🌳🌲🌳🌲" << std::endl;
	file << "     |||" << std::endl;
	
	file.close();
	std::cout << "Shrubbery has been planted at " << _target << std::endl;
}
