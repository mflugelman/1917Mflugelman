#pragma once
#include <string>
#include "Unit.h"

class Tank : public Unit
{
public:
	Tank();
	Tank(bool isUserPlayer, shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound);
	~Tank();
	void attack(shared_ptr<Unit> attackedUnit);
};
