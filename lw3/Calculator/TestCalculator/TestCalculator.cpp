#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"

#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include "../Calculator.h"


//добавит тесты негативные больше 

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

TEST_CASE("Функция Evaluate", "[calculator]") {
    Calc calc;

    SECTION("Вычисление значения переменной") {
        calc.SetLet("x", "10");
        REQUIRE(calc.Evaluate("x") == Approx(10.0));
    }

    SECTION("Вычисление значения функции с одной переменной") {
        calc.SetLet("x", "5");
        calc.SetFn("f", "x");
        REQUIRE(calc.Evaluate("f") == Approx(5.0));
    }

    SECTION("Вычисление значения функции с двумя переменными (сложение)") {
        calc.SetLet("a", "3");
        calc.SetLet("b", "7");
        calc.SetFn("sum", "a + b");
        REQUIRE(calc.Evaluate("sum") == Approx(10.0));
    }

    SECTION("Вычисление значения функции с двумя переменными (вычитание)") {
        calc.SetLet("a", "10");
        calc.SetLet("b", "4");
        calc.SetFn("sub", "a - b");
        REQUIRE(calc.Evaluate("sub") == Approx(6.0));
    }

    SECTION("Вычисление значения функции с двумя переменными (умножение)") {
        calc.SetLet("a", "2");
        calc.SetLet("b", "3");
        calc.SetFn("mul", "a * b");
        REQUIRE(calc.Evaluate("mul") == Approx(6.0));
    }

    SECTION("Вычисление значения функции с двумя переменными (деление)") {
        calc.SetLet("a", "10");
        calc.SetLet("b", "2");
        calc.SetFn("div", "a / b");
        REQUIRE(calc.Evaluate("div") == Approx(5.0));
    }

    SECTION("Деление на ноль должно вернуть NAN") {
        calc.SetLet("a", "10");
        calc.SetLet("b", "0");
        calc.SetFn("div", "a / b");
        REQUIRE(std::isnan(calc.Evaluate("div")));
    }

    SECTION("Вычисление функции с аргументами-функциями") {
        calc.SetLet("a", "2");
        calc.SetLet("b", "3");
        calc.SetFn("f1", "a + b");        // f1 = 5
        calc.SetLet("c", "4");
        calc.SetFn("f2", "f1 * c");       // f2 = 5 * 4 = 20
        REQUIRE(calc.Evaluate("f2") == Approx(20.0));
    }

    SECTION("Неопределённое значение должно вернуть NAN") {
        REQUIRE(std::isnan(calc.Evaluate("not_exist")));
    }
}

TEST_CASE("PrintVars: пустой список переменных", "[calculator][printvars]") {
    Calc calc;
    REQUIRE(calc.SortVars() == "");
}

TEST_CASE("PrintVars: вывод переменных отсортированных по алфавиту", "[calculator][printvars]") {
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

TEST_CASE("PrintVars: вывод переменной с неопределённым значением (nan)", "[calculator][printvars]") {
    Calc calc;

    calc.SetVar("x");
    std::string expected = "x:nan\n";

    REQUIRE(calc.SortVars() == expected);
}

TEST_CASE("PrintFns: пустой список функций", "[calculator][printfns]") {
    Calc calc;

    REQUIRE(calc.SortFns() == "");
}

TEST_CASE("PrintFns: вывод функций отсортированных по алфавиту", "[calculator][printfns]") {
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

TEST_CASE("PrintFns: функция с неопределённым значением (nan)", "[calculator][printfns]") {
    Calc calc;

    calc.SetLet("a", "10");
    calc.SetLet("b", "0");
    calc.SetFn("div", "a / b");  

    std::string expected = "div:nan\n";
    REQUIRE(calc.SortFns() == expected);
}

TEST_CASE("Ошибка: недопустимый идентификатор в SetVar", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar("1invalid"), "Invalid usage");
}

TEST_CASE("Ошибка: недопустимый идентификатор в SetLet", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("2var", "100"), "Invalid usage");
}

TEST_CASE("Ошибка: использование имени функции в SetLet", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("x", "10");
    calc.SetFn("f", "x");
    REQUIRE_THROWS_WITH(calc.SetLet("f", "20"), "Name already exists");
}

TEST_CASE("Ошибка: использование необъявленной переменной в SetLet", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("a", "b"), "Name does not exist");
}

TEST_CASE("Ошибка: использование необъявленного идентификатора в SetFn", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetFn("f", "x + y"), "Name does not exist");
}

TEST_CASE("Ошибка: попытка создания функции с уже используемым именем", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("v", "10");
    REQUIRE_THROWS_WITH(calc.SetFn("v", "x + y"), "Name already exists");
}

TEST_CASE("Ошибка: создание функции с неверным числом аргументов", "[calculator][errors]") {
    Calc calc;

    calc.SetLet("a", "10");
    calc.SetLet("b", "20");
    
    REQUIRE_THROWS_WITH(calc.SetFn("f1", "+"), "Invalid usage");

    REQUIRE_THROWS_WITH(calc.SetFn("f2", "a + b + a"), "Invalid usage");
}


//добавил
TEST_CASE("Ошибка: пустое имя переменной в SetVar", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar(""), "Invalid usage");
}

TEST_CASE("Ошибка: пробелы в имени переменной в SetVar", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar("a b"), "Invalid usage");
}

TEST_CASE("Ошибка: недопустимый символ в имени переменной", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetVar("var!"), "Invalid usage");
}

TEST_CASE("Ошибка: пустое имя в SetLet", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("", "123"), "Invalid usage");
}

TEST_CASE("Ошибка: SetLet с недопустимым rhs (нечисло и неидентификатор)", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetLet("x", "@@@"), "Name does not exist");
}

TEST_CASE("Ошибка: SetFn с пустым выражением", "[calculator][errors]") {
    Calc calc;
    REQUIRE_THROWS_WITH(calc.SetFn("h", ""), "Invalid usage");
}

TEST_CASE("Ошибка: SetFn с лишними пробелами в имени", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("a", "1");
    REQUIRE_THROWS_WITH(calc.SetFn(" badName", "a"), "Invalid usage");
}

TEST_CASE("Ошибка: SetFn с числовым именем", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("a", "1");
    REQUIRE_THROWS_WITH(calc.SetFn("1fn", "a"), "Invalid usage");
}

TEST_CASE("Ошибка: alias-переменная на функцию и затем переопределение", "[calculator][errors]") {
    Calc calc;
    calc.SetLet("x", "1");
    calc.SetFn("f", "x");
    // правильно делегируем на f
    calc.SetLet("y", "f");
    // но переопределить f через let нельзя
    REQUIRE_THROWS_WITH(calc.SetLet("f", "y"), "Name already exists");
}
