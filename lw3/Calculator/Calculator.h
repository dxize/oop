#pragma once

#include "Variable.cpp"
#include "Functions.cpp"
#include <unordered_map>
#include <string>
#include <vector>

class Calc
{
public:
	void SetVar(const std::string& name);
	Variable& GetVar(const std::string& name);
	void SetLet(const std::string& name, const std::string& value);

	void SetFn(const std::string& name, const std::string& value);
	Function& GetFn(const std::string& name);

	double Evaluate(const std::string& name);
	std::string PrintVars();
	std::string PrintFn();
private:
	std::unordered_map<std::string, Variable> m_variables;
	std::unordered_map<std::string, Function> m_functions;

	bool EnsureFnExists(const std::string& name, std::vector<std::string>& variables, const std::string& sign);
	void ParseFnExpression(const std::string& name, const std::string& value, 
		std::vector<std::string>& variables, std::string& sign);
};