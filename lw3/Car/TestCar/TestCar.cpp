#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Car.h" 

TEST_CASE("Управление двигателем", "[Car]") {
    Car car;

    SECTION("Включение двигателя") {
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Повторное включение двигателя") {
        car.TurnOnEngine();
        REQUIRE_NOTHROW(car.TurnOnEngine());
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Выключение двигателя при ненулевой скорости или ненейтральной передаче") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE_THROWS_WITH(car.TurnOffEngine(), "Car must be stopped and in neutral gear");
        REQUIRE(car.IsTurnedOn() == true);
    }

    SECTION("Успешное выключение двигателя") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetGear(0);   
        car.SetSpeed(0);     
        REQUIRE_NOTHROW(car.TurnOffEngine());
        REQUIRE(car.IsTurnedOn() == false);
    }
}

TEST_CASE("Переключение передач", "[Car]") {
    Car car;

    SECTION("Переключение при выключенном двигателе") {
        REQUIRE_THROWS_WITH(car.SetGear(1), "Cannot set gear while engine is off");
    }

    SECTION("Неверное значение передачи") {
        car.TurnOnEngine();
        REQUIRE_THROWS_WITH(car.SetGear(10), "Invalid gear");
    }

    SECTION("Успешное переключение на подходящую передачу") {
        car.TurnOnEngine();
        REQUIRE_NOTHROW(car.SetGear(1));
        REQUIRE_NOTHROW(car.SetSpeed(20));
        REQUIRE_NOTHROW(car.SetGear(2));
        REQUIRE_NOTHROW(car.SetSpeed(40));
    }

    SECTION("Попытка переключения на передачу с неподходящей скоростью") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15); 
        REQUIRE_THROWS_WITH(car.SetGear(2), "Unsuitable current speed");
    }

    SECTION("Переключение на заднюю передачу при ненулевой скорости и нулевой") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE_THROWS_WITH(car.SetGear(-1), "Cannot reverse while moving");
        car.SetSpeed(0);
        REQUIRE_NOTHROW(car.SetGear(-1));
    }

    //Добавил после ревью
    SECTION("Переключение с задней передачи на нейтральную следом на переденюю на скорости") {
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetGear(0);
        REQUIRE_THROWS_WITH(car.SetGear(1), "Cannot reverse while moving");
    }
}

TEST_CASE("Изменение скорости", "[Car]") {
    Car car;

    SECTION("Отрицательное значение скорости") {
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE_THROWS_WITH(car.SetSpeed(-5), "Speed cannot be negative");
    }

    SECTION("Установка скорости при выключенном двигателе") {
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Cannot set speed while engine is off");
    }

    SECTION("Ускорение на нейтральной передаче запрещено, снижение разрешено") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE_NOTHROW(car.SetGear(0));
        REQUIRE_THROWS_WITH(car.SetSpeed(40), "Cannot accelerate on neutral");
        REQUIRE_NOTHROW(car.SetSpeed(20));
        REQUIRE(car.GetSpeed() == 20);
    }

    SECTION("Установка скорости вне диапазона выбранной передачи") {
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE_THROWS_WITH(car.SetSpeed(35), "Speed is out of gear range");
        car.SetSpeed(30);
        REQUIRE_NOTHROW(car.SetGear(2)); 
        REQUIRE_THROWS_WITH(car.SetSpeed(10), "Speed is out of gear range");
    }
}

TEST_CASE("Определение направления движения", "[Car]") {
    Car car;

    SECTION("Автомобиль стоит на месте") {
        car.TurnOnEngine();
        car.SetGear(0);
        car.SetSpeed(0);
        REQUIRE(car.GetDirection() == "standing still");
    }

    SECTION("Движение вперёд") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        REQUIRE(car.GetDirection() == "forward");
    }

    SECTION("Движение назад") {
        car.TurnOnEngine();
        car.SetGear(-1);
        REQUIRE_NOTHROW(car.SetSpeed(15));
        REQUIRE(car.GetDirection() == "backward");
    }

    //Добавил после ревью
    SECTION("Перключение с задней передачи на нейтраль при уменьшении скорости для проверки верного отображения ротации направления движения") {
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetGear(0);
        car.SetSpeed(8);
        REQUIRE(car.GetDirection() == "backward");
    }
}
