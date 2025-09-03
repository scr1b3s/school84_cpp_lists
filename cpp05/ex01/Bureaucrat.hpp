#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class Form; // Forward declaration

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;

public:
	// Orthodox Canonical Form
	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();

	// Getters
	const std::string&	getName() const;
	int					getGrade() const;

	// Member functions
	void				incrementGrade();
	void				decrementGrade();
	void				signForm(Form& form);

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
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif
