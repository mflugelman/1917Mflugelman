#include "Infantry.h"
#include <iostream>

Infantry::Infantry() {}

Infantry::Infantry(bool isUserPlayer, shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound) : Unit(texture, sound)
{
	m_spriteRectangle = isUserPlayer ? sf::IntRect(0, 64, 64, 64) : sf::IntRect(0, 0, 64, 64);

	setTextureRect(m_spriteRectangle);

	m_sound.setVolume(10.0f);

	m_movement = 1;
	m_spriteSize = 64;
	m_cost = 200;
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

void Infantry::move_y(float y)
{
	move(0, -y * m_movement);

	int currentPos = getPosition().y;
	//Update only on multiples of 4 for a smooth movement
	if (currentPos % 3 == 0) {
		if (m_spriteRectangle.left == m_spriteSize * 3)
			m_spriteRectangle.left = 0;
		else
			m_spriteRectangle.left += m_spriteSize;

		setTextureRect(m_spriteRectangle);
	}
}

