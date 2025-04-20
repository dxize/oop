#pragma once

#include <string>
#include <vector>

class Function
{
public:
	Function(const std::string& name, std::vector<std::string>& variables, const std::string& operation) :
		m_name(name), m_variables(variables), m_operation(operation), m_found(true) {}

	void SetSign(std::string operation);

	std::string GetSign();

	void SetVars(std::vector<std::string> variables);
	std::vector<std::string> GetVars();

private:
	std::string m_name;
	std::string m_operation;
	std::vector<std::string> m_variables;
	bool m_found;
};
