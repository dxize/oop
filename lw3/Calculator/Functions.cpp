#include <string>
#include <vector>
#include "Functions.h"


bool Function::IsFound() const
{
	return m_found;
}

void Function::SetSign(std::string sign)
{
	m_sign = sign;
}

std::string Function::GetSign()
{
	return m_sign;
}

void Function::SetVars(std::vector<std::string> variables)
{
	m_variables = variables;
}

std::vector<std::string> Function::GetVars()
{
	return m_variables;
}

