#include "ScalarConverter.hpp"

// Private constructor (prevents instantiation)
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// Type detection methods
bool ScalarConverter::isChar(const std::string& input)
{
	return (input.length() == 3 && input[0] == '\'' && input[2] == '\'' && 
			input[1] >= 32 && input[1] <= 126);
}

bool ScalarConverter::isInt(const std::string& input)
{
	if (input.empty())
		return false;
	
	size_t start = 0;
	if (input[0] == '+' || input[0] == '-')
		start = 1;
	
	if (start >= input.length())
		return false;
	
	for (size_t i = start; i < input.length(); i++)
	{
		if (!std::isdigit(input[i]))
			return false;
	}
	
	// Check for integer overflow
	char* endptr;
	long value = std::strtol(input.c_str(), &endptr, 10);
	if (*endptr != '\0')
		return false;
	
	return (value >= std::numeric_limits<int>::min() && 
			value <= std::numeric_limits<int>::max());
}

bool ScalarConverter::isFloat(const std::string& input)
{
	if (input.length() < 2 || input[input.length() - 1] != 'f')
		return false;
	
	std::string withoutF = input.substr(0, input.length() - 1);
	
	if (withoutF.empty())
		return false;
	
	size_t start = 0;
	if (withoutF[0] == '+' || withoutF[0] == '-')
		start = 1;
	
	bool hasDot = false;
	bool hasDigit = false;
	
	for (size_t i = start; i < withoutF.length(); i++)
	{
		if (withoutF[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (std::isdigit(withoutF[i]))
		{
			hasDigit = true;
		}
		else
		{
			return false;
		}
	}
	
	return hasDigit;
}

bool ScalarConverter::isDouble(const std::string& input)
{
	if (input.empty())
		return false;
	
	size_t start = 0;
	if (input[0] == '+' || input[0] == '-')
		start = 1;
	
	bool hasDot = false;
	bool hasDigit = false;
	
	for (size_t i = start; i < input.length(); i++)
	{
		if (input[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (std::isdigit(input[i]))
		{
			hasDigit = true;
		}
		else
		{
			return false;
		}
	}
	
	return hasDigit;
}

bool ScalarConverter::isPseudoLiteral(const std::string& input)
{
	return (input == "-inff" || input == "+inff" || input == "nanf" ||
			input == "-inf" || input == "+inf" || input == "nan");
}

// Conversion methods
void ScalarConverter::convertFromChar(char c)
{
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

void ScalarConverter::convertFromInt(int value)
{
	printChar(static_cast<double>(value));
	std::cout << "int: " << value << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << std::endl;
}

void ScalarConverter::convertFromFloat(float value)
{
	printChar(static_cast<double>(value));
	printInt(static_cast<double>(value));
	printFloat(static_cast<double>(value));
	printDouble(static_cast<double>(value));
}

void ScalarConverter::convertFromDouble(double value)
{
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

void ScalarConverter::handlePseudoLiteral(const std::string& input)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	
	if (input == "-inff" || input == "-inf")
	{
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
	else if (input == "+inff" || input == "+inf")
	{
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else // nanf or nan
	{
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
}

// Display helper methods
void ScalarConverter::printChar(double value, bool impossible)
{
	if (impossible || std::isnan(value) || std::isinf(value) || 
		value < 0 || value > 127 || (value >= 0 && value <= 31) || value == 127)
	{
		if (impossible || std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
			std::cout << "char: impossible" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
	{
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	}
}

void ScalarConverter::printInt(double value, bool impossible)
{
	if (impossible || std::isnan(value) || std::isinf(value) || 
		value < std::numeric_limits<int>::min() || 
		value > std::numeric_limits<int>::max())
	{
		std::cout << "int: impossible" << std::endl;
	}
	else
	{
		std::cout << "int: " << static_cast<int>(value) << std::endl;
	}
}

void ScalarConverter::printFloat(double value, bool isPseudo)
{
	if (isPseudo)
		return; // Already handled in handlePseudoLiteral
	
	if (std::isnan(value))
		std::cout << "float: nanf" << std::endl;
	else if (std::isinf(value))
	{
		if (value < 0)
			std::cout << "float: -inff" << std::endl;
		else
			std::cout << "float: +inff" << std::endl;
	}
	else
	{
		float f = static_cast<float>(value);
		if (f == static_cast<int>(f))
			std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
		else
			std::cout << "float: " << f << "f" << std::endl;
	}
}

void ScalarConverter::printDouble(double value, bool isPseudo)
{
	if (isPseudo)
		return; // Already handled in handlePseudoLiteral
	
	if (std::isnan(value))
		std::cout << "double: nan" << std::endl;
	else if (std::isinf(value))
	{
		if (value < 0)
			std::cout << "double: -inf" << std::endl;
		else
			std::cout << "double: +inf" << std::endl;
	}
	else
	{
		if (value == static_cast<int>(value))
			std::cout << "double: " << std::fixed << std::setprecision(1) << value << std::endl;
		else
			std::cout << "double: " << value << std::endl;
	}
}

// Main conversion method
void ScalarConverter::convert(const std::string& input)
{
	if (input.empty())
	{
		std::cout << "Error: Empty input" << std::endl;
		return;
	}
	
	// Check for pseudo-literals first
	if (isPseudoLiteral(input))
	{
		handlePseudoLiteral(input);
		return;
	}
	
	// Check for char literal
	if (isChar(input))
	{
		char c = input[1];
		convertFromChar(c);
		return;
	}
	
	// Check for int literal
	if (isInt(input))
	{
		int value = std::atoi(input.c_str());
		convertFromInt(value);
		return;
	}
	
	// Check for float literal
	if (isFloat(input))
	{
		std::string withoutF = input.substr(0, input.length() - 1);
		float value = static_cast<float>(std::atof(withoutF.c_str()));
		convertFromFloat(value);
		return;
	}
	
	// Check for double literal
	if (isDouble(input))
	{
		double value = std::atof(input.c_str());
		convertFromDouble(value);
		return;
	}
	
	// If none of the above, it's an invalid input
	std::cout << "Error: Invalid input format" << std::endl;
}
