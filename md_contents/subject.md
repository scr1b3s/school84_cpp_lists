At least this beats coffee-making

Turn-in directory: ex03/
Files to turn in: Files from previous exercises + Intern.{h, hpp}, Intern.cpp
Forbidden functions: None


Since filling out forms all day would be too cruel for our bureaucrats, interns exist to take on this tedious task. In this exercise, you must implement the Intern class. The intern has no name, no grade, and no unique characteristics. The only thing bureaucrats care about is that they do their job.

However, the intern has one key ability: the makeForm() function. This function takes two strings as parameters: the first one represents the name of a form, and the second one represents the target of the form. It returns a pointer to a AForm object (corresponding to the form name passed as a parameter), with its target initialized to the second parameter.

It should print something like:
Intern creates <form>

If the provided form name does not exist, print an explicit error message.

You must avoid unreadable and messy solutions, such as using an excessive if/elseif/else structure. This kind of approach will not be accepted during the evaluation process. You’re not in the Piscine (pool) anymore. As usual, you must test everything to ensure it works as expected.

For example, the following code creates a RobotomyRequestForm targeted at "Bender":
```cpp
{
Intern someRandomIntern;
AForm* rrf;
rrf = someRandomIntern.makeForm("robotomy request", "Bender");
}
```