#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>	
#include <iomanip>
#include <string>
#include "vectorVarFirst.h"


int main()
{
	std::vector<double> numbers;

	ReadNumbers(numbers);

	if (numbers.size() > 0)
	{
		ProcessNumbers(numbers);
		PrintSortedNumbers(numbers);
	}

	return 0;
}