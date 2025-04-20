#include <string>
#include <vector>
#include "Functions.h"

void Function::SetSign(std::string sign)
{
	m_operation = sign;
}

std::string Function::GetSign()
{
	return m_operation;
}

void Function::SetVars(std::vector<std::string> variables)
{
	m_variables = variables;
}

std::vector<std::string> Function::GetVars()
{
	return m_variables;
}

