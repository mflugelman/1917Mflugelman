#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

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
	Unit(shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound);
	virtual ~Unit();

	bool isAlive() { return m_isAlive; }
	void setIsAlive(bool isAlive);
	virtual void move_y(float y);
	int getCost();
	UnitType getType() { return m_type; }
	virtual void attack(shared_ptr<Unit> attackedUnit) = 0;
	void takeDamage(int damage);
	int m_strength;
	void setPosition(float x, float y);
	sf::Sound m_sound;

protected:
	int m_movement;
	int m_cost;
	int m_isAlive;
	bool m_isUserPlayer;
	int m_spriteSize;
	UnitType m_type;
	shared_ptr<sf::Texture> m_texture;
	sf::SoundBuffer m_soundEffect;

private:
	void init();
};
