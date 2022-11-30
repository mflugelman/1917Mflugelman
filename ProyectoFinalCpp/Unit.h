#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;

enum UnitType {
	INFANTRY = 1,
	TANK,
	PLANE
};

class Unit : public sf::Sprite
{
public:
	Unit();
	Unit(UnitType);
	virtual ~Unit();

	bool isAlive() { return m_isAlive; }
	void move_y(float y);
	int getCost() { return m_cost; }
	UnitType getType() { return m_type; }
	virtual void attack(shared_ptr<Unit> attackedUnit) = 0;
	void takeDamage(int damage);
	virtual void setSprites(bool isUserPlayer) = 0;
	int m_strength;

protected:
	int m_movement;
	int m_cost;
	int m_isAlive;
	bool m_isUserPlayer;
	UnitType m_type;
	sf::Texture* m_texture;

private:
	void init();
};
