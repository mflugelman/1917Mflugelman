#include "Tank.h"
#include <iostream>

const std::string Tank::s_frontSpriteFile = "../assests/tankFront.png";
const std::string Tank::s_backSpriteFile = "../assets/tankBack.png";

Tank::Tank()
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(s_backSpriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	setScale(0.4, 0.4);

	setTexture(*m_texture);

	m_movement = 1;
	m_cost = 100;
	m_isAlive = true;
	m_strength = (int)INFANTRY + rand() % ((int)INFANTRY / 2 + 1);
	m_type = INFANTRY;

	std::cout << "Tank Created" << std::endl;
}

Tank::~Tank()
{
	std::cout << "Tank Destroyed" << std::endl;
}

