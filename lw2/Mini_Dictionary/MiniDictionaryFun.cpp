#include <locale>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include "MiniDictionary.h"

std::map<std::string, std::set<std::string>> dictionary;

std::string ToLower(const std::string& str)
{
    std::locale loc("Russian");
    std::string lowerStr;
    for (char ch : str)
    {
        lowerStr += std::tolower(ch, loc);
    }
    return lowerStr;
}


void InitData(std::istream& input)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::string word, key;
        std::vector<std::string> keys;
        std::vector<std::string> values;

        while (iss >> word && word != "-")  // ������ ��� ����� ����� "-"
        {
            keys.push_back(word);
        }

        while (iss >> word)
        {
            values.push_back(word);
        }

        if (!keys.empty() && !values.empty())
        {
            std::string lowerKey;
            std::string lowerValue;

            for (const auto& k : keys)
            {
                lowerKey += ToLower(k) + ' ';
            }
            for (const auto& value : values)
            {
                lowerValue += ToLower(value) + ' ';
            }

            if (!lowerKey.empty())
                lowerKey.erase(lowerKey.size() - 1);

            if (!lowerValue.empty())
                lowerValue.erase(lowerValue.size() - 1);

            dictionary[lowerKey].insert(lowerValue);
            dictionary[lowerValue].insert(lowerKey);
        }
    }
}


void ReadFromFile(const std::string& filename)
{
    std::ifstream inputFile(filename);
    if (inputFile)
    {
        InitData(inputFile);
    }
}

void PrintTranslation(const std::set<std::string>& translations, const std::string& word)
{
    std::cout << word << " �����������: ";
    bool first = true;
    for (const auto& translation : translations)
    {
        if (!first) std::cout << ", ";
        std::cout << translation;
        first = false;
    }
    std::cout << '\n';
}

void AddNewData(const std::string& word) //������������ ��� ���������� ������ � ������������� � ��� ������� 
{
    std::cout << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������." << '\n';

    std::string translation;
    std::getline(std::cin, translation);

    if (!translation.empty())
    {
        dictionary[ToLower(word)].insert(ToLower(translation));
        dictionary[ToLower(translation)].insert(ToLower(word));
        std::cout << "����� \"" << word << "\" ��������� � ������� ��� \"" << translation << "\"." << '\n';
    }
    else
    {
        std::cout << "����� \"" << word << "\" ���������������." << '\n';
    }
}

void ProcessWord(const std::string& line)
{
    std::string word = ToLower(line);
    auto it = dictionary.find(word);
    if (it != dictionary.end())
    {
        PrintTranslation(it->second, line);
    }
    else
    {
        AddNewData(line);
    }
}

void SaveDataToFile(const std::string& filename)
{
    std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << '\n';
    std::string answer;
    std::getline(std::cin, answer);

    if (answer == "Y" || answer == "y")
    {
        std::ofstream outputFile(filename);
        for (const auto& entry : dictionary)
        {
            outputFile << entry.first << " - ";
            bool first = true;
            for (const auto& value : entry.second)
            {
                if (!first)
                {
                    outputFile << entry.first << " - ";
                }
                outputFile << value << '\n';
                first = false;
            }

            if (first) //���� ���� ����, �� ��� ��������
            {
                outputFile << '\n';
            }

        }
        std::cout << "��������� ���������. �� ��������." << '\n';
    }
}