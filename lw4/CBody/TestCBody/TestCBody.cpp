#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include "../../../catch.hpp"

#include <cmath>
#include "../CSphere.h"
#include "../CCone.h"
#include "../CCylinder.h"
#include "../CParallelepiped.h"
#include "../CCompound.h"
#include "../CBodyManager.h"

TEST_CASE("Рассчёты для сферы", "[CSphere]") {
    CSphere sphere(2.0, 500.0);
    double expectedVolume = (4.0 / 3.0) * M_PI * pow(2.0, 3);
    double expectedMass = expectedVolume * 500.0;

    REQUIRE(sphere.GetDensity() == Approx(500.0));
    REQUIRE(sphere.GetVolume() == Approx(expectedVolume));
    REQUIRE(sphere.GetMass() == Approx(expectedMass));
}

TEST_CASE("Рассчёты для цилиндра", "[CCylinder]") {
    CCylinder cyl(1.0, 2.0, 800.0);
    double expectedVolume = M_PI * 1.0 * 1.0 * 2.0;
    double expectedMass = expectedVolume * 800.0;

    REQUIRE(cyl.GetVolume() == Approx(expectedVolume));
    REQUIRE(cyl.GetMass() == Approx(expectedMass));
    REQUIRE(cyl.GetDensity() == Approx(800.0));
}

TEST_CASE("Рассчёты для конуса", "[CCone]") {
    CCone cone(1.0, 3.0, 700.0);
    double expectedVolume = (1.0 / 3.0) * M_PI * 1.0 * 1.0 * 3.0;
    double expectedMass = expectedVolume * 700.0;

    REQUIRE(cone.GetVolume() == Approx(expectedVolume));
    REQUIRE(cone.GetMass() == Approx(expectedMass));
}

TEST_CASE("Рассчёты для параллелепипеда", "[CParallelepiped]") {
    CParallelepiped par(2.0, 3.0, 4.0, 1000.0);
    double expectedVolume = 2.0 * 3.0 * 4.0;
    double expectedMass = expectedVolume * 1000.0;

    REQUIRE(par.GetVolume() == Approx(expectedVolume));
    REQUIRE(par.GetMass() == Approx(expectedMass));
}

TEST_CASE("Агрегация в составном теле", "[CCompound]") {
    auto sphere = std::make_shared<CSphere>(1.0, 1000.0);
    auto cylinder = std::make_shared<CCylinder>(1.0, 2.0, 800.0);

    CCompound compound;
    compound.AddChildBody(sphere);
    compound.AddChildBody(cylinder);

    double expectedVolume = sphere->GetVolume() + cylinder->GetVolume();
    double expectedMass = sphere->GetMass() + cylinder->GetMass();

    REQUIRE(compound.GetVolume() == Approx(expectedVolume));
    REQUIRE(compound.GetMass() == Approx(expectedMass));
    REQUIRE(compound.GetDensity() == Approx(expectedMass / expectedVolume));
}

TEST_CASE("Логика менеджера тел", "[CBodyManager]") {
    CBodyManager manager;

    auto sphere = std::make_shared<CSphere>(2.0, 500.0);
    auto cone = std::make_shared<CCone>(1.0, 2.0, 600.0);

    manager.AddBody(sphere);
    manager.AddBody(cone);

    REQUIRE(manager.FindMaxMass() == sphere);   
    REQUIRE(manager.FindMinWeightInWater() == sphere);
}

TEST_CASE("Составное тело не может содержать само себя", "[CCompound]") {
    auto compound = std::make_shared<CCompound>();
    REQUIRE_THROWS_AS(compound->AddChildBody(compound), std::logic_error);
}

TEST_CASE("Нулевая плотность у пустого составного тела", "[CCompound]") {
    CCompound emptyCompound;
    REQUIRE(emptyCompound.GetVolume() == 0);
    REQUIRE(emptyCompound.GetDensity() == 0);
}
