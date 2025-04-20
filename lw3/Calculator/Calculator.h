#pragma once

#include "Variable.h"
#include "Functions.h"
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
	std::string SortVars();
	std::string SortFns();

	bool HasVar(const std::string& name) const;
	bool HasFn(const std::string& name) const;
private:
	std::unordered_map<std::string, Variable> m_variables;
	std::unordered_map<std::string, Function> m_functions;
	std::unordered_map<std::string, double> m_cache;

	bool EnsureFnExists(const std::string& name, std::vector<std::string>& variables, const std::string& sign);
	void ParseFnExpression(const std::string& name, const std::string& value,
		std::vector<std::string>& variables, std::string& sign);
	bool IsValidIdentifier(const std::string& id);
};