#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Calculator.h"

enum class Cmd { VAR, LET, FN, PRINT, PRINTVARS, PRINTFNS, EXIT, UNKNOWN };

Cmd parse(const std::string& s) 
{
    if (s == "var")        return Cmd::VAR;
    if (s == "let")        return Cmd::LET;
    if (s == "fn")         return Cmd::FN;
    if (s == "print")      return Cmd::PRINT;
    if (s == "printvars")  return Cmd::PRINTVARS;
    if (s == "printfns")   return Cmd::PRINTFNS;
    if (s == "exit")       return Cmd::EXIT;
        return Cmd::UNKNOWN;
}

std::string trim(const std::string& s) 
{
    auto lb = s.find_first_not_of(" \t\r\n");
    if (lb == std::string::npos) return "";
    auto rb = s.find_last_not_of(" \t\r\n");
    return s.substr(lb, rb - lb + 1);
}

bool HandleCommand(const std::string& line, Calc& calc) {
    std::istringstream in(line);
    std::string kw;
    if (!(in >> kw))
        return true;  // пустая строка, продолжаем цикл

    switch (parse(kw)) 
    {
    case Cmd::VAR: 
    {
        std::string rest;
        std::string id;
        in >> id;
        if (id.empty()) throw std::runtime_error("Invalid usage");
        calc.SetVar(id);
        break;
    }

    case Cmd::LET: 
    {
        std::string rest;
        std::getline(in, rest);
        auto pos = rest.find('=');
        if (pos == std::string::npos) throw std::runtime_error("Invalid usage");

        std::string lhs = trim(rest.substr(0, pos));
        std::string rhs = trim(rest.substr(pos + 1));
        if (lhs.empty() || rhs.empty()) throw std::runtime_error("Invalid usage");

        calc.SetLet(lhs, rhs);
        break;
    }

    case Cmd::FN: 
    {
        std::string rest;
        std::getline(in, rest);
        auto pos = rest.find('=');
        if (pos == std::string::npos) throw std::runtime_error("Invalid usage");

        std::string lhs = trim(rest.substr(0, pos));
        std::string expr = trim(rest.substr(pos + 1));
        if (lhs.empty() || expr.empty()) throw std::runtime_error("Invalid usage");

        calc.SetFn(lhs, expr);
        break;
    }

    case Cmd::PRINT: 
    {
        std::string rest;
        std::getline(in, rest);
        std::string id = trim(rest);
        if (id.empty()) throw std::runtime_error("Invalid usage");

        double v;
        if (calc.GetVar(id).IsFound()) 
        {
            v = calc.GetVar(id).GetValue();
        }
        else if (calc.GetFn(id).IsFound()) 
        {
            v = calc.Evaluate(id);
        }
        else {
            throw std::runtime_error("Name does not exist");
        }

        if (std::isnan(v)) 
        {
            std::cout << "nan\n";
        }
        else {
            std::cout << std::fixed << std::setprecision(2) << v << "\n";
        }
        break;
    }

    case Cmd::PRINTVARS:
        std::cout << calc.SortVars();
        break;

    case Cmd::PRINTFNS:
        std::cout << calc.SortFns();
        break;

    case Cmd::EXIT:
        return false; 

    case Cmd::UNKNOWN:
    default:
        std::cout << "Unknown command\n";
        break;
    }

    return true;
}

int main() 
{
    Calc calc;
    std::string line;

    while (std::getline(std::cin, line)) 
    {
        try 
        {
            if (!HandleCommand(line, calc)) break;
        }
        catch (const std::runtime_error& e) 
        {
            std::cout << e.what() << "\n";
        }
    }

    return 0;
}
