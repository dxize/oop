#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "MiniDictionary.h"  

#include <sstream>
#include <fstream>
#include <cstdio>

TEST_CASE("ToLower: Проверка преобразования строки в нижний регистр", "[ToLower]") {
    SECTION("Пустая строка") {
        std::string input = "";
        std::string output = ToLower(input);
        REQUIRE(output == "");
    }

    SECTION("Строка с латинскими буквами") {
        std::string input = "Hello World";
        std::string output = ToLower(input);
        REQUIRE(output == "hello world");
    }

    SECTION("Строка с кириллицей") {
        std::string input = "ПрИвЕт";
        std::string output = ToLower(input);
        REQUIRE(output == "привет");
    }

    SECTION("Строка с пробелами и знаками препинания") {
        std::string input = "The Red Square!";
        std::string output = ToLower(input);
        REQUIRE(output == "the red square!");
    }
}

TEST_CASE("InitData: Загрузка данных словаря из потока", "[InitData]") {

    std::istringstream iss("cat - кот кошка\nball - мяч\n");
    dictionary.clear();

    InitData(iss);

    SECTION("Наличие перевода для 'cat'") {
        auto it = dictionary.find("cat");
        REQUIRE(it != dictionary.end());
        bool found = false;
        for (const auto& tr : it->second) {
            if (tr.find("кот") != std::string::npos) {
                found = true;
                break;
            }
        }
        REQUIRE(found);
    }

    SECTION("Двунаправленность: перевод для 'мяч'") {
        auto it = dictionary.find("мяч");
        REQUIRE(it != dictionary.end());
        bool found = false;
        for (const auto& tr : it->second) {
            if (tr.find("ball") != std::string::npos) {
                found = true;
                break;
            }
        }
        REQUIRE(found);
    }
}

TEST_CASE("ProcessWord: Обработка известного слова", "[ProcessWord]") {

    dictionary.clear();
    dictionary["cat"].insert("кот");
    dictionary["кот"].insert("cat");

    std::ostringstream oss;
    auto origCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    ProcessWord("cat");

    std::cout.rdbuf(origCoutBuffer);
    std::string output = oss.str();

    SECTION("Вывод перевода для слова 'cat'") {
        REQUIRE(output.find("cat переводится:") != std::string::npos);
        REQUIRE(output.find("кот") != std::string::npos);
    }
}

TEST_CASE("AddNewData: Обработка неизвестного слова", "[AddNewData]") { //разгарничить где происходит работа с пользователем а где процесс 
    dictionary.clear();

    std::istringstream input("мясо\n");
    auto origCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream oss;
    auto origCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    AddNewData("meat");

    std::cout.rdbuf(origCoutBuffer);
    std::cin.rdbuf(origCinBuffer);

    SECTION("Добавление перевода для 'meat'") {
        auto it = dictionary.find("meat");
        REQUIRE(it != dictionary.end());
        REQUIRE(it->second.find("мясо") != it->second.end());

        auto it_rev = dictionary.find("мясо");
        REQUIRE(it_rev != dictionary.end());
        REQUIRE(it_rev->second.find("meat") != it_rev->second.end());
    }
}

TEST_CASE("SaveDataToFile: Сохранение данных в файл", "[SaveDataToFile]") {
    dictionary.clear();
    dictionary["cat"].insert("кот");
    dictionary["кот"].insert("cat");

    std::string filename = "temp_dictionary.txt";

    std::istringstream input("y\n");
    auto origCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    SaveDataToFile(filename);

    std::cin.rdbuf(origCinBuffer);

    std::ifstream infile(filename);
    std::stringstream fileContent;
    fileContent << infile.rdbuf();
    infile.close();

    std::string content = fileContent.str();

    SECTION("Файл содержит сохранённые данные") {
        REQUIRE(content.find("cat -") != std::string::npos);
        REQUIRE(content.find("кот") != std::string::npos);
    }

    std::remove(filename.c_str());
}
