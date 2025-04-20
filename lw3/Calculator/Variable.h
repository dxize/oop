#pragma once

#include <string>

class Variable
{
public:
	Variable(const std::string& name) : m_name(name), m_value(NAN) {}

	double GetValue();
	std::string GetName();

	void SetValue(double value);

private:
	std::string m_name;
	double m_value = NAN;
};