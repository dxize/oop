#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, Less const& less) //разобратьс€ кака€ у мен€ здесь гаранти€ исключпени€ и объ€снить
{
    if (arr.empty())
        return false;

    T tempMax = arr[0];
    for (size_t i = 1; i < arr.size(); ++i)
    {
        if (less(tempMax, arr[i]))
        {
            tempMax = arr[i];
        }
    }

    maxValue = tempMax;
    return true;
}
