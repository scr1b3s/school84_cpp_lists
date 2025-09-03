#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat; // Forward declaration

class Form
{
private:
	const std::string	_name;
	bool				_signed;
	const int			_gradeToSign;
	const int			_gradeToExecute;

public:
	// Orthodox Canonical Form
	Form();
	Form(const std::string& name, int gradeToSign, int gradeToExecute);
	Form(const Form& other);
	Form& operator=(const Form& other);
	~Form();

	// Getters
	const std::string&	getName() const;
	bool				getSigned() const;
	int					getGradeToSign() const;
	int					getGradeToExecute() const;

	// Member functions
	void				beSigned(const Bureaucrat& bureaucrat);

	// Exception classes
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

// Overload of insertion operator
std::ostream& operator<<(std::ostream& out, const Form& form);

#endif
