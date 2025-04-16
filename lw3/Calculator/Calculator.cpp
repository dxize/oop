#include "Calculator.h"
#include <string>
#include <iostream>

void Calc::SetVar(const std::string& name)
{
	//добавить проверку на есть ли оно среди переменных
	m_variables_.emplace(name, Variable(name));
}

Variable& Calc::GetVar(const std::string& name)
{
	auto variable = m_variables_.find(name);
	if (variable != m_variables_.end())
	{
		return variable->second;
	}
	else
	{
		static Variable dummy; 
		return dummy;
	}
}

void Calc::EnsureVarExists(const std::string& name)
{
	if (!GetVar(name).IsFound())
	{
		m_variables_.emplace(name, Variable(name));
	}
}

void Calc::SetLet(const std::string& name, const std::string& value)
{
	std::size_t pos;
	double num = std::stod(value, &pos);

	if (pos == value.size()) // Если все символы строки обработаны, то pos должен равняться размеру строки(если число)
	{
		EnsureVarExists(name);
		GetVar(name).SetValue(num);
	}
	else
	{
		EnsureVarExists(name);
		GetVar(name).SetValue(GetVar(value).GetValue());
	}
}