#include "Unit.h"

Unit::Unit(int movement, float radius)
	:m_movement(movement)
{
	setRadius(radius);
	setFillColor(sf::Color::White);
	cout << "Unit Created" << endl;
}

Unit::~Unit()
{
	cout << "Unit Destroyed" << endl;
}

void Unit::move_y(float y)
{
	move(0, y * m_movement);
}