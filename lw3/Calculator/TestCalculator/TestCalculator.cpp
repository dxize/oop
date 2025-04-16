#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"

#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include "../Calculator.h"


TEST_CASE("Класс Переменной", "[calculator]") {
    Calc calc;

    SECTION("Объявление переменной") {
        std::string name = "a";
        calc.SetVar(name);
        REQUIRE(calc.GetVar(name).GetName() == name);
    }

    SECTION("Присвоение числа к переменной") {
        std::string name = "a";
        std::string value = "100";
        calc.SetLet(name, value);
        REQUIRE(calc.GetVar(name).GetValue() == 100);
    }

    SECTION("Присвоение значение существующей переменной к старой и к новой") {
        std::string name1 = "argForgGiving";
        std::string value1 = "100";
        calc.SetLet(name1, value1); //значение, которое буду присваивать

        std::string name2 = "argOld";//старое значение(ранее созданное), которому будет присвоено значение
        calc.SetVar(name2); 
        calc.SetLet(name2, name1);
        REQUIRE(calc.GetVar(name2).GetValue() == 100);

        std::string name3 = "argNew"; //новое значение(ещё нет в списке переменных), которое будет создано и получит значение
        calc.SetLet(name3, name1);
        REQUIRE(calc.GetVar(name3).GetValue() == 100);
    }
}

TEST_CASE("Класс Функций", "[calculator]") {
    Calc calc;

    SECTION("Создание функции и присвоение ей несуществующей переменной") {
        std::string name1 = "arg1";
        std::string value = "arg2";
        REQUIRE_THROWS_WITH(calc.SetFn(name1, value), "Name does not exist");
    }

    SECTION("Создание функции и присвоение ей выражение") {
        std::string name1 = "arg1";
        std::string value = "arg2 + arg3";
        calc.SetVar("arg2");
        calc.SetVar("arg3");
        calc.SetFn(name1, value);
        REQUIRE(calc.GetFn(name1).GetVars()[0] == "arg2");
        REQUIRE(calc.GetFn(name1).GetVars()[1] == "arg3");
        REQUIRE(calc.GetFn(name1).GetSign() == "+");
    }

    SECTION("Создание функции, которая ранее была создана") {
        std::string name1 = "arg1";
        std::string value1 = "arg2 + arg3";
        std::string value2 = "arg4";
        calc.SetVar("arg2");
        calc.SetVar("arg3");
        calc.SetFn(name1, value1);
        REQUIRE_THROWS_WITH(calc.SetFn(name1, value2), "Name already exists");
    }
}
