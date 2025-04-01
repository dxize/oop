#include <iostream>
#include <string>
#include <map>
#include "HtmlDecodeFunction.h"

int main()
{
	std::string html;	
	std::string decodeHtml;

	while (std::getline(std::cin, html))
	{
		decodeHtml = HtmlDecode(html);
		std::cout << decodeHtml;
	}

	return 0;
}