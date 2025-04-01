#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

int StringToInt(const std::string& str, int radix,  bool& wasError)
{
	int result = 0;
	bool isMinus = false;
	int start = 0;

	if (str[0] == '-') {
		isMinus = true;
		start = 1;
	}

	for (int i = start; i < str.length(); ++i) 
	{
		int digit = 0 ;

		if (str[i] - '0' < radix && str[i] <= '9' && str[i] >= '0') // вынести в функцию 
		{
			digit = str[i] - '0';
		}
		else if (str[i] - 'A' + 10 < radix && str[i] >= 'A' && str[i] <= 'Z')
		{
			digit = str[i] - 'A' + 10;
		}
		else
		{
			wasError = true;
			return 0;
		}

		if (result > (INT_MAX - digit) / radix)
		{
			wasError = true;
			return 0;
		}

		result = result * radix + digit;
	}

	if (isMinus)
	{
		return -result;
	}
	else
	{
		return result;
	}

}

std::string IntToString(int n, int radix, bool& wasError)
{
	std::string result{ "" };
	std::string convertChars{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" }; // лучше продолжать использовать таблицу аски
	bool isMinus{ false };

	if (radix < 2 || radix > 36) { // убрать эту проверку
		wasError = true;
		return "";
	}

	if (n < 0)
	{
		isMinus = true;
		n = -n;
	}
	else if (n == 0)
	{
		return "0";
	}

	while (n != 0)
	{
		char remainderNum;

		remainderNum = convertChars[n % radix];
		result.insert(0, 1, remainderNum);
		n /= radix;
	}

	if (isMinus)
	{
		result.insert(0, "-");
	}
	
	return result;
	
}

void ConvertNumberSystem(std::string& fromNumberSystem, std::string& toNumberSystem, //законстантить ссылки + можно вернуть строку
	std::string& numberIsStr, bool& wasError)
{
	int numberIsNum;
	int fromRadix = StringToInt(fromNumberSystem, 10, wasError);
	int toRadix = StringToInt(toNumberSystem, 10, wasError);

	if (1 < fromRadix && fromRadix < 37 && 1 < toRadix && toRadix < 37) // вынести в функцию проверку на радикс
	{
		numberIsNum = StringToInt(numberIsStr, fromRadix, wasError);
		numberIsStr = IntToString(numberIsNum, toRadix, wasError);
	}
	else
	{
		wasError = true;
	}
}


int main(int argc, char* argv[])
{
	bool wasError = false;
	std::string fromNumberSystem;
	std::string toNumberSystem;
	std::string number;

	if (argc == 4)
	{
		fromNumberSystem = argv[1];
		toNumberSystem = argv[2];
		number = argv[3];
	}
	else
	{
		std::cout << "ERROR";
		return 1;
	}

	ConvertNumberSystem(fromNumberSystem, toNumberSystem, number, wasError);

	if (wasError) 
	{
		std::cout << "ERROR";
		return 1;
	}
	
	std::cout << number;
	
	return 0;
}