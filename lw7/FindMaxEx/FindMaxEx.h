#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, Less const& less)
{
    if (arr.empty())
        return false;

    T tempMax = arr[0];
    try
    {
        for (size_t i = 1; i < arr.size(); ++i)
        {
            if (less(tempMax, arr[i]))
            {
                tempMax = arr[i];
            }
        }
    }
    catch (...)  
    {
        return false;
    }

    maxValue = tempMax;
    return true;
}
