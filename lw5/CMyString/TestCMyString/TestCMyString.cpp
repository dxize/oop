#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "CMyString.h"
#include <sstream>
#include <string>
#include <cstring>  

TEST_CASE("Конструктор по умолчанию создаёт пустую строку", "[CMyString][Constructor]") {
    CMyString s;
    REQUIRE(s.GetLength() == 0);
    REQUIRE(std::string(s.GetStringData()) == "");
    REQUIRE(s.GetCapacity() == 0);
}

TEST_CASE("Конструктор из const char* без встроенных нулей", "[CMyString][Constructor]") {
    const char* cstr = "Hello";
    CMyString s(cstr);
    REQUIRE(s.GetLength() == 5);
    REQUIRE(std::string(s.GetStringData(), s.GetLength()) == "Hello");
    REQUIRE(s.GetCapacity() == 5);
}

TEST_CASE("Конструктор из пустой C-строки", "[CMyString][Constructor]") {
    const char* cstr = "";
    CMyString s(cstr);
    REQUIRE(s.GetLength() == 0);
    REQUIRE(std::string(s.GetStringData()) == "");
    REQUIRE(s.GetCapacity() == 0);
}

TEST_CASE("Конструктор из const char* с встроенными нулями", "[CMyString][Constructor]") {
    const char raw[] = { 'A', '\0', 'B', 'C' };
    CMyString s(raw, 4);
    REQUIRE(s.GetLength() == 4);
    const char* data = s.GetStringData();
    REQUIRE(data[0] == 'A');
    REQUIRE(data[1] == '\0');
    REQUIRE(data[2] == 'B');
    REQUIRE(data[3] == 'C');
    REQUIRE(data[4] == '\0');
    REQUIRE(s.GetCapacity() == 4);
}

TEST_CASE("Конструктор из std::string", "[CMyString][Constructor]") {
    std::string stl = std::string("Foo\0Bar", 7);  
    CMyString s(stl);
    REQUIRE(s.GetLength() == 7);
    const char* data = s.GetStringData();
    REQUIRE(std::memcmp(data, stl.data(), 7) == 0);
    REQUIRE(data[7] == '\0');
    REQUIRE(s.GetCapacity() == 7);
}

TEST_CASE("Конструктор копирования", "[CMyString][Copy]") {
    CMyString original("DeepCopy");
    CMyString copy(original);
    REQUIRE(copy.GetLength() == original.GetLength());
    REQUIRE(std::string(copy.GetStringData(), copy.GetLength()) ==
        std::string(original.GetStringData(), original.GetLength()));


    CMyString o2("ModifyMe");
    CMyString o2copy(o2);
    REQUIRE(o2.GetLength() == o2copy.GetLength());
    o2[0] = 'X';
    REQUIRE(o2[0] == 'X');
    REQUIRE(o2copy[0] == 'M');  
}

TEST_CASE("Перемещающий конструктор", "[CMyString][Move]") {
    CMyString a("MoveMe");
    size_t oldLen = a.GetLength();
    size_t oldCap = a.GetCapacity();
    const char* oldData = a.GetStringData();

    CMyString b(std::move(a));
    REQUIRE(b.GetLength() == oldLen);
    REQUIRE(b.GetCapacity() == oldCap);
    REQUIRE(b.GetStringData() == oldData);

    REQUIRE(a.GetLength() == 0);
    REQUIRE(std::string(a.GetStringData()) == "");
    REQUIRE(a.GetCapacity() == 0);
}

TEST_CASE("Оператор копирующего присваивания и самоприсваивание", "[CMyString][Assignment]") {
    CMyString s1("AssignMe");
    CMyString s2;
    s2 = s1;
    REQUIRE(s2.GetLength() == s1.GetLength());
    REQUIRE(std::string(s2.GetStringData(), s2.GetLength()) ==
        std::string(s1.GetStringData(), s1.GetLength()));

    s1[0] = 'Z';
    REQUIRE(s1[0] == 'Z');
    REQUIRE(s2[0] == 'A'); 

    s2 = s2;
    REQUIRE(std::string(s2.GetStringData(), s2.GetLength()) == "AssignMe");
}

TEST_CASE("Перемещающее присваивание", "[CMyString][Assignment]") {
    CMyString s1("MoveAssign");
    size_t len = s1.GetLength();
    size_t cap = s1.GetCapacity();
    const char* ptr = s1.GetStringData();

    CMyString s2;
    s2 = std::move(s1);
    REQUIRE(s2.GetLength() == len);
    REQUIRE(s2.GetCapacity() == cap);
    REQUIRE(s2.GetStringData() == ptr);

    REQUIRE(s1.GetLength() == 0);
    REQUIRE(std::string(s1.GetStringData()) == "");
    REQUIRE(s1.GetCapacity() == 0);
}

TEST_CASE("Оператор += и удвоение capacity при переполнении", "[CMyString][Append]") {
    CMyString s("12345");
    size_t initialCap = s.GetCapacity();
    REQUIRE(initialCap == 5);

    CMyString suffix("67");
    s += suffix;  // "1234567"
    REQUIRE(s.GetLength() == 7);
    REQUIRE(s.GetCapacity() >= 7);
    REQUIRE(std::string(s.GetStringData(), s.GetLength()) == "1234567");

    CMyString big("ABCDEFGH"); // длина 8
    size_t beforeCap = s.GetCapacity();
    s += big;
    REQUIRE(s.GetLength() == 7 + 8);
    REQUIRE(s.GetCapacity() >= 15);
    REQUIRE(std::string(s.GetStringData(), s.GetLength()) == "1234567ABCDEFGH");
}

TEST_CASE("Операторы + для CMyString, std::string, const char*", "[CMyString][Concat]") {
    CMyString a("Hello");
    CMyString b("World");
    CMyString c = a + b;
    REQUIRE(c.GetLength() == 10);
    REQUIRE(std::string(c.GetStringData(), c.GetLength()) == "HelloWorld");

    std::string stl = "Foo";
    CMyString cm("Bar");
    CMyString d = stl + cm;
    REQUIRE(d.GetLength() == 6);
    REQUIRE(std::string(d.GetStringData(), d.GetLength()) == "FooBar");

    const char* literal = "Start";
    CMyString e = literal + CMyString("End");
    REQUIRE(e.GetLength() == 8);
    REQUIRE(std::string(e.GetStringData(), e.GetLength()) == "StartEnd");
}

TEST_CASE("Операторы == и !=", "[CMyString][Compare]") {
    CMyString x("Alpha");
    CMyString y("Alpha");
    CMyString z("Beta");
    REQUIRE(x == y);
    REQUIRE(!(x != y));
    REQUIRE(x != z);
    REQUIRE(!(x == z));
}

TEST_CASE("Лексикографические сравнения", "[CMyString][Compare]") {
    CMyString a("Apple");
    CMyString b("Banana");
    CMyString c("ApplePie");
    CMyString d("App");

    REQUIRE(a < b);
    REQUIRE(b > a);
    REQUIRE(a < c);      
    REQUIRE(d < a);      
    REQUIRE(a > d);
    REQUIRE(a <= c);
    REQUIRE(c >= a);
    REQUIRE(a <= a);
    REQUIRE(a >= a);
}

TEST_CASE("Оператор [] для чтения и записи", "[CMyString][Index]") {
    CMyString s("Bounds");
    REQUIRE(s.GetLength() == 6);
    // чтение
    REQUIRE(s[0] == 'B');
    REQUIRE(s[5] == 's');
    // запись
    s[0] = 'b';
    REQUIRE(s[0] == 'b');
}

TEST_CASE("SubString возвращает корректную подстроку", "[CMyString][SubString]") {
    CMyString base("SubstringTest");
    CMyString sub1 = base.SubString(3, 6);   
    REQUIRE(sub1.GetLength() == 6);
    REQUIRE(std::string(sub1.GetStringData(), sub1.GetLength()) == "string");

    CMyString sub2 = base.SubString(3);      
    REQUIRE(sub2.GetLength() == 10);
    REQUIRE(std::string(sub2.GetStringData(), sub2.GetLength()) == "stringTest");

    CMyString sub3 = base.SubString(20, 5);
    REQUIRE(sub3.GetLength() == 0);
    REQUIRE(std::string(sub3.GetStringData()) == "");
}

TEST_CASE("Clear обнуляет длину, но сохраняет capacity", "[CMyString][Clear]") {
    CMyString s("ClearMe");
    size_t capBefore = s.GetCapacity();
    REQUIRE(s.GetLength() == 7);
    s.Clear();
    REQUIRE(s.GetLength() == 0);
    REQUIRE(std::string(s.GetStringData()) == "");
    REQUIRE(s.GetCapacity() == capBefore);
}

TEST_CASE("Операторы << и >> для ввода/вывода", "[CMyString][IO]") {
    CMyString s("StreamTest");
    std::ostringstream oss;
    oss << s;
    REQUIRE(oss.str() == "StreamTest");

    std::istringstream iss("HelloWorld NextToken");
    CMyString a, b;
    iss >> a >> b;
    REQUIRE(a.GetLength() == 10);
    REQUIRE(std::string(a.GetStringData(), a.GetLength()) == "HelloWorld");
    REQUIRE(b.GetLength() == 9);
    REQUIRE(std::string(b.GetStringData(), b.GetLength()) == "NextToken");

    std::istringstream emptyIss("");
    CMyString emp;
    REQUIRE(!(emptyIss >> emp));
    REQUIRE(emp.GetLength() == 0);
    REQUIRE(std::string(emp.GetStringData()) == "");
}