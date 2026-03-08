#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _prices;
		
		// Private helper functions
		bool _isValidDate(const std::string &date);
		bool _isValidValue(const std::string &valueStr, float &value);
		bool _parseLine(const std::string &line, std::string &date, float &value);
		
	public:
		// Constructors
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &other);
		
		// Assignment operator
		BitcoinExchange &operator=(const BitcoinExchange &other);
		
		// Destructor
		~BitcoinExchange(void);
		
		// Load price database from CSV file
		bool loadDatabase(const std::string &filename);
		
		// Process input file with dates and values
		void processFile(const std::string &filename);
};

#endif
