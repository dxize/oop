#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Car.h"

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

std::string Car::GetDirection()
{
    return m_direction;
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
    else if (!m_isTurnedOn)
    {
        throw std::runtime_error("Cannot set gear while engine is off");
    }
    else if (gear == -1 && m_speed != 0) 
    {
        throw std::runtime_error("Cannot reverse while moving");
    }
    else if (m_speed > speedRange[gear + 1].second || m_speed < speedRange[gear + 1].first)
    {
        throw std::runtime_error("Unsuitable current speed");
    }
    else
    {
        m_gear = gear;
    }
}

void Car::SetSpeed(int speed)
{
    if (speed < 0)
    {
        throw std::runtime_error("Speed cannot be negative");
    }
    else if (!m_isTurnedOn)
    {
        throw std::runtime_error("Cannot set speed while engine is off");
    }
    else if (m_gear == 0 && speed > m_speed)
    {
        throw std::runtime_error("Cannot accelerate on neutral");
    }
    else if (speed < speedRange[m_gear + 1].first || speed > speedRange[m_gear + 1].second)
    {
        throw std::runtime_error("Speed is out of gear range");
    }
    else
    {
        m_speed = speed;
        SetDirection();
    }
}

void Car::Info()
{
    std::cout << "Engine: " << (m_isTurnedOn ? "on" : "off") << "\n"
        << "Direction: " << m_direction << "\n"
        << "Speed: " << m_speed << "\n"
        << "Gear: " << m_gear << "\n\n";
}

void Car::SetDirection()
{
    if (m_speed == 0)
    {
        m_direction = "standing still";
    }
    else if (m_gear == -1)
    {
        m_direction = "backward";
    }
    else
    {
        m_direction = "forward";
    }
}