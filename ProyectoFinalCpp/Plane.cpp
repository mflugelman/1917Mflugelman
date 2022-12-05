#include "Plane.h"
#include <iostream>

Plane::Plane() {}

Plane::Plane(bool isUserPlayer, shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound) : Unit(texture, sound)
{
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