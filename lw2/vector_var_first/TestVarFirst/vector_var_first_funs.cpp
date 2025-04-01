#include "vectorVarFirst.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>	
#include <iomanip>
#include <string>

void ReadNumbers(std::vector<double>& numbers)
{
	std::string line;
	double num;

	std::getline(std::cin, line);
	std::istringstream iss(line);

	while (iss >> num) {
		numbers.push_back(num);
	}

	if (!iss.eof())
	{
		std::cout << "ERROR" << std::endl;
		numbers.clear();
	}
}

void ProcessNumbers(std::vector<double>& numbers)
{
	double sumNumbers = 0;
	double averageNumber = 0;

	sumNumbers = std::accumulate(
		numbers.begin(),
		numbers.end(),
		0.0,
		[](double acc, double num) {
			return (num > 0) ? (acc + num) : acc;
		}
	);

	size_t countPositive = std::count_if(
		numbers.begin(),
		numbers.end(),
		[](double num) { return num > 0; }
	);

	if (countPositive > 0)
	{
		averageNumber = sumNumbers / countPositive;
	}

	for (int i = 0; numbers.size() > i; ++i) //нужно переделать под std::трансформ)
	{
		numbers[i] += averageNumber;
	}

}

void PrintSortedNumbers(std::vector<double>& numbers)
{
	std::vector<double> copy = numbers;

	std::ios::fmtflags oldFlags = std::cout.flags();
	std::streamsize oldPrecision = std::cout.precision();

	std::cout << std::fixed << std::setprecision(3);

	std::sort(copy.begin(), copy.end());

	for (double num : copy) {
		std::cout << num << " ";
	}

	std::cout.flags(oldFlags);
	std::cout.precision(oldPrecision);
}