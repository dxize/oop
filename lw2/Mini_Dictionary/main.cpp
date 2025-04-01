#include <map>
#include <set>
#include <windows.h>
#include <string>
#include <iostream>
#include "MiniDictionary.h"

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 2)
    {
        std::cerr << "Ошибка: укажите имя файла словаря." << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    ReadFromFile(filename);
    size_t initialSize = dictionary.size();

    std::string line;
    while (true)
    {
        std::getline(std::cin, line);
        if (line == "...")
        {
            break;
        }
        ProcessWord(line);
    }

    if (dictionary.size() > initialSize)
    {
        SaveDataToFile(filename);
    }

    return 0;
}
