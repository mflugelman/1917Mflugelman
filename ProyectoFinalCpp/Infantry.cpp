#include "Infantry.h"
#include <iostream>

const std::string Infantry::s_frontSpriteFile = "../assets/infantryfront.png";
const std::string Infantry::s_backSpriteFile = "../assets/infantryback1.png";

Infantry::Infantry()
{
	m_texture = new sf::Texture;
	m_movement = 1;
	m_cost = 100;
	m_isAlive = true;
	m_strength = 10 + rand() % (10 / 2 + 1);
	m_type = INFANTRY;

	std::cout << "Infantry Created S:" << m_strength << std::endl;
}

Infantry::~Infantry()
{
	std::cout << "Infantry Destroyed" << std::endl;
}

void Infantry::attack(shared_ptr<Unit> attackedUnit) 
{
	switch (attackedUnit->getType())
	{
	case INFANTRY:
		attackedUnit->takeDamage(m_strength);
		break;
	case TANK:
		attackedUnit->takeDamage(m_strength / 2);
		break;
	default:
		break;
	}
}

void Infantry::setSprites(bool isUserPlayer) 
{
	if (!m_texture->loadFromFile(isUserPlayer ? s_backSpriteFile : s_frontSpriteFile ))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	setTexture(*m_texture);
}