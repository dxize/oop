#include "Car.h"
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::pair<int, int>> speedRange = {
    {0, 20},   // Задний ход	
    {0, 150},  // Нейтраль
    {0, 30},   // Первая
    {20, 50},  // Вторая
    {30, 60},  // Третья
    {40, 90},  // Четвертая
    {50, 150}  // Пятая
};

bool Car::IsTurnedOn()
{
    return m_isTurnedOn;
}

std::string Car::GetDirection() const
{
    return DirectionToString(m_direction);
}

int Car::GetSpeed()
{
    return m_speed;
}

int Car::GetGear()
{
    return m_gear;
}

void Car::TurnOnEngine()
{
    m_isTurnedOn = true;
}

void Car::TurnOffEngine()
{
    if (m_isTurnedOn && m_gear == 0 && m_speed == 0)
    {
        m_isTurnedOn = false;
    }
    else
    {
        throw std::runtime_error("Car must be stopped and in neutral gear");
    }
}

void Car::SetGear(int gear)
{
    if (gear < m_MIN_GEAR || gear > m_MAX_GEAR)
    {
        throw std::runtime_error("Invalid gear");     
    }
    if (!m_isTurnedOn)
    {
        throw std::runtime_error("Cannot set gear while engine is off");
    }
    if (m_direction != Direction::StandingStill && (m_gear == 0 && gear != 0 || gear == -1 && m_gear != 0 || m_gear == -1 && gear != 0))
    {
        throw std::runtime_error("Cannot reverse while moving");
    }
    if (m_speed > speedRange[gear + 1].second || m_speed < speedRange[gear + 1].first)
    {
        throw std::runtime_error("Unsuitable current speed");
    }

    m_gear = gear;
}

void Car::SetSpeed(int speed)
{
    if (speed < 0)
    {
        throw std::runtime_error("Speed cannot be negative");
    }
    if (!m_isTurnedOn)
    {
        throw std::runtime_error("Cannot set speed while engine is off");
    }
    if (m_gear == 0 && speed > m_speed)
    {
        throw std::runtime_error("Cannot accelerate on neutral");
    }
    if (speed < speedRange[m_gear + 1].first || speed > speedRange[m_gear + 1].second)
    {
        throw std::runtime_error("Speed is out of gear range");
    }

    m_speed = speed;
    SetDirection();
}

void Car::Info()
{
    std::cout << "Engine: " << (m_isTurnedOn ? "on" : "off") << "\n"
        << "Direction: " << GetDirection() << "\n"
        << "Speed: " << m_speed << "\n"
        << "Gear: " << m_gear << "\n\n";
}

void Car::SetDirection()
{
    if (m_speed == 0)
    {
        m_direction = Direction::StandingStill;
    }
    else if (m_gear == -1)
    {
        m_direction = Direction::Backward;
    }
    else if (m_gear > 0 && m_direction != Direction::Backward)
    {
        m_direction = Direction::Forward;
    }
}

std::string Car::DirectionToString(Direction d) const
{
    switch (d)
    {
    case Direction::StandingStill:
        return "standing still";
    case Direction::Forward:
        return "forward";
    case Direction::Backward:
        return "backward";
    }
    return "";
}
