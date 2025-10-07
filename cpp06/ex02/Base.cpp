#include "Base.hpp"
#include <iostream>

Base::~Base()
{
	std::cout << "Base destructor called" << std::endl;
}

A::~A()
{
	std::cout << "A destructor called" << std::endl;
}

B::~B()
{
	std::cout << "B destructor called" << std::endl;
}

C::~C()
{
	std::cout << "C destructor called" << std::endl;
}
