#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>

class RPN
{
	private:
		std::stack<float> _stack;
		
		// Helper function to check if string is a number
		bool _isNumber(const std::string &str);
		
		// Helper function to check if string is an operator
		bool _isOperator(const std::string &str);
		
		// Helper function to apply operator
		float _applyOperator(float a, float b, char op);
		
	public:
		// Constructor
		RPN(void);
		
		// Copy constructor
		RPN(const RPN &other);
		
		// Assignment operator
		RPN &operator=(const RPN &other);
		
		// Destructor
		~RPN(void);
		
		// Process RPN expression
		bool calculate(const std::string &expression, float &result);
};

#endif
