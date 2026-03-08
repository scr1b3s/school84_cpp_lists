#include "RPN.hpp"
#include <sstream>
#include <cmath>
#include <cstdlib>

RPN::RPN(void)
{
}

RPN::RPN(const RPN &other) : _stack(other._stack)
{
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN(void)
{
	while (!_stack.empty())
		_stack.pop();
}

bool RPN::_isNumber(const std::string &str)
{
	if (str.empty())
		return false;
	
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

bool RPN::_isOperator(const std::string &str)
{
	return (str == "+" || str == "-" || str == "*" || str == "/");
}

float RPN::_applyOperator(float a, float b, char op)
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Division by zero");
			return a / b;
		default:
			throw std::runtime_error("Unknown operator");
	}
}

bool RPN::calculate(const std::string &expression, float &result)
{
	// Clear the stack
	while (!_stack.empty())
		_stack.pop();
	
	std::istringstream iss(expression);
	std::string token;
	
	while (iss >> token)
	{
		if (_isNumber(token))
		{
			// Push number to stack
			_stack.push(std::atof(token.c_str()));
		}
		else if (_isOperator(token))
		{
			// Need at least 2 operands
			if (_stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return false;
			}
			
			// Pop two operands
			float b = _stack.top();
			_stack.pop();
			float a = _stack.top();
			_stack.pop();
			
			// Apply operator
			try
			{
				float res = _applyOperator(a, b, token[0]);
				_stack.push(res);
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error" << std::endl;
				return false;
			}
		}
		else
		{
			// Invalid token
			std::cerr << "Error" << std::endl;
			return false;
		}
	}
	
	// Final stack should have exactly 1 element
	if (_stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return false;
	}
	
	result = _stack.top();
	return true;
}
