#include "Plane.h"
#include <iostream>

const std::string Plane::s_frontSpriteFile = "../assets/planefront.png";
const std::string Plane::s_backSpriteFile = "../assets/planeback.png";

Plane::Plane() {}

Plane::Plane(bool isUserPlayer)
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(isUserPlayer ? s_backSpriteFile : s_frontSpriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}
	setTexture(*m_texture);

	m_movement = 4;
	m_spriteSize = 114;
	m_cost = 2000;
	m_isAlive = true;
	m_strength = 100 + rand() % ((int)100 / 2 + 1);
	m_type = PLANE;

	std::cout << "Plane Created S:" << m_strength << std::endl;
}

Plane::~Plane()
{
	std::cout << "Plane Destroyed" << std::endl;
}

void Plane::attack(shared_ptr<Unit> attackedUnit)
{
	switch (attackedUnit->getType())
	{
	case INFANTRY:
		attackedUnit->takeDamage(m_strength * 3);
		break;
	case TANK:
		attackedUnit->takeDamage(m_strength * 2);
		break;
	case PLANE:
		attackedUnit->takeDamage(m_strength);
	default:
		break;
	}
}

void Plane::setSprites(bool isUserPlayer)
{

}