#pragma once
#include <string>
#include "Unit.h"

class Plane : public Unit
{
public:
	Plane();
	Plane(bool isUserPlayer, shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound);
	~Plane();
	void attack(shared_ptr<Unit> attackedUnit);
	void setSprites(bool isUserPlayer);
};
