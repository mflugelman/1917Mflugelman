#pragma once
#include <string>
#include "Unit.h"

class Plane : public Unit
{
public:
	Plane();
	~Plane();
	void attack(shared_ptr<Unit> attackedUnit);
private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
};
