#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <iomanip>

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _prices(other._prices)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_prices = other._prices;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

bool BitcoinExchange::_isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	// Check YYYY
	for (int i = 0; i < 4; i++)
		if (!std::isdigit(date[i]))
			return false;
	
	// Check MM
	for (int i = 5; i < 7; i++)
		if (!std::isdigit(date[i]))
			return false;
	
	// Check DD
	for (int i = 8; i < 10; i++)
		if (!std::isdigit(date[i]))
			return false;
	
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if (year < 2009 || year > 2099)
		return false;
	
	return true;
}

bool BitcoinExchange::_isValidValue(const std::string &valueStr, float &value)
{
	if (valueStr.empty())
		return false;
	
	char *endptr;
	value = std::strtof(valueStr.c_str(), &endptr);
	
	if (*endptr != '\0')
		return false;
	
	if (value < 0)
		return false;
	
	if (value > 1000)
		return false;
	
	return true;
}

bool BitcoinExchange::_parseLine(const std::string &line, std::string &date, float &value)
{
	size_t pipePos = line.find('|');
	if (pipePos == std::string::npos)
		return false;
	
	// Extract date
	date = line.substr(0, pipePos);
	
	// Trim spaces from date (right)
	while (!date.empty() && (date[date.length() - 1] == ' ' || date[date.length() - 1] == '\t'))
		date = date.substr(0, date.length() - 1);
	// Trim spaces from date (left)
	while (!date.empty() && (date[0] == ' ' || date[0] == '\t'))
		date = date.substr(1);
	
	// Extract value
	std::string valueStr = line.substr(pipePos + 1);
	
	// Trim spaces from value (left)
	while (!valueStr.empty() && (valueStr[0] == ' ' || valueStr[0] == '\t'))
		valueStr = valueStr.substr(1);
	// Trim spaces from value (right)
	while (!valueStr.empty() && (valueStr[valueStr.length() - 1] == ' ' || valueStr[valueStr.length() - 1] == '\t'))
		valueStr = valueStr.substr(0, valueStr.length() - 1);
	
	return _isValidValue(valueStr, value);
}

bool BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return false;
	}
	
	std::string line;
	// Skip header
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;
		
		std::string date = line.substr(0, commaPos);
		std::string priceStr = line.substr(commaPos + 1);
		
		float price = std::strtof(priceStr.c_str(), NULL);
		_prices[date] = price;
	}
	
	file.close();
	return true;
}

void BitcoinExchange::processFile(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	
	std::string line;
	// Skip header
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		
		std::string date;
		float value;
		
		// First check if it's a valid date format
		size_t pipePos = line.find('|');
		if (pipePos != std::string::npos)
		{
			// Has pipe, try to parse
			if (!_parseLine(line, date, value))
			{
				if (!_isValidDate(date))
					std::cout << "Error: bad input => " << date << std::endl;
				else if (value < 0)
					std::cout << "Error: not a positive number." << std::endl;
				else if (value > 1000)
					std::cout << "Error: too large a number." << std::endl;
				else
					std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}
		}
		else
		{
			// No pipe, it's a bad date
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		// Find the price for this date
		std::map<std::string, float>::iterator it = _prices.lower_bound(date);
		
		// If exact date exists, use it; otherwise use the one before
		if (it != _prices.end() && it->first == date)
		{
			// Exact match
			float result = value * it->second;
			std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << result << std::endl;
		}
		else if (it != _prices.begin())
		{
			// Use the previous date
			--it;
			float result = value * it->second;
			std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << result << std::endl;
		}
		else
		{
			std::cout << "Error: bad input => " << date << std::endl;
		}
	}
	
	file.close();
}
