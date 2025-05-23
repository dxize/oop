#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "CStringStack.h"

TEST_CASE("������ ���� ����� ���� ���������") {
    CStringStack stack;
    REQUIRE(stack.empty());
    REQUIRE(stack.size() == 0);

    SECTION("top ����������� ���������� ��� ������� �����") {
        REQUIRE_THROWS_AS(stack.top(), StackEmpty);
    }

    SECTION("pop ����������� ���������� ��� ������� �����") {
        REQUIRE_THROWS_AS(stack.pop(), StackEmpty);
    }
}

TEST_CASE("Push � top �������� ���������") {
    CStringStack stack;
    stack.push("������");
    REQUIRE_FALSE(stack.empty());
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == "������");

    stack.push("������");
    REQUIRE(stack.size() == 2);
    REQUIRE(stack.top() == "������");
}

TEST_CASE("Pop ������� ������� �������") {
    CStringStack stack;
    stack.push("������");
    stack.push("������");

    stack.pop();
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == "������");

    stack.pop();
    REQUIRE(stack.empty());
}

TEST_CASE("����������� ����������� ������� �������� �����") {
    CStringStack original;
    original.push("a");
    original.push("b");

    CStringStack copy(original);
    REQUIRE(copy.size() == 2);
    REQUIRE(copy.top() == "b");

    // ��������� ��������� �� ������ �������� �� �����
    original.pop();
    REQUIRE(copy.top() == "b");
}

TEST_CASE("�������� ������������ ���������� ������ copy-and-swap") {
    CStringStack a;
    a.push("x");
    CStringStack b;
    b.push("y");
    b.push("z");

    a = b;
    REQUIRE(a.size() == b.size());
    REQUIRE(a.top() == "z");

    b.pop();
    REQUIRE(a.top() == "z"); // �� ���������
}

TEST_CASE("����������� ����������� �������� �������") {
    CStringStack a;
    a.push("����������");

    CStringStack b(std::move(a));
    REQUIRE(b.size() == 1);
    REQUIRE(b.top() == "����������");
    REQUIRE(a.empty());  // ����� ����������� �������� ����
}

TEST_CASE("�������� ������������� ������������ �������� ��������") {
    CStringStack a;
    a.push("����");

    CStringStack b;
    b = std::move(a);

    REQUIRE(b.size() == 1);
    REQUIRE(b.top() == "����");
    REQUIRE(a.empty());
}

TEST_CASE("Push � ������������ ��������") {
    CStringStack stack;
    std::string str = "������������";
    stack.push(std::move(str));
    REQUIRE(stack.top() == "������������");
}
