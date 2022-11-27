#include "Unit.h"

Unit::Unit()
{
	cout << "Unit Created" << endl;
}


Unit::Unit(UnitType unit_type)
{
	m_type = unit_type;
	init();
	cout << "Unit Created" << endl;
	cout << "Strength" << m_strength;
}

Unit::~Unit()
{
	delete m_texture;
	cout << "Unit Destroyed" << endl;
}

void Unit::move_y(float y)
{
	move(0, -y * m_movement);

	int currenty = getPosition().y;

	if (currenty + getGlobalBounds().height < 50)
	{
		m_isAlive = false;
	}
}

void Unit::init() {
	switch (m_type)
	{
	case INFANTRY:
		m_cost = 100;
		m_isAlive = true;
		m_strength = (int)INFANTRY + rand() % ((int)INFANTRY / 2 + 1);
		break;
	case TANK:
		m_cost = 500;
		m_isAlive = true;
		m_strength = (int)TANK + rand() % ((int)TANK / 2 + 1);
		break;
	case PLANE:
		m_cost = 1000;
		m_isAlive = true;
		m_strength = (int)PLANE + rand() % ((int)PLANE / 2 + 1);
		break;
	default:
		break;
	}
}