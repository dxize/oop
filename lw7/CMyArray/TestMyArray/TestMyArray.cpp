#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../CMyArray.h"
#include <string>
#include <utility>

TEST_CASE("������ �� ��������� ����", "[CMyArray]") 
{
    CMyArray<int> a;
    REQUIRE(a.Size() == 0);
    REQUIRE(a.begin() == a.end());
}

TEST_CASE("���������� ��������� � ���������� ������", "[CMyArray]") 
{
    CMyArray<int> a;
    a.PushBack(10);
    REQUIRE(a.Size() == 1);
    REQUIRE(a[0] == 10);

    a.PushBack(20);
    REQUIRE(a.Size() == 2);
    REQUIRE(a[1] == 20);
}

TEST_CASE("operator[] ������� std::out_of_range ��� ������ �� �������", "[CMyArray]") 
{
    CMyArray<int> a;
    a.PushBack(1);
    REQUIRE_THROWS_AS(a[1], std::out_of_range);
    REQUIRE_THROWS_WITH(a[5], "Index out of bounds");
}

TEST_CASE("Resize ����������� � �������������� ������", "[CMyArray]") 
{
    CMyArray<int> a;
    a.PushBack(5);
    a.Resize(4);
    REQUIRE(a.Size() == 4);
    REQUIRE(a[0] == 5);
    REQUIRE(a[1] == 0);
    REQUIRE(a[2] == 0);
    REQUIRE(a[3] == 0);
}

TEST_CASE("Resize ��������� ������ �������", "[CMyArray]") 
{
    CMyArray<int> a;
    for (int i = 0; i < 5; ++i) a.PushBack(i);
    a.Resize(2);
    REQUIRE(a.Size() == 2);
    REQUIRE(a[0] == 0);
    REQUIRE(a[1] == 1);
    REQUIRE_THROWS_AS(a[2], std::out_of_range);
}

TEST_CASE("Clear ������� ��� ��������", "[CMyArray]") 
{
    CMyArray<int> a;
    a.PushBack(1);
    a.PushBack(2);
    a.Clear();
    REQUIRE(a.Size() == 0);
    REQUIRE(a.begin() == a.end());
}

TEST_CASE("��������� ������ � ����� �������� ���������", "[CMyArray]") 
{
    CMyArray<std::string> a;
    a.PushBack("a");
    a.PushBack("b");
    a.PushBack("c");

    std::vector<std::string> forward;
    for (auto& s : a)
    {
        forward.push_back(s);
    }
    REQUIRE(forward == std::vector<std::string>{"a", "b", "c"});

    std::vector<std::string> backward;
    for (auto it = a.rbegin(); it != a.rend(); ++it) 
    {
        backward.push_back(*it);
    }
    REQUIRE(backward == std::vector<std::string>{"c", "b", "a"});
}

TEST_CASE("�����������: ����������� � �������� ������������", "[CMyArray]") 
{
    CMyArray<int> a;
    for (int i = 0; i < 3; ++i) a.PushBack(i);
    
    SECTION("����������� �����������") 
    {
        CMyArray<int> b(a);
        REQUIRE(b.Size() == 3);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 1);
        REQUIRE(b[2] == 2);
    }

    SECTION("�������� ����������� ������������") 
    {
        CMyArray<int> b;
        b = a;
        REQUIRE(b.Size() == 3);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 1);
        REQUIRE(b[2] == 2);
    }
}

TEST_CASE("�����������: ����������� � �������� ������������", "[CMyArray]") 
{
    CMyArray<int> a;
    for (int i = 0; i < 4; ++i) a.PushBack(i);

    SECTION("����������� �����������") 
    {
        CMyArray<int> b(std::move(a));
        REQUIRE(b.Size() == 4);
        REQUIRE(b[3] == 3);
        REQUIRE(a.Size() == 0);
    }

    SECTION("�������� ������������� ������������") 
    {
        CMyArray<int> b;
        b = std::move(a);
        REQUIRE(b.Size() == 4);
        REQUIRE(b[3] == 3);
        REQUIRE(a.Size() == 0);
    }
}

TEST_CASE("������ � ����� float", "[CMyArray]") 
{
    CMyArray<float> a;
    a.PushBack(1.5f);
    a.PushBack(2.5f);
    REQUIRE(a.Size() == 2);
    REQUIRE(a[0] == Approx(1.5f));
    REQUIRE(a[1] == Approx(2.5f));
}

TEST_CASE("������ � ����� std::string", "[CMyArray]") 
{
    CMyArray<std::string> a;
    a.PushBack("foo");
    a.PushBack("bar");
    REQUIRE(a.Size() == 2);
    REQUIRE(a[0] == "foo");
    REQUIRE(a[1] == "bar");
}//����������� ������ ���� � ���������� ��������
//������� ���� �����
