#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "CStringStack.h"

TEST_CASE("Пустой стек ведет себя корректно") {
    CStringStack stack;
    REQUIRE(stack.empty());
    REQUIRE(stack.size() == 0);

    SECTION("top выбрасывает исключение для пустого стека") {
        REQUIRE_THROWS_AS(stack.top(), StackEmpty);
    }

    SECTION("pop выбрасывает исключение для пустого стека") {
        REQUIRE_THROWS_AS(stack.pop(), StackEmpty);
    }
}

TEST_CASE("Push и top работают корректно") {
    CStringStack stack;
    stack.push("первый");
    REQUIRE_FALSE(stack.empty());
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == "первый");

    stack.push("второй");
    REQUIRE(stack.size() == 2);
    REQUIRE(stack.top() == "второй");
}

TEST_CASE("Pop удаляет верхний элемент") {
    CStringStack stack;
    stack.push("первый");
    stack.push("второй");

    stack.pop();
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == "первый");

    stack.pop();
    REQUIRE(stack.empty());
}

TEST_CASE("Конструктор копирования создает глубокую копию") {
    CStringStack original;
    original.push("a");
    original.push("b");

    CStringStack copy(original);
    REQUIRE(copy.size() == 2);
    REQUIRE(copy.top() == "b");

    // Изменения оригинала не должны повлиять на копию
    original.pop();
    REQUIRE(copy.top() == "b");
}

TEST_CASE("Оператор присваивания использует идиому copy-and-swap") {
    CStringStack a;
    a.push("x");
    CStringStack b;
    b.push("y");
    b.push("z");

    a = b;
    REQUIRE(a.size() == b.size());
    REQUIRE(a.top() == "z");

    b.pop();
    REQUIRE(a.top() == "z"); // не изменился
}

TEST_CASE("Конструктор перемещения передает ресурсы") {
    CStringStack a;
    a.push("перемещено");

    CStringStack b(std::move(a));
    REQUIRE(b.size() == 1);
    REQUIRE(b.top() == "перемещено");
    REQUIRE(a.empty());  // после перемещения источник пуст
}

TEST_CASE("Оператор перемещающего присваивания передает владение") {
    CStringStack a;
    a.push("один");

    CStringStack b;
    b = std::move(a);

    REQUIRE(b.size() == 1);
    REQUIRE(b.top() == "один");
    REQUIRE(a.empty());
}

TEST_CASE("Push с перемещением работает") {
    CStringStack stack;
    std::string str = "динамический";
    stack.push(std::move(str));
    REQUIRE(stack.top() == "динамический");
}
