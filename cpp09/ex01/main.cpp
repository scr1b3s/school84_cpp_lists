#include "RPN.hpp"
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	RPN rpn;
	float result;
	
	if (rpn.calculate(argv[1], result))
	{
		// Check if result is integer or float
		if (result == (int)result)
			std::cout << (int)result << std::endl;
		else
			std::cout << std::fixed << std::setprecision(2) << result << std::endl;
		return 0;
	}
	
	return 1;
}
