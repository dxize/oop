#ifndef MINI_DICTIONARY_H
#define MINI_DICTIONARY_H

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map> //заголовочный файл с функией реализации должен называься одинаково

extern std::map<std::string, std::set<std::string>> dictionary;

std::string ToLower(const std::string& str);

void InitData(std::istream& input);

void ReadFromFile(const std::string& filename);

void PrintTranslation(const std::set<std::string>& translations, const std::string& word);

void AddNewData(const std::string& word);

void ProcessWord(const std::string& line);

void SaveDataToFile(const std::string& filename);

#endif 