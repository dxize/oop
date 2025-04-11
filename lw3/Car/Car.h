#pragma once
#include <string>

enum class Direction {
    StandingStill,
    Forward,
    Backward
};

class Car
{
public:
    bool IsTurnedOn();
    std::string GetDirection() const;
    int GetSpeed();
    int GetGear();
    void TurnOnEngine();
    void TurnOffEngine();
    void SetGear(int gear);
    void SetSpeed(int speed);
    void Info();
private:
    const int m_MAX_GEAR = 5;
    const int m_MIN_GEAR = -1;
    int m_speed = 0;
    int m_gear = 0;
    Direction m_direction = Direction::StandingStill;
    bool m_isTurnedOn = false;

    void SetDirection();

    std::string DirectionToString(Direction d) const;
};
