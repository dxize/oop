#pragma once

#include <string>

class Variable
{
public:
	Variable(const std::string& name) : m_name(name), m_value(NAN), m_found(true) {}

	Variable() : m_name("Переменная не найдена"), m_value(NAN), m_found(false) {}

	double GetValue();
	std::string GetName();

	void SetValue(double value);

	bool IsFound() const;

private:
	std::string m_name;
	double m_value = NAN;
	bool m_found;
};