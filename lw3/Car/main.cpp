#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include "Car.h"

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

enum class CommandType {
    Info,
    EngineOn,
    EngineOff,
    SetGear,
    SetSpeed,
    Exit,
    Unknown
};

CommandType GetCommandType(const std::string& command)
{
    if (command == "Info")
        return CommandType::Info;
    else if (command == "EngineOn")
        return CommandType::EngineOn;
    else if (command == "EngineOff")
        return CommandType::EngineOff;
    else if (command.rfind("SetGear", 0) == 0)
        return CommandType::SetGear;
    else if (command.rfind("SetSpeed", 0) == 0)
        return CommandType::SetSpeed;
    else if (command == "Exit")
        return CommandType::Exit;
    else
        return CommandType::Unknown;
}

void ProcessCommand(const std::string& command, Car& car)
{
    try
    {
        CommandType type = GetCommandType(command);
        switch (type)
        {
        case CommandType::Info:
            car.Info();
            break;
        case CommandType::EngineOn:
            car.TurnOnEngine();
            std::cout << "Engine turned on\n\n";
            break;
        case CommandType::EngineOff:
            car.TurnOffEngine();
            std::cout << "Engine turned off\n\n";
            break;
        case CommandType::SetGear:
            HandleCommandWithInt(command, 8, &Car::SetGear, car);
            break;
        case CommandType::SetSpeed:
            HandleCommandWithInt(command, 9, &Car::SetSpeed, car);
            break;
        case CommandType::Exit:
            std::exit(0);
            break;
        case CommandType::Unknown:
            std::cout << "Unknown command\n\n";
            break;
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << "\n\n";
    }
}

int main()
{
    Car myCar;
    std::string command;

    while (std::getline(std::cin, command))
    {
        ProcessCommand(command, myCar);
    }

    return 0;
}
