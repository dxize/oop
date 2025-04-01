#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "vectorVarFirst.h"

TEST_CASE("�������� ReadNumbers", "[ReadNumbers]") {
    SECTION("���������� ����") {
        std::istringstream input("1.1 2.2 3.3 4.4\n");
        std::cin.rdbuf(input.rdbuf());
        std::vector<double> numbers;
        ReadNumbers(numbers);
        REQUIRE(numbers.size() == 4);
        REQUIRE(numbers[0] == Approx(1.1));
        REQUIRE(numbers[1] == Approx(2.2));
        REQUIRE(numbers[2] == Approx(3.3));
        REQUIRE(numbers[3] == Approx(4.4));
    }

    SECTION("������������ ����") {
        std::istringstream input("1.1 abc 2.2\n");
        std::cin.rdbuf(input.rdbuf());
        std::vector<double> numbers;
        std::ostringstream output;
        std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
        ReadNumbers(numbers);
        std::cout.rdbuf(old_cout);
        REQUIRE(numbers.empty());
        REQUIRE(output.str() == "ERROR\n");
    }
}

TEST_CASE("�������� ProcessNumbers", "[ProcessNumbers]") {
    SECTION("��������� ������������� �����") {
        std::vector<double> numbers = { 1.0, 2.0, 3.0 };
        ProcessNumbers(numbers);
        REQUIRE(numbers[0] == Approx(3.0));
        REQUIRE(numbers[1] == Approx(4.0));
        REQUIRE(numbers[2] == Approx(5.0));
    }

    SECTION("��������� � �������������� �������") {
        std::vector<double> numbers = { -1.0, 2.0, -3.0, 4.0 };
        ProcessNumbers(numbers);
        REQUIRE(numbers[0] == Approx(2.0));
        REQUIRE(numbers[1] == Approx(5.0));
        REQUIRE(numbers[2] == Approx(0.0));
        REQUIRE(numbers[3] == Approx(7.0));
    }

    SECTION("������ ������") {
        std::vector<double> numbers;
        ProcessNumbers(numbers);
        REQUIRE(numbers.empty());
    }
    //�������� ����� ��� ������������� �����
}

TEST_CASE("�������� PrintSortedNumbers", "[PrintSortedNumbers]") {
    SECTION("����� ���������������� �������") {
        std::vector<double> numbers = { 3.0, 1.0, 2.0 };
        std::ostringstream output;
        std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
        PrintSortedNumbers(numbers);
        std::cout.rdbuf(old_cout);
        REQUIRE(output.str() == "1.000 2.000 3.000 ");
    }

    SECTION("������ ������") {
        std::vector<double> numbers;
        std::ostringstream output;
        std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
        PrintSortedNumbers(numbers);
        std::cout.rdbuf(old_cout);
        REQUIRE(output.str().empty());
    }
}
