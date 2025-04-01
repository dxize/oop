#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "prime_generator.h"  

TEST_CASE("�������� ������ GeneratePrimeNumbersSet", "[GeneratePrimeNumbersSet]") {
    SECTION("������� 0") {
        REQUIRE(GeneratePrimeNumbersSet(0).empty());
    }

    SECTION("������� 1") {
        REQUIRE(GeneratePrimeNumbersSet(1).empty());
    }

    SECTION("������� ����� �� 10") {
        std::set<int> expected = { 2, 3, 5, 7 };
        REQUIRE(GeneratePrimeNumbersSet(10) == expected);
    }

    SECTION("������� ����� �� 11") {
        std::set<int> expected = { 2, 3, 5, 7, 11 };
        REQUIRE(GeneratePrimeNumbersSet(11) == expected);
    }

    SECTION("����� �� 100") {
        std::set<int> result = GeneratePrimeNumbersSet(100);
        REQUIRE(result.find(97) != result.end());  // 97 - �������
        REQUIRE(result.find(100) == result.end()); // 100 - �� �������
    }

}
//�������� ���� �� 100 ��������� 