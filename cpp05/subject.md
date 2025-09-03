Turn-in directory: ex01/
Files to turn in: Files from the previous exercise + Form.{h, hpp}, Form.cpp
Forbidden functions: None

Now that you have bureaucrats, let’s give them something to do. What better activity could there be than filling out a stack of forms?

Let’s create a Form class. It has:
• A constant name.
• A boolean indicating whether it is signed (at construction, it is not).
• A constant grade required to sign it.
• A constant grade required to execute it.
All these attributes are private, not protected.

The grades of the Form follow the same rules as those of the Bureaucrat. Thus, the following exceptions will be thrown if a form’s grade is out of bounds:

Form::GradeTooHighException and Form::GradeTooLowException.

As before, write getters for all attributes and overload the insertion («) operator to print all the form’s information.

Also, add a beSigned() member function to the Form that takes a Bureaucrat as a parameter. It changes the form’s status to signed if the bureaucrat’s grade is high enough (greater than or equal to the required one). Remember, grade 1 is higher than grade 2.

If the grade is too low, throw a Form::GradeTooLowException.

Then, modify the signForm() member function in the Bureaucrat class. This function must call Form::beSigned() to attempt to sign the form. If the form is signed successfully, it will print something like:

<bureaucrat> signed <form>

Otherwise, it will print something like:
<bureaucrat> couldn’t sign <form> because <reason>.

Implement and submit some tests to ensure everything works as expected.