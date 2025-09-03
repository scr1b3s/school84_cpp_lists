#include "Form.hpp"
#include "Bureaucrat.hpp"

// Orthodox Canonical Form
Form::Form() : _name("Default Form"), _signed(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute) 
	: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "Form parametric constructor called" << std::endl;
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& other) 
	: _name(other._name), _signed(other._signed), 
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called" << std::endl;
}

Form& Form::operator=(const Form& other)
{
	std::cout << "Form assignment operator called" << std::endl;
	if (this != &other)
	{
		// Note: _name, _gradeToSign, and _gradeToExecute are const, so we can't assign them
		// Only _signed can be assigned
		_signed = other._signed;
	}
	return *this;
}

Form::~Form()
{
	std::cout << "Form destructor called" << std::endl;
}

// Getters
const std::string& Form::getName() const
{
	return _name;
}

bool Form::getSigned() const
{
	return _signed;
}

int Form::getGradeToSign() const
{
	return _gradeToSign;
}

int Form::getGradeToExecute() const
{
	return _gradeToExecute;
}

// Member functions
void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_signed = true;
}

// Exception classes implementation
const char* Form::GradeTooHighException::what() const throw()
{
	return "grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "grade is too low";
}

// Overload of insertion operator
std::ostream& operator<<(std::ostream& out, const Form& form)
{
	out << "Form " << form.getName() << ", signed: " << (form.getSigned() ? "yes" : "no")
		<< ", grade required to sign: " << form.getGradeToSign()
		<< ", grade required to execute: " << form.getGradeToExecute();
	return out;
}
