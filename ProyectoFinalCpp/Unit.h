#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;

enum UnitType {
	INFANTRY = 10,
	TANK = 50,
	PLANE = 100
};

class Unit : public sf::CircleShape
{
public:
	Unit(UnitType);
	virtual ~Unit();

	bool is_alive() { return m_isAlive; }
	void move_y(float y);
	int get_cost();

protected:
	int m_movement;
	int m_strength;
	int m_cost;
	int m_isAlive;
	UnitType m_type;

private:
	void init();
};
