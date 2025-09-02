Turn-in directory: ex00/
Files to turn in: Makefile, main.cpp, Bureaucrat.{h, hpp}, Bureaucrat.cpp
Forbidden functions: None

Please note that exception classes do not have to be designed in Orthodox Canonical Form. However, every other class must follow it.

Let’s design an artificial nightmare of offices, corridors, forms, and waiting queues. Sounds fun? No? Too bad.

First, start with the smallest cog in this vast bureaucratic machine: the Bureaucrat.

A Bureaucrat must have:
• A constant name.
• A grade that ranges from 1 (highest possible grade) to 150 (lowest possible grade).

Any attempt to instantiate a Bureaucrat with an invalid grade must throw an exception:
either a Bureaucrat::GradeTooHighException or a Bureaucrat::GradeTooLowException.

You will provide getters for both attributes: getName() and getGrade().
You must also implement two member functions to increment or decrement the bureaucrat’s grade.
If the grade goes out of range, both functions must throw the same exceptions as the constructor.

Remember, since grade 1 is the highest and 150 the lowest, incrementing a grade 3 should result in a grade 2 for the bureaucrat.

The thrown exceptions must be catchable using try and catch blocks:

try
{
/* do some stuff with bureaucrats */
}

catch (std::exception & e)
{
/* handle exception */
}

You must implement an overload of the insertion («) operator to print output in the following format (without the angle brackets):

<name>, bureaucrat grade <grade>.

As usual, submit some tests to prove that everything works as expected.