#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

class Car
{
public:
    bool IsTurnedOn()
    {
        return m_isTurnedOn;
    }

    std::string GetDirection()
    {
        return m_direction;
    }

    int GetSpeed()
    {
        return m_speed;
    }

    int GetGear()
    {
        return m_gear;
    }

    void TurnOnEngine()
    {
        m_isTurnedOn = true;
    }

    void TurnOffEngine()
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

    void SetGear(int gear)
    {
        std::vector<std::pair<int, int>> speedRange = {
            {0, 20},   // Задний ход	
            {0, 150},  // Нейтраль
            {0, 30},   // Первая
            {20, 50},  // Вторая
            {30, 60},  // Третья
            {40, 90},  // Четвертая
            {50, 150}  // Пятая
        };

        if (gear < m_MinGear || gear > m_MaxGear)
        {
            throw std::runtime_error("Invalid gear");
        }
        else if (!m_isTurnedOn)
        {
            throw std::runtime_error("Cannot set gear while engine is off");
        }
        else if ((gear == -1 || m_gear == -1) && m_speed != 0)
        {
            throw std::runtime_error("Cannot switch between reverse and forward gears while moving");
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

    void SetSpeed(int speed)
    {
        std::vector<std::pair<int, int>> speedRange = {
            {0, 20},   // Задний ход	
            {0, 150},  // Нейтраль
            {0, 30},   // Первая
            {20, 50},  // Вторая
            {30, 60},  // Третья
            {40, 90},  // Четвертая
            {50, 150}  // Пятая
        };

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

    void Info()
    {
        std::cout << "Engine: " << (m_isTurnedOn ? "on" : "off") << "\n"
            << "Direction: " << m_direction << "\n"
            << "Speed: " << m_speed << "\n"
            << "Gear: " << m_gear << "\n\n";
    }

private:
    const int m_MaxGear = 5;
    const int m_MinGear = -1;
    int m_speed = 0;
    int m_gear = 0;
    std::string m_direction = "standing still";
    bool m_isTurnedOn = false;

    void SetDirection()
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
};

bool TryParseInt(const std::string& str, int& outValue)
{
    std::istringstream iss(str);
    iss >> outValue;
    return !(iss.fail() || !iss.eof());
}

void HandleCommandWithInt(const std::string& command, size_t offset, void (Car::* action)(int), Car& car)
{
    int value;
    if (!TryParseInt(command.substr(offset), value))
    {
        throw std::runtime_error("Invalid command argument");
    }
    (car.*action)(value);
}

int main()
{
    Car myCar;
    std::string command;

    while (true)
    {
        std::getline(std::cin, command);

        try
        {
            if (command == "Info")
            {
                myCar.Info();
            }
            else if (command == "EngineOn")
            {
                myCar.TurnOnEngine();
                std::cout << "Engine turned on\n\n";
            }
            else if (command == "EngineOff")
            {
                myCar.TurnOffEngine();
                std::cout << "Engine turned off\n\n";
            }
            else if (command.rfind("SetGear", 0) == 0)
            {
                HandleCommandWithInt(command, 8, &Car::SetGear, myCar);
            }
            else if (command.rfind("SetSpeed", 0) == 0)
            {
                HandleCommandWithInt(command, 9, &Car::SetSpeed, myCar);
            }
            else if (command == "Exit")
            {
                break;
            }
            else
            {
                std::cout << "Unknown command\n\n";
            }
        }
        catch (const std::runtime_error& e)
        {
            std::cout << e.what() << "\n\n";
        }
    }

    return 0;
}
