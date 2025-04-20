#include "Calculator.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cmath>

bool Calc::IsValidIdentifier(const std::string& id) {
    if (id.empty()) return false;
    if (!(std::isalpha(id[0]) || id[0] == '_'))
        return false;
    for (char c : id) 
    {
        if (!(std::isalnum(c) || c == '_'))
            return false;
    }
    return true;
}

bool Calc::HasVar(const std::string& name) const
{
    return m_variables.find(name) != m_variables.end();
}

bool Calc::HasFn(const std::string& name) const
{
    return m_functions.find(name) != m_functions.end();
}


void Calc::SetVar(const std::string& name)
{
    m_cache.clear();

    if (!IsValidIdentifier(name))
        throw std::runtime_error("Invalid usage");

    if (HasFn(name))
        throw std::runtime_error("Name already exists");

    if (!HasVar(name))
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
}

void Calc::SetLet(const std::string& name, const std::string& value)
{
    m_cache.clear();

    if (!IsValidIdentifier(name))
        throw std::runtime_error("Invalid usage");

    if (HasFn(name))
        throw std::runtime_error("Name already exists");

    SetVar(name);

    double val;
    std::size_t pos;
  
    try 
    {
        val = std::stod(value, &pos);
        if (pos != value.size())
            throw std::invalid_argument("not full parse");
    }
    catch (...) 
    {
        if (HasVar(value))
        {
            val = GetVar(value).GetValue();
        }
        else if (HasFn(value))
        {
            val = Evaluate(value);
        }
        else
        {
            throw std::runtime_error("Name does not exist");
        }
    }

    GetVar(name).SetValue(val);
}


Function& Calc::GetFn(const std::string& name) 
{
    auto function = m_functions.find(name);
    if (function != m_functions.end())
    {
        return function->second;
    }
}

bool Calc::EnsureFnExists(const std::string& name, std::vector<std::string>& variables, const std::string& sign)
{
    if (!IsValidIdentifier(name))
    {
        throw std::runtime_error("Invalid usage");
    }
    
    if (HasVar(name) || HasFn(name))
    {
        throw std::runtime_error("Name already exists");
    }

    m_functions.emplace(name, Function(name, variables, sign));
    return false;
}

void Calc::ParseFnExpression(const std::string& name, const std::string& value,
    std::vector<std::string>& variables, std::string& sign)
{
    std::string expr;
 
    for (char ch : value) 
    {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') 
        {
            expr.push_back(' ');
            expr.push_back(ch);
            expr.push_back(' ');
        }
        else 
        {
            expr.push_back(ch);
        }
    }
    std::istringstream stream(expr);
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
            
            if (!HasVar(word) && !HasFn(word))
            {
                throw std::runtime_error("Name does not exist");
            }
            variables.push_back(word);
        }
    }
    else 
    {
        throw std::runtime_error("Name already exists");
    }

    if (variables.empty() || variables.size() > 2) 
    {
        throw std::runtime_error("Invalid usage");
    }

}

void Calc::SetFn(const std::string& name, const std::string& value)
{
    m_cache.clear();

    std::vector<std::string> variables;
    std::string sign;

    ParseFnExpression(name, value, variables, sign);

    if (sign.size() == 1)
    {
        GetFn(name).SetSign(sign);
    }

    GetFn(name).SetVars(variables);
}

std::string Calc::SortVars() 
{
    if (m_variables.empty())
        return "";

    std::vector<std::string> keys;
    for (const auto& pair : m_variables)
    {
        keys.push_back(pair.first);
    }
    std::sort(keys.begin(), keys.end());

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    for (const auto& key : keys)
    {
        double val = GetVar(key).GetValue();
        oss << key << ":";
        if (std::isnan(val))
            oss << "nan";
        else
            oss << val;
        oss << "\n";
    }
    return oss.str();
}

std::string Calc::SortFns() 
{
    if (m_functions.empty())
        return "";

    std::vector<std::string> keys;
    for (const auto& pair : m_functions)
    {
        keys.push_back(pair.first);
    }
    std::sort(keys.begin(), keys.end());

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    for (const auto& key : keys)
    {
        double val = Evaluate(key);
        oss << key << ":";
        if (std::isnan(val))
            oss << "nan";
        else
            oss << val;
        oss << "\n";
    }
    return oss.str();
}

double Calc::Evaluate(const std::string& name)
{
    
    auto cache = m_cache.find(name);
    if (cache != m_cache.end()) {
        return cache->second;
    }

    double result = NAN;
    if (HasVar(name)) {
        result = GetVar(name).GetValue();
    }
    else if (HasFn(name)) {
        auto args = GetFn(name).GetVars();
        double op1 = Evaluate(args[0]);
        if (args.size() == 1) {
            result = op1;
        }
        else {
            double op2 = Evaluate(args[1]);
            if (std::isnan(op1) || std::isnan(op2)) {
                result = NAN;
            }
            else {
                auto sign = GetFn(name).GetSign();
                if (sign == "+") result = op1 + op2;
                if (sign == "-") result = op1 - op2;
                if (sign == "*") result = op1 * op2;
                if (sign == "/") result = (op2 != 0 ? op1 / op2 : NAN);
            }
        }
    }
    
    m_cache[name] = result;
    return result;
}
