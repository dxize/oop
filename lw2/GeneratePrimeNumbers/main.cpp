#include <iostream>
#include <set>
#include <string>
#include <chrono>
#include "prime_generator.h"

void PrintPrimeNumbers(const std::set<int>& primes, int upperBound)
{
	std::cout << "Prime numbers up to " << upperBound << ":  \n";

	for (int num : primes) {
		std::cout << num << "\n";
	}

	std::cout << "Count prime numbers: " << primes.size() << "\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "ERROR" << std::endl;
		return 1;
	}

	try
	{
		int upperBound = std::stoi(argv[1]);

		if (upperBound < 0) //вынести проверку в функцию
		{
			throw std::invalid_argument("ERROR");
		}	
		auto start = std::chrono::high_resolution_clock::now();

		std::set<int> primes = GeneratePrimeNumbersSet(upperBound);

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		PrintPrimeNumbers(primes, upperBound);

		std::cout << "GeneratePrimeNumbersSet function time: " << duration.count() << " ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}