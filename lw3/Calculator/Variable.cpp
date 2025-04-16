#include <string>

class Variable
{
public:
	Variable(const std::string& name) : m_name(name), m_value(NAN), m_found(true) {}

	Variable() : m_name("Переменная не найдена"), m_value(NAN), m_found(false) {}

	double GetValue()
	{
		return m_value;
	}
	std::string GetName()
	{
		return m_name;
	}
	
	void SetValue(double value)
	{
		m_value = value;
	}

	bool IsFound() const 
	{ 
		return m_found; 
	}

private:
	std::string m_name;
	double m_value = NAN;
	bool m_found;
};