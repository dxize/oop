#include <string>
#include "Variable.h"

double Variable::GetValue()
{
	return m_value;
}
std::string Variable::GetName()
{
	return m_name;
}
	
void Variable::SetValue(double value)
{
	m_value = value;
}

