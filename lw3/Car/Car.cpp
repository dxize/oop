#include <iostream>
#include <string>
#include <vector>

class Car 
{
public:

	bool IsTurnedOn()
	{
		return m_isTurnedOn;
	}
	
	std::string GetDirection()
	{
		return m_direction;
	}

	int GetSpeed()
	{
		return m_speed;
	}

	int GetGear()
	{
		return m_gear;
	}

	void TurnOnEngine()
	{
		m_isTurnedOn = true;
	}

	void TurnOffEngine()
	{
		if (m_isTurnedOn && m_gear == 0 && m_speed == 0)
		{
			m_isTurnedOn = false;
		}
	}

	void SetGear(int gear)
	{
		std::vector<std::pair<int, int>> speedRange = { //����������� �������� � ��������� ���������
			{0, 20}, //������ ���	
			{0, 150}, //��������
			{0, 30}, // ������
			{20, 50}, //������
			{30, 60}, //������
			{40, 90}, //���������
			{50, 150} //�����
		};

		if (gear <= m_MaxGear && gear >= m_MinGear)  
		{
			std::cout << "Invalid gear"; //�������
		}
		else if (!m_isTurnedOn)
		{
			std::cout << "�annot set gear while engine is off"; //�������
		}
		else if (gear == -1 && m_speed != 0)
		{
			std::cout << "Cannot reverse while moving"; //�������
		}
		else if (m_speed > speedRange[gear + 1].second || m_speed < speedRange[gear + 1].first)
		{
			std::cout << "Unsuitable current speed"; //�������
		}
		else 
		{
			m_gear = gear;

		}
	}

	void SetSpeed(int speed)
	{
		std::vector<std::pair<int, int>> speedRange = { //����������� �������� � ��������� ���������
			{0, 20}, //������ ���	
			{0, 150}, //��������
			{0, 30}, // ������
			{20, 50}, //������
			{30, 60}, //������
			{40, 90}, //���������
			{50, 150} //�����
		};

		if (speed < 0)
		{
			std::cout << "Speed cannot be negative"; //�������
		}
		else if (!m_isTurnedOn)
		{
			std::cout << "Cannot set speed while engine is off"; //�������
		}
		else if (m_gear == 0)
		{
			std::cout << "Cannot accelerate on neutral"; //�������
		}
		else if (speed <= speedRange[m_gear + 1].first || speed >= speedRange[m_gear + 1].second)
		{
			std::cout << "Speed is out of gear range"; //�������
		}
		else
		{
			m_speed = speed;
			SetDirection();
		}
	}

private:
	const int m_MaxGear = 5;
	const int m_MinGear = -1;
	int m_speed = 0;
	int m_gear = 0;
	std::string m_direction = "standing still";
	bool m_isTurnedOn = false;

	void SetDirection()
	{
		if (m_speed == 0)
		{
			m_direction = "standing still";
		}

		if (m_speed != 0 && m_gear == -1)
		{
			m_direction = "backward";
		}
		else if (m_speed != 0 && m_gear != 0)
		{
			m_direction = "forward";
		}
	}
};

int main()
{
	return 0;
}