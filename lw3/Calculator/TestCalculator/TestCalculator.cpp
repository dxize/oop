#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"

#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include "../Calculator.h"


//������� ����� ���������� ������ 

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

TEST_CASE("������� Evaluate", "[calculator]") {
    Calc calc;

    SECTION("���������� �������� ����������") {
        calc.SetLet("x", "10");
        REQUIRE(calc.Evaluate("x") == Approx(10.0));
    }

    SECTION("���������� �������� ������� � ����� ����������") {
        calc.SetLet("x", "5");
        calc.SetFn("f", "x");
        REQUIRE(calc.Evaluate("f") == Approx(5.0));
    }

    SECTION("���������� �������� ������� � ����� ����������� (��������)") {
        calc.SetLet("a", "3");
        calc.SetLet("b", "7");
        calc.SetFn("sum", "a + b");
        REQUIRE(calc.Evaluate("sum") == Approx(10.0));
    }

    SECTION("���������� �������� ������� � ����� ����������� (���������)") {
        calc.SetLet("a", "10");
        calc.SetLet("b", "4");
        calc.SetFn("sub", "a - b");
        REQUIRE(calc.Evaluate("sub") == Approx(6.0));
    }

    SECTION("���������� �������� ������� � ����� ����������� (���������)") {
        calc.SetLet("a", "2");
        calc.SetLet("b", "3");
        calc.SetFn("mul", "a * b");
        REQUIRE(calc.Evaluate("mul") == Approx(6.0));
    }

    SECTION("���������� �������� ������� � ����� ����������� (�������)") {
        calc.SetLet("a", "10");
        calc.SetLet("b", "2");
        calc.SetFn("div", "a / b");
        REQUIRE(calc.Evaluate("div") == Approx(5.0));
    }

    SECTION("������� �� ���� ������ ������� NAN") {
        calc.SetLet("a", "10");
        calc.SetLet("b", "0");
        calc.SetFn("div", "a / b");
        REQUIRE(std::isnan(calc.Evaluate("div")));
    }

    SECTION("���������� ������� � �����������-���������") {
        calc.SetLet("a", "2");
        calc.SetLet("b", "3");
        calc.SetFn("f1", "a + b");        // f1 = 5
        calc.SetLet("c", "4");
        calc.SetFn("f2", "f1 * c");       // f2 = 5 * 4 = 20
        REQUIRE(calc.Evaluate("f2") == Approx(20.0));
    }

    SECTION("������������� �������� ������ ������� NAN") {
        REQUIRE(std::isnan(calc.Evaluate("not_exist")));
    }
}

TEST_CASE("PrintVars: ������ ������ ����������", "[calculator][printvars]") {
    Calc calc;
    REQUIRE(calc.SortVars() == "");
}

TEST_CASE("PrintVars: ����� ���������� ��������������� �� ��������", "[calculator][printvars]") {
    Calc calc;
    calc.SetLet("z", "100");
    calc.SetLet("a", "50");
    calc.SetLet("m", "25");

    std::string expected =
        "a:50.00\n"
        "m:25.00\n"
        "z:100.00\n";

    REQUIRE(calc.SortVars() == expected);
}

TEST_CASE("PrintVars: ����� ���������� � ������������� ��������� (nan)", "[calculator][printvars]") {
    Calc calc;

    calc.SetVar("x");
    std::string expected = "x:nan\n";

    REQUIRE(calc.SortVars() == expected);
}

TEST_CASE("PrintFns: ������ ������ �������", "[calculator][printfns]") {
    Calc calc;

    REQUIRE(calc.SortFns() == "");
}

TEST_CASE("PrintFns: ����� ������� ��������������� �� ��������", "[calculator][printfns]") {
    Calc calc;

    calc.SetLet("a", "10");
    calc.SetLet("b", "20");
    calc.SetLet("c", "5");

    calc.SetFn("diff", "a - c");
    calc.SetFn("sum", "a + b");

    std::string expected =
        "diff:5.00\n"
        "sum:30.00\n";

    REQUIRE(calc.SortFns() == expected);
}

TEST_CASE("PrintFns: ������� � ������������� ��������� (nan)", "[calculator][printfns]") {
    Calc calc;

    calc.SetLet("a", "10");
    calc.SetLet("b", "0");
    calc.SetFn("div", "a / b");  

    std::string expected = "div:nan\n";
    REQUIRE(calc.SortFns() == expected);
}

TEST_CASE("������: ������������ ������������� � SetVar", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar("1invalid"), "Invalid usage");
}

TEST_CASE("������: ������������ ������������� � SetLet", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("2var", "100"), "Invalid usage");
}

TEST_CASE("������: ������������� ����� ������� � SetLet", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("x", "10");
    calc.SetFn("f", "x");
    REQUIRE_THROWS_WITH(calc.SetLet("f", "20"), "Name already exists");
}

TEST_CASE("������: ������������� ������������� ���������� � SetLet", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("a", "b"), "Name does not exist");
}

TEST_CASE("������: ������������� �������������� �������������� � SetFn", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetFn("f", "x + y"), "Name does not exist");
}

TEST_CASE("������: ������� �������� ������� � ��� ������������ ������", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("v", "10");
    REQUIRE_THROWS_WITH(calc.SetFn("v", "x + y"), "Name already exists");
}

TEST_CASE("������: �������� ������� � �������� ������ ����������", "[calculator][errors]") {
    Calc calc;

    calc.SetLet("a", "10");
    calc.SetLet("b", "20");
    
    REQUIRE_THROWS_WITH(calc.SetFn("f1", "+"), "Invalid usage");

    REQUIRE_THROWS_WITH(calc.SetFn("f2", "a + b + a"), "Invalid usage");
}


//�������
TEST_CASE("������: ������ ��� ���������� � SetVar", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar(""), "Invalid usage");
}

TEST_CASE("������: ������� � ����� ���������� � SetVar", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar("a b"), "Invalid usage");
}

TEST_CASE("������: ������������ ������ � ����� ����������", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar("var!"), "Invalid usage");
}

TEST_CASE("������: ������ ��� � SetLet", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("", "123"), "Invalid usage");
}

TEST_CASE("������: SetLet � ������������ rhs (������� � ���������������)", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("x", "@@@"), "Name does not exist");
}

TEST_CASE("������: SetFn � ������ ����������", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetFn("h", ""), "Invalid usage");
}

TEST_CASE("������: SetFn � ������� ��������� � �����", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("a", "1");
    REQUIRE_THROWS_WITH(calc.SetFn(" badName", "a"), "Invalid usage");
}

TEST_CASE("������: SetFn � �������� ������", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("a", "1");
    REQUIRE_THROWS_WITH(calc.SetFn("1fn", "a"), "Invalid usage");
}

TEST_CASE("������: alias-���������� �� ������� � ����� ���������������", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("x", "1");
    calc.SetFn("f", "x");
    // ��������� ���������� �� f
    calc.SetLet("y", "f");
    // �� �������������� f ����� let ������
    REQUIRE_THROWS_WITH(calc.SetLet("f", "y"), "Name already exists");
}
