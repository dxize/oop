#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../CDate.h"  
#include <sstream>

TEST_CASE("Конструктор по умолчанию устанавливает 01.01.1970 и действительна", "CDate()") {
    CDate d;
    REQUIRE(d.IsValid());
    REQUIRE(d.GetDay() == 1);
    REQUIRE(d.GetMonth() == Month::JANUARY);
    REQUIRE(d.GetYear() == 1970);
    REQUIRE(d.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("Проверка параметризованного конструктора на валидность и невалидность даты", "CDate(day, month, year)") {
    SECTION("Корректная дата") {
        CDate d(29, Month::FEBRUARY, 2020);
        REQUIRE(d.IsValid());
        REQUIRE(d.GetDay() == 29);
        REQUIRE(d.GetMonth() == Month::FEBRUARY);
        REQUIRE(d.GetYear() == 2020);
    }
    SECTION("Неверный день в месяце") {
        CDate d(31, Month::APRIL, 2021);
        REQUIRE_FALSE(d.IsValid());
    }
    SECTION("Год вне диапазона") {
        CDate d(1, Month::JANUARY, 1969);
        REQUIRE_FALSE(d.IsValid());
    }
}

TEST_CASE("Конструктор по таймстемпу и обратное преобразование", "CDate(timestamp)") {
    CDate epoch(0u);
    REQUIRE(epoch.IsValid());
    REQUIRE(epoch.GetDay() == 1);
    REQUIRE(epoch.GetMonth() == Month::JANUARY);
    REQUIRE(epoch.GetYear() == 1970);

    CDate next(1u);
    REQUIRE(next.IsValid());
    REQUIRE(next.GetDay() == 2);
}

TEST_CASE("Операторы инкремента и декремента", "операторы ++, --") {
    CDate d(1, Month::MARCH, 2021);
    ++d;
    REQUIRE(d.GetDay() == 2);
    CDate tmp = d++;
    REQUIRE(tmp.GetDay() == 2);
    REQUIRE(d.GetDay() == 3);

    --d;
    REQUIRE(d.GetDay() == 2);
    tmp = d--;
    REQUIRE(tmp.GetDay() == 2);
    REQUIRE(d.GetDay() == 1);
}

TEST_CASE("Сложение и вычитание дней", "операторы +, - (дни)") {
    CDate d(28, Month::FEBRUARY, 2010);
    CDate r = d + 3;
    REQUIRE(r.GetDay() == 3);
    REQUIRE(r.GetMonth() == Month::MARCH);
    REQUIRE(r.GetYear() == 2010);

    CDate r2 = 3 + d;
    REQUIRE(r2 == r);

    CDate s = r - 5;
    REQUIRE(s.GetDay() == 26);
    REQUIRE(s.GetMonth() == Month::FEBRUARY);
    REQUIRE(s.GetYear() == 2010);
}

TEST_CASE("Разность двух дат в днях", "оператор -(CDate)") {
    CDate d1(1, Month::JANUARY, 2010);
    CDate d2(30, Month::DECEMBER, 2009);
    REQUIRE((d1 - d2) == 2);
    REQUIRE((d2 - d1) == -2);
}

TEST_CASE("Составные операции += и -=", "операторы +=, -=") {
    CDate d(1, Month::JANUARY, 2000);
    d += 366;
    REQUIRE(d.GetYear() == 2001);
    d -= 366;                
    REQUIRE(d.GetYear() == 2000);
}

TEST_CASE("Операторы сравнения дат", "<, >, <=, >=, ==, !=") {
    CDate a(1, Month::JANUARY, 2000);
    CDate b(2, Month::JANUARY, 2000);
    REQUIRE(a < b);
    REQUIRE(b > a);
    REQUIRE(a <= a);
    REQUIRE(b >= b);
    REQUIRE(a != b);
    REQUIRE_FALSE(a == b);
}

TEST_CASE("Потоковый ввод и вывод дат", "операторы <<, >>") {
    CDate d(5, Month::NOVEMBER, 2025);
    std::ostringstream oss;
    oss << d;
    REQUIRE(oss.str() == "05.11.2025");

    std::istringstream iss("15.08.1947");
    CDate in;
    iss >> in;
    REQUIRE_FALSE(in.IsValid());

    std::istringstream iss2("29.02.2024");
    CDate in2;
    iss2 >> in2;
    REQUIRE(in2.IsValid());
    REQUIRE(in2.GetDay() == 29);
    REQUIRE(in2.GetMonth() == Month::FEBRUARY);
    REQUIRE(in2.GetYear() == 2024);
}

TEST_CASE("Переход за границы диапазона делает дату невалидной", "проверка границ диапазона") {
    CDate end(31, Month::DECEMBER, 9999);
    ++end;
    REQUIRE_FALSE(end.IsValid());
    CDate begin(1, Month::JANUARY, 1970);
    --begin;
    REQUIRE_FALSE(begin.IsValid());
}
//добавить тесты на невалидность