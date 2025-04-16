#include "Calculator.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

void Calc::SetVar(const std::string& name)
{
    if (!GetVar(name).IsFound())
    {
        m_variables.emplace(name, Variable(name));
    }
}

Variable& Calc::GetVar(const std::string& name)
{
	auto variable = m_variables.find(name);
	if (variable != m_variables.end())
	{
		return variable->second;
	}
	else
	{
		static Variable dummy; 
		return dummy;
	}
}

void Calc::SetLet(const std::string& name, const std::string& value)
{
    try {
        std::size_t pos;
        double num = std::stod(value, &pos);
        // ≈сли строка полностью преобразована в число, то pos равен длине строки
        if (pos == value.size())
        {
            SetVar(name);
            GetVar(name).SetValue(num);
        }
        else
        {
            // ≈сли число извлекаетс€ не полностью Ч интерпретируем как им€ переменной
            SetVar(name);
            GetVar(name).SetValue(GetVar(value).GetValue());
        }
    }
    catch (const std::invalid_argument&)
    {
        // ≈сли std::stod не смог преобразовать строку, значит, это не число.
        SetVar(name);
        GetVar(name).SetValue(GetVar(value).GetValue());
    }
}

Function& Calc::GetFn(const std::string& name)
{
    auto function = m_functions.find(name);
    if (function != m_functions.end())
    {
        return function->second;
    }
    else
    {
        static Function dummy;
        return dummy;
    }
}

bool Calc::EnsureFnExists(const std::string& name, std::vector<std::string>& variables, const std::string& sign)
{
    if (name[0] > '0' && name[0] < '0')
    {
        throw std::runtime_error("Invalid usage");
    }
    
    if (!GetFn(name).IsFound())
    {
        m_functions.emplace(name, Function(name, variables, sign));
        return false;
    }

    return true;
}

void Calc::ParseFnExpression(const std::string& name, const std::string& value, 
    std::vector<std::string>& variables, std::string& sign)
{
    std::istringstream stream(value);
    std::string word;

    if (!EnsureFnExists(name, variables, sign))
    {
        while (stream >> word)
        {
            if (word.size() == 1 && (word == "+" || word == "-" || word == "*" || word == "/"))
            {
                sign = word;
                continue;
            }

            if (!GetVar(word).IsFound()) {
                throw std::runtime_error("Name does not exist");
            }

            variables.push_back(word);
        }
    }
    else
    {
        throw std::runtime_error("Name already exists");
    }

    if (variables.size() == 0 || variables.size() > 2) {
        throw std::runtime_error("Invalid usage");
    }

}

void Calc::SetFn(const std::string& name, const std::string& value)
{
    std::vector<std::string> variables;
    std::string sign;

    ParseFnExpression(name, value, variables, sign);

    if (sign.size() == 1)
    {
        GetFn(name).SetSign(sign);
    }

    GetFn(name).SetVars(variables);

}