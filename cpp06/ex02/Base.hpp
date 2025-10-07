#ifndef BASE_HPP
#define BASE_HPP

class Base
{
public:
	virtual ~Base();
};

class A : public Base
{
public:
	virtual ~A();
};

class B : public Base
{
public:
	virtual ~B();
};

class C : public Base
{
public:
	virtual ~C();
};

#endif
