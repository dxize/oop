#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "prime_generator.h"  

TEST_CASE("Проверка работы GeneratePrimeNumbersSet", "[GeneratePrimeNumbersSet]") {
    SECTION("Граница 0") {
        REQUIRE(GeneratePrimeNumbersSet(0).empty());
    }

    SECTION("Граница 1") {
        REQUIRE(GeneratePrimeNumbersSet(1).empty());
    }

    SECTION("Простые числа до 10") {
        std::set<int> expected = { 2, 3, 5, 7 };
        REQUIRE(GeneratePrimeNumbersSet(10) == expected);
    }

    SECTION("Простые числа до 11") {
        std::set<int> expected = { 2, 3, 5, 7, 11 };
        REQUIRE(GeneratePrimeNumbersSet(11) == expected);
    }

    SECTION("Числа до 100") {
        std::set<int> result = GeneratePrimeNumbersSet(100);
        REQUIRE(result.find(97) != result.end());  // 97 - простое
        REQUIRE(result.find(100) == result.end()); // 100 - не простое
    }

}
//добавить тест на 100 миллионов 