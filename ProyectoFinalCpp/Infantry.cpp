#include "Infantry.h"
#include <iostream>

const std::string Infantry::s_frontSpriteFile = "../assests/";
const std::string Infantry::s_backSpriteFile = "../assets/infantryback1.png";

Infantry::Infantry()
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(s_backSpriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	setTexture(*m_texture);

	m_movement = 1;
	m_cost = 100;
	m_isAlive = true;
	m_strength = (int)INFANTRY + rand() % ((int)INFANTRY / 2 + 1);
	m_type = INFANTRY;

	std::cout << "Infantry Created" << std::endl; 
}

Infantry::~Infantry()
{
	std::cout << "Infantry Destroyed" << std::endl;
}

