#include "Tank.h"
#include <iostream>

Tank::Tank() {}

Tank::Tank(bool isUserPlayer, shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound) : Unit(texture, sound)
{
	setScale(0.4, 0.4);

	m_cost = 1000;
	m_spriteSize = 64;
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