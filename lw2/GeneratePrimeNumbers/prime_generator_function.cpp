#include "prime_generator.h"
#include <vector>

const int minPrimeNum = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::vector<bool> isPrimeNumb(upperBound + 1, true);

    if (upperBound >= 1) isPrimeNumb[0] = false;
    if (upperBound >= 2) isPrimeNumb[1] = false;

    for (int i = minPrimeNum; i * i <= upperBound; ++i)// подумать как ускорить в +-2 раза
    {
        if (isPrimeNumb[i])
        {
            for (int j = i * i; j <= upperBound; j += i)
            {
                isPrimeNumb[j] = false;
            }
        }
    }

    std::set<int> primes;
    for (int i = minPrimeNum; i <= upperBound; ++i)
    {
        if (isPrimeNumb[i])
        {
            primes.insert(i);
        }
    }

    return primes;
}
