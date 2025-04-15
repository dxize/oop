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
}
