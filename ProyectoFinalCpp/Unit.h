#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;

class Unit : public sf::CircleShape
{
public:
	Unit(int movement, float radius);
	~Unit();

	void move_y(float y);

private:
	int m_movement;
};



