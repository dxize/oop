#pragma once
#include <string>

class Car
{
public:
    bool IsTurnedOn();
    std::string GetDirection();
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
    std::string m_direction = "standing still";
    bool m_isTurnedOn = false;

    void SetDirection();
};