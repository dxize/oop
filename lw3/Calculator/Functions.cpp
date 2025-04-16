#include <string>
#include <vector>

class Function
{
public:
	Function(const std::string& name, std::vector<std::string>& variables, const std::string& sign) : 
		m_name(name), m_variables(variables),m_sign(sign), m_found(true) {}

	Function() : m_name("Функция не найдена"), m_found(false) {}

	bool IsFound() const
	{
		return m_found;
	}

	void SetSign(std::string sign)
	{
		m_sign = sign;
	}

	std::string GetSign()
	{
		return m_sign;
	}

	void SetVars(std::vector<std::string> variables)
	{
		m_variables = variables;
	}

	std::vector<std::string> GetVars()
	{
		return m_variables;
	}

private:
	std::string m_name;
	std::string m_sign;
	std::vector<std::string> m_variables;
	bool m_found;
};