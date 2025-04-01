#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "MiniDictionary.h"  

#include <sstream>
#include <fstream>
#include <cstdio>

TEST_CASE("ToLower: �������� �������������� ������ � ������ �������", "[ToLower]") {
    SECTION("������ ������") {
        std::string input = "";
        std::string output = ToLower(input);
        REQUIRE(output == "");
    }

    SECTION("������ � ���������� �������") {
        std::string input = "Hello World";
        std::string output = ToLower(input);
        REQUIRE(output == "hello world");
    }

    SECTION("������ � ����������") {
        std::string input = "������";
        std::string output = ToLower(input);
        REQUIRE(output == "������");
    }

    SECTION("������ � ��������� � ������� ����������") {
        std::string input = "The Red Square!";
        std::string output = ToLower(input);
        REQUIRE(output == "the red square!");
    }
}

TEST_CASE("InitData: �������� ������ ������� �� ������", "[InitData]") {

    std::istringstream iss("cat - ��� �����\nball - ���\n");
    dictionary.clear();

    InitData(iss);

    SECTION("������� �������� ��� 'cat'") {
        auto it = dictionary.find("cat");
        REQUIRE(it != dictionary.end());
        bool found = false;
        for (const auto& tr : it->second) {
            if (tr.find("���") != std::string::npos) {
                found = true;
                break;
            }
        }
        REQUIRE(found);
    }

    SECTION("�����������������: ������� ��� '���'") {
        auto it = dictionary.find("���");
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

TEST_CASE("ProcessWord: ��������� ���������� �����", "[ProcessWord]") {

    dictionary.clear();
    dictionary["cat"].insert("���");
    dictionary["���"].insert("cat");

    std::ostringstream oss;
    auto origCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    ProcessWord("cat");

    std::cout.rdbuf(origCoutBuffer);
    std::string output = oss.str();

    SECTION("����� �������� ��� ����� 'cat'") {
        REQUIRE(output.find("cat �����������:") != std::string::npos);
        REQUIRE(output.find("���") != std::string::npos);
    }
}

TEST_CASE("AddNewData: ��������� ������������ �����", "[AddNewData]") { //������������ ��� ���������� ������ � ������������� � ��� ������� 
    dictionary.clear();

    std::istringstream input("����\n");
    auto origCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream oss;
    auto origCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    AddNewData("meat");

    std::cout.rdbuf(origCoutBuffer);
    std::cin.rdbuf(origCinBuffer);

    SECTION("���������� �������� ��� 'meat'") {
        auto it = dictionary.find("meat");
        REQUIRE(it != dictionary.end());
        REQUIRE(it->second.find("����") != it->second.end());

        auto it_rev = dictionary.find("����");
        REQUIRE(it_rev != dictionary.end());
        REQUIRE(it_rev->second.find("meat") != it_rev->second.end());
    }
}

TEST_CASE("SaveDataToFile: ���������� ������ � ����", "[SaveDataToFile]") {
    dictionary.clear();
    dictionary["cat"].insert("���");
    dictionary["���"].insert("cat");

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

    SECTION("���� �������� ���������� ������") {
        REQUIRE(content.find("cat -") != std::string::npos);
        REQUIRE(content.find("���") != std::string::npos);
    }

    std::remove(filename.c_str());
}
