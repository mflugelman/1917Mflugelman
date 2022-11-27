#include "Plane.h"
#include <iostream>

const std::string Plane::s_frontSpriteFile = "../assests/";
const std::string Plane::s_backSpriteFile = "../assets/planeback.png";

Plane::Plane()
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(s_backSpriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	setTexture(*m_texture);

	m_movement = 4;
	m_cost = 2000;
	m_isAlive = true;
	m_strength = (int)INFANTRY + rand() % ((int)INFANTRY / 2 + 1);
	m_type = INFANTRY;

	std::cout << "Plane Created" << std::endl;
}

Plane::~Plane()
{
	std::cout << "Plane Destroyed" << std::endl;
}

