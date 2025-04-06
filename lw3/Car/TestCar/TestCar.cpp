#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Car.h" 

TEST_CASE("���������� ����������", "[Car]") {
    Car car;

    SECTION("��������� ���������") {
        // ��� ������ ��������� ��������� ������ ����������
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("��������� ��������� ���������") {
        // ��������� ��������� �� ������ ��������� � ������ � ��������� �������� ����������
        car.TurnOnEngine();
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("���������� ��������� ��� ��������� �������� ��� ������������� ��������") {
        // ��� ���������� ��������� � ��������� 1 � ��������� ��������� ��������� ��������� ������
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        // ��������� ���������� � ����������
        REQUIRE_THROWS_WITH(car.TurnOffEngine(), "Car must be stopped and in neutral gear");
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("�������� ���������� ���������") {
        // ��� ���������� ��������� �����: ��������� �������, �������� 0 � �������� 0
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);      // ����������� � ��������
        car.SetSpeed(0);     // ������������� ����������
        REQUIRE_NOTHROW(car.TurnOffEngine());
        REQUIRE(car.IsTurnedOn() == false);
    }
}

TEST_CASE("������������ �������", "[Car]") {
    Car car;

    SECTION("������������ ��� ����������� ���������") {
        // ������� ���������� ����� �������� ��� ����������� ��������� ������ ����������� ����������
        REQUIRE_THROWS_WITH(car.SetGear(1), "Cannot set gear while engine is off");
    }

    SECTION("�������� �������� ��������") {
        car.TurnOnEngine();
        // �������� �������� ��� ��������� -1..5 �������� � ������
        REQUIRE_THROWS_WITH(car.SetGear(10), "Invalid gear");
    }

    SECTION("�������� ������������ �� ���������� ��������") {
        car.TurnOnEngine();
        // ��� ������� �������� ����� ������� � �������� �� ������ ��������
        REQUIRE_NOTHROW(car.SetGear(1));
        // ����������� � �������� ��������� ������ �������� (0�30)
        REQUIRE_NOTHROW(car.SetSpeed(20));
        // ��� �������� 20 �������� ������������ �� ������ (�������� ������: 20�50)
        REQUIRE_NOTHROW(car.SetGear(2));
        REQUIRE_NOTHROW(car.SetSpeed(40));
    }

    SECTION("������� ������������ �� �������� � ������������ ���������") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15);  // ��� ������ �������� (0�30) �������� 15 ��������
        // ������������ �� ������ �������� (20�50) ��� �������� 15 ������ ������� ������
        REQUIRE_THROWS_WITH(car.SetGear(2), "Unsuitable current speed");
    }

    SECTION("������������ �� ������ �������� ��� ��������� ��������") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        // ������� �� ������ �������� �������� ������ ��� ������� ��������
        REQUIRE_THROWS_WITH(car.SetGear(-1), "Cannot reverse while moving");
        // ���� ������� ���������� �������� 0, ������������ ������ ������ �������
        car.SetSpeed(0);
        REQUIRE_NOTHROW(car.SetGear(-1));
    }
}

TEST_CASE("��������� ��������", "[Car]") {
    Car car;

    SECTION("������������� �������� ��������") {
        car.TurnOnEngine();
        car.SetGear(1);
        // ��������� ������������� �������� ������ �������� ����������
        REQUIRE_THROWS_WITH(car.SetSpeed(-5), "Speed cannot be negative");
    }

    SECTION("��������� �������� ��� ����������� ���������") {
        // ��� ����������� ��������� ��������� �������� ����������
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Cannot set speed while engine is off");
    }

    SECTION("��������� �� ����������� �������� ���������") {
        car.TurnOnEngine();
        // ������ �� ������ ��������
        car.SetGear(1);
        car.SetSpeed(30);
        // ������������� � ��������
        REQUIRE_NOTHROW(car.SetGear(0));
        // ������� ��������� �������� �� �������� (�� 30 �� 40) ������ ��������� ����������
        REQUIRE_THROWS_WITH(car.SetSpeed(40), "Cannot accelerate on neutral");
        // ��� ���� �������� �������� �����������
        REQUIRE_NOTHROW(car.SetSpeed(20));
        REQUIRE(car.GetSpeed() == 20);
    }

    SECTION("��������� �������� ��� ��������� ��������� ��������") {
        car.TurnOnEngine();
        car.SetGear(1);
        // ������ ��������: �������� 0�30, ��������� �������� 35 ������ ������� ������
        REQUIRE_THROWS_WITH(car.SetSpeed(35), "Speed is out of gear range");
        // ��� ��������� ������������ �� ������ �������� �������� ������ ���� �� ������� ����������� ��������� ������ ��������
        car.SetSpeed(30);
        REQUIRE_NOTHROW(car.SetGear(2));  // ������ ��������: �������� 20�50
        // ������� ���������� ��������, ������� �� ������ � �������� ������ ��������, ������ ������� ����������
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Speed is out of gear range");
    }
}

TEST_CASE("����������� ����������� ��������", "[Car]") {
    Car car;

    SECTION("���������� ����� �� �����") {
        car.TurnOnEngine();
        car.SetGear(0);
        car.SetSpeed(0);
        // ��� ������� �������� ����������� ������ ���� "standing still"
        REQUIRE(car.GetDirection() == "standing still");
    }

    SECTION("�������� �����") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        // ��� ������������� �������� � �������� �������� ����������� ������ ���� "forward"
        REQUIRE(car.GetDirection() == "forward");
    }

    SECTION("�������� �����") {
        car.TurnOnEngine();
        // ������������ �� ������ �������� �������� ��� ������� ��������
        car.SetGear(-1);
        // ��� ��������� �������� � �������� ��������� ������ �������� (0�20) ����������� ������ ���� "backward"
        REQUIRE_NOTHROW(car.SetSpeed(15));
        REQUIRE(car.GetDirection() == "backward");
    }
}
