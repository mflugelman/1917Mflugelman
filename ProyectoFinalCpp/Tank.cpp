#include "Tank.h"
#include <iostream>

const std::string Tank::s_frontSpriteFile = "../assets/tankfront.png";
const std::string Tank::s_backSpriteFile = "../assets/tankback.png";

Tank::Tank() {}

Tank::Tank(bool isUserPlayer)
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(isUserPlayer ? s_backSpriteFile : s_frontSpriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}
	setScale(0.4, 0.4);

	setTexture(*m_texture);
	m_soundEffect.loadFromFile("../assets/DeathFlash.flac");
	m_sound.setBuffer(m_soundEffect);

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