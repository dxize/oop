#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Car.h" 

TEST_CASE("Управление двигателем", "[Car]") {
    Car car;

    SECTION("Включение двигателя") {
        // При первом включении двигатель должен включиться
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Повторное включение двигателя") {
        // Повторное включение не должно приводить к ошибке и двигатель остается включенным
        car.TurnOnEngine();
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Выключение двигателя при ненулевой скорости или ненейтральной передаче") {
        // При включенном двигателе с передачей 1 и ненулевой скоростью выключить двигатель нельзя
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        // Ожидается исключение с сообщением
        REQUIRE_THROWS_WITH(car.TurnOffEngine(), "Car must be stopped and in neutral gear");
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Успешное выключение двигателя") {
        // Для выключения двигателя нужно: двигатель включен, передача 0 и скорость 0
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);      // Переключаем в нейтраль
        car.SetSpeed(0);     // Останавливаем автомобиль
        REQUIRE_NOTHROW(car.TurnOffEngine());
        REQUIRE(car.IsTurnedOn() == false);
    }
}

TEST_CASE("Переключение передач", "[Car]") {
    Car car;

    SECTION("Переключение при выключенном двигателе") {
        // Попытка установить любую передачу при выключенном двигателе должна выбрасывать исключение
        REQUIRE_THROWS_WITH(car.SetGear(1), "Cannot set gear while engine is off");
    }

    SECTION("Неверное значение передачи") {
        car.TurnOnEngine();
        // Значение передачи вне диапазона -1..5 приводит к ошибке
        REQUIRE_THROWS_WITH(car.SetGear(10), "Invalid gear");
    }

    SECTION("Успешное переключение на подходящую передачу") {
        car.TurnOnEngine();
        // При нулевой скорости можно перейти с нейтрали на первую передачу
        REQUIRE_NOTHROW(car.SetGear(1));
        // Разгоняемся в пределах диапазона первой передачи (0–30)
        REQUIRE_NOTHROW(car.SetSpeed(20));
        // При скорости 20 возможно переключение на вторую (диапазон второй: 20–50)
        REQUIRE_NOTHROW(car.SetGear(2));
        REQUIRE_NOTHROW(car.SetSpeed(40));
    }

    SECTION("Попытка переключения на передачу с неподходящей скоростью") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15);  // Для первой передачи (0–30) скорость 15 подходит
        // Переключение на вторую передачу (20–50) при скорости 15 должно вызвать ошибку
        REQUIRE_THROWS_WITH(car.SetGear(2), "Unsuitable current speed");
    }

    SECTION("Переключение на заднюю передачу при ненулевой скорости") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        // Переход на заднюю передачу возможен только при нулевой скорости
        REQUIRE_THROWS_WITH(car.SetGear(-1), "Cannot reverse while moving");
        // Если сначала установить скорость 0, переключение должно пройти успешно
        car.SetSpeed(0);
        REQUIRE_NOTHROW(car.SetGear(-1));
    }
}

TEST_CASE("Изменение скорости", "[Car]") {
    Car car;

    SECTION("Отрицательное значение скорости") {
        car.TurnOnEngine();
        car.SetGear(1);
        // Установка отрицательной скорости должна вызывать исключение
        REQUIRE_THROWS_WITH(car.SetSpeed(-5), "Speed cannot be negative");
    }

    SECTION("Установка скорости при выключенном двигателе") {
        // При выключенном двигателе установка скорости невозможна
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Cannot set speed while engine is off");
    }

    SECTION("Ускорение на нейтральной передаче запрещено") {
        car.TurnOnEngine();
        // Разгон на первой передаче
        car.SetGear(1);
        car.SetSpeed(30);
        // Переключаемся в нейтраль
        REQUIRE_NOTHROW(car.SetGear(0));
        // Попытка увеличить скорость на нейтрали (от 30 до 40) должна выбросить исключение
        REQUIRE_THROWS_WITH(car.SetSpeed(40), "Cannot accelerate on neutral");
        // При этом снижение скорости допускается
        REQUIRE_NOTHROW(car.SetSpeed(20));
        REQUIRE(car.GetSpeed() == 20);
    }

    SECTION("Установка скорости вне диапазона выбранной передачи") {
        car.TurnOnEngine();
        car.SetGear(1);
        // Первая передача: диапазон 0–30, установка скорости 35 должна вызвать ошибку
        REQUIRE_THROWS_WITH(car.SetSpeed(35), "Speed is out of gear range");
        // Для успешного переключения на вторую передачу скорость должна быть на границе допустимого диапазона первой передачи
        car.SetSpeed(30);
        REQUIRE_NOTHROW(car.SetGear(2));  // Вторая передача: диапазон 20–50
        // Попытка установить скорость, которая не входит в диапазон второй передачи, должна вызвать исключение
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Speed is out of gear range");
    }
}

TEST_CASE("Определение направления движения", "[Car]") {
    Car car;

    SECTION("Автомобиль стоит на месте") {
        car.TurnOnEngine();
        car.SetGear(0);
        car.SetSpeed(0);
        // При нулевой скорости направление должно быть "standing still"
        REQUIRE(car.GetDirection() == "standing still");
    }

    SECTION("Движение вперёд") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        // При положительной скорости и передней передаче направление должно быть "forward"
        REQUIRE(car.GetDirection() == "forward");
    }

    SECTION("Движение назад") {
        car.TurnOnEngine();
        // Переключение на заднюю передачу возможно при нулевой скорости
        car.SetGear(-1);
        // При установке скорости в пределах диапазона задней передачи (0–20) направление должно быть "backward"
        REQUIRE_NOTHROW(car.SetSpeed(15));
        REQUIRE(car.GetDirection() == "backward");
    }
}
