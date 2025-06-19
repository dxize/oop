#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"

#include "../FindMaxEx.h"
#include "../Athlete.h"

#include <vector>

bool CompareByHeight(const Athlete& a, const Athlete& b)
{
    return a.height < b.height;
}

bool CompareByWeight(const Athlete& a, const Athlete& b)
{
    return a.weight < b.weight;
}

struct ThrowOnTallHeight
{
    bool operator()(const Athlete& a, const Athlete& b) const {
        if (b.height > 185.0)
            throw std::runtime_error("Компаратор упал при росте > 185.0");
        return CompareByHeight(a, b);
    }
};

TEST_CASE("FindMaxEx возвращает false для пустого массива")
{
    std::vector<Athlete> athletes;
    Athlete max;
    bool result = FindMaxEx(athletes, max, CompareByHeight);
    REQUIRE_FALSE(result);
}

TEST_CASE("FindMaxEx находит спортсмена с максимальным ростом")
{
    std::vector<Athlete> athletes = {
        {"Ivanov I.I.", 180.0, 75.0},
        {"Petrov P.P.", 190.5, 82.3},
        {"Sidorov S.S.", 178.2, 90.0}
    };

    Athlete maxHeightAthlete;
    bool result = FindMaxEx(athletes, maxHeightAthlete, CompareByHeight);
        
    REQUIRE(result);
    REQUIRE(maxHeightAthlete.name == "Petrov P.P.");
    REQUIRE(maxHeightAthlete.height == Approx(190.5));
}

TEST_CASE("FindMaxEx находит спортсмена с максимальным весом")
{
    std::vector<Athlete> athletes = {
        {"Ivanov I.I.", 180.0, 75.0},
        {"Petrov P.P.", 190.5, 82.3},
        {"Sidorov S.S.", 178.2, 90.0}
    };

    Athlete maxWeightAthlete;
    bool result = FindMaxEx(athletes, maxWeightAthlete, CompareByWeight);

    REQUIRE(result);
    REQUIRE(maxWeightAthlete.name == "Sidorov S.S.");
    REQUIRE(maxWeightAthlete.weight == Approx(90.0));
}

TEST_CASE("FindMaxEx возвращает false при исключении компаратора на объектах Athlete") {
    std::vector<Athlete> athletes = {
        {"Ivanov I.I.", 180.0, 75.0},
        {"Petrov P.P.", 190.5, 82.3}, // здесь бросится исключение
        {"Sidorov S.S.", 178.2, 90.0}
    };

    Athlete result; 
    bool ok = FindMaxEx(athletes, result, ThrowOnTallHeight());

    REQUIRE_FALSE(ok);
}
