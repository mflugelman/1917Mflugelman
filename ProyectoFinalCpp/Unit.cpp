#include "Unit.h"

Unit::Unit(UnitType unit_type)
{
	m_type = unit_type;
	setRadius(10);
	init();
	setFillColor(sf::Color::White);
	cout << "Unit Created" << endl;
	cout << "Strength" << m_strength;
}

Unit::~Unit()
{
	cout << "Unit Destroyed" << endl;
}

void Unit::move_y(float y)
{
	move(0, -y * m_movement);

	int currenty = getPosition().y;

	if (currenty + getRadius() < 50)
	{
		m_isAlive = false;
	}
	else if (currenty < 50) 
	{
		setRadius(getRadius() + 1);
		setFillColor(sf::Color::Red);
	}
}

void Unit::init() {
	switch (m_type)
	{
	case INFANTRY:
		m_movement = 1;
		m_cost = 100;
		m_isAlive = true;
		m_strength = (int)INFANTRY + rand() % ((int)INFANTRY / 2 + 1);
		break;
	case TANK:
		m_movement = 2;
		m_cost = 500;
		m_isAlive = true;
		m_strength = (int)TANK + rand() % ((int)TANK / 2 + 1);
		break;
	case PLANE:
		m_movement = 4;
		m_cost = 1000;
		m_isAlive = true;
		m_strength = (int)PLANE + rand() % ((int)PLANE / 2 + 1);
		break;
	default:
		break;
	}
}