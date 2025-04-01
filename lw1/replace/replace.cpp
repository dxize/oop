#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>


std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{

	size_t pos = 0;
	
	std::string result;
	if (searchString == "")
	{
		return result = subject;
	}

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.length() - pos);
			break; 
		}

		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	bool isEmptyInput{ true };
		
	while (std::getline(input, line))
	{
		isEmptyInput = false;
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
	if (isEmptyInput)
	{
		std::cout << "ERROR" << std::endl;
	}
}

bool CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName, 
	const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile)
	{
		return false;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile)
	{
		return false;
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);
	outputFile.flush();

	return true;
}

std::string OperatingMode(char** argv, int argc)
{	
	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		std::cout << "1) Usage: replace.exe <input file> <output file> <search string> < replace string>\n"
			<<"2) Usage: replace.exe - h\n" << "3) Use stdin.\n";
		return "manual";
	}
	else if (argc == 1)
	{
		/*std::cout << "Use the first line to write the desired string,"
			<< "the second line to write the replacement string, and then the replacement text.\n"
			<< "for example:\n"
			<< "ma\nmama\nmama delala pelmeni\nya pokushal plotno\n";*/
		return "console";
	}
	else if (argc == 5)
	{
		return "file";
	}
	else
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return "";
	}
}

int main(int argc, char* argv[])
{
	std::string mode = OperatingMode(argv, argc);
	if (mode == "")
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	if (mode == "manual")
	{
		return 0;
	}
	else if (mode == "console")
	{
		std::string searchString, replacementString, text, line;

		/*std::cout << "Enter search string: ";*/
		std::getline(std::cin, searchString);
		/*std::cout << "Enter replacement string: ";*/
		std::getline(std::cin, replacementString);
		bool isEmptyInput{ true };

		while (std::getline(std::cin, line))
		{
			isEmptyInput = false;
			text += ReplaceString(line, searchString, replacementString) + "\n";
		}

		if (isEmptyInput)
		{
			std::cout << "ERROR" << std::endl;
		}

		std::cout << text;
	}
	else if (mode == "file")
	{
		std::string inputFileName = argv[1];
		std::string outputFileName = argv[2];
		std::string search = argv[3];
		std::string replace = argv[4];
		if (!CopyFileWithReplacement(inputFileName, outputFileName, search, replace))
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}

	}

	return 0;
}//ENUM ÄÎÁÀÂÈÒÜ / ÏÅÐÅÈÌÅÍÎÂÀÒÜ È ÈÑÏÐÀÂÈÒÜ ÝÌÏÒÈÈÌÏÓÒ