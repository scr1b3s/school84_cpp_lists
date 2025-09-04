#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cmath>

class ScalarConverter
{
private:
	// Private constructor to prevent instantiation
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

	// Helper methods for type detection
	static bool	isChar(const std::string& input);
	static bool	isInt(const std::string& input);
	static bool	isFloat(const std::string& input);
	static bool	isDouble(const std::string& input);
	static bool	isPseudoLiteral(const std::string& input);

	// Helper methods for conversion
	static void	convertFromChar(char c);
	static void	convertFromInt(int value);
	static void	convertFromFloat(float value);
	static void	convertFromDouble(double value);
	static void	handlePseudoLiteral(const std::string& input);

	// Helper methods for display
	static void	printChar(double value, bool impossible = false);
	static void	printInt(double value, bool impossible = false);
	static void	printFloat(double value, bool isPseudo = false);
	static void	printDouble(double value, bool isPseudo = false);

public:
	static void	convert(const std::string& input);
};

#endif
