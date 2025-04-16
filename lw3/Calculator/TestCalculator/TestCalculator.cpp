#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"

#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include "../Calculator.h"


TEST_CASE("����� ����������", "[calculator]") {
    Calc calc;

    SECTION("���������� ����������") {
        std::string name = "a";
        calc.SetVar(name);
        REQUIRE(calc.GetVar(name).GetName() == name);
    }

    SECTION("���������� ����� � ����������") {
        std::string name = "a";
        std::string value = "100";
        calc.SetLet(name, value);
        REQUIRE(calc.GetVar(name).GetValue() == 100);
    }

    SECTION("���������� �������� ������������ ���������� � ������ � � �����") {
        std::string name1 = "argForgGiving";
        std::string value1 = "100";
        calc.SetLet(name1, value1); //��������, ������� ���� �����������

        std::string name2 = "argOld";//������ ��������(����� ���������), �������� ����� ��������� ��������
        calc.SetVar(name2); 
        calc.SetLet(name2, name1);
        REQUIRE(calc.GetVar(name2).GetValue() == 100);

        std::string name3 = "argNew"; //����� ��������(��� ��� � ������ ����������), ������� ����� ������� � ������� ��������
        calc.SetLet(name3, name1);
        REQUIRE(calc.GetVar(name3).GetValue() == 100);
    }
}

TEST_CASE("����� �������", "[calculator]") {
    Calc calc;

    SECTION("�������� ������� � ���������� �� �������������� ����������") {
        std::string name1 = "arg1";
        std::string value = "arg2";
        REQUIRE_THROWS_WITH(calc.SetFn(name1, value), "Name does not exist");
    }

    SECTION("�������� ������� � ���������� �� ���������") {
        std::string name1 = "arg1";
        std::string value = "arg2 + arg3";
        calc.SetVar("arg2");
        calc.SetVar("arg3");
        calc.SetFn(name1, value);
        REQUIRE(calc.GetFn(name1).GetVars()[0] == "arg2");
        REQUIRE(calc.GetFn(name1).GetVars()[1] == "arg3");
        REQUIRE(calc.GetFn(name1).GetSign() == "+");
    }

    SECTION("�������� �������, ������� ����� ���� �������") {
        std::string name1 = "arg1";
        std::string value1 = "arg2 + arg3";
        std::string value2 = "arg4";
        calc.SetVar("arg2");
        calc.SetVar("arg3");
        calc.SetFn(name1, value1);
        REQUIRE_THROWS_WITH(calc.SetFn(name1, value2), "Name already exists");
    }
}
