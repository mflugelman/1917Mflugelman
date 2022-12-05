#include "Unit.h"

Unit::Unit()
{
	m_isAlive = true;
	cout << "Unit Created" << endl;
}

Unit::Unit(shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound)
{
	m_isAlive = true;
	setTexture(*texture);
	m_sound.setBuffer(*sound);
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
	cout << "Unit Destroyed" << endl;
}

void Unit::move_y(float y)
{
	move(0, -y * m_movement);
}

int Unit::getCost()
{
	return m_cost;
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

void Unit::takeDamage(int damage)
{
	m_strength -= damage;

	if (m_strength <= 0)
		m_isAlive = false;
}

void Unit::setPosition(float x, float y)
{
	float correctedX = x - m_spriteSize / 2.0f < 0 ? m_spriteSize / 2.0f : x - m_spriteSize / 2;

	sf::Sprite::setPosition(correctedX, y);
}

void Unit::setIsAlive(bool isAlive) { m_isAlive = isAlive; }