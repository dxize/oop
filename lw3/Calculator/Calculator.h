#pragma once

#include "Variable.cpp"
#include <unordered_map>
#include <string>

class Calc
{
public:
	void SetVar(const std::string& name);
	Variable& GetVar(const std::string& name);
	void SetLet(const std::string& name, const std::string& value);

private:
	void EnsureVarExists(const std::string& name);
	std::unordered_map<std::string, Variable> m_variables_;
};