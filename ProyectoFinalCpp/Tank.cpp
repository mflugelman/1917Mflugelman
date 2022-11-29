#include "Tank.h"
#include <iostream>

const std::string Tank::s_frontSpriteFile = "../assests/tankFront.png";
const std::string Tank::s_backSpriteFile = "../assets/tankBack.png";
Tank::Tank() : Unit()
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(s_backSpriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	setScale(0.4, 0.4);

	setTexture(*m_texture);
	m_cost = 100;
	m_movement = 1;
	m_isAlive = true;
	m_strength = 50+ rand() % (50/ 2 + 1);
	m_type = TANK;

	std::cout << "Tank Created S:" << m_strength << std::endl;
}

Tank::~Tank()
{
	std::cout << "Tank Destroyed" << std::endl;
}

void Tank::attack(shared_ptr<Unit> attackedUnit)
{
	switch (attackedUnit->getType())
	{
	case INFANTRY:
		attackedUnit->takeDamage(m_strength*2);
		break;
	case TANK:
		attackedUnit->takeDamage(m_strength);
		break;
	case PLANE:
		attackedUnit->takeDamage(m_strength / 2);
	default:
		break;
	}
}