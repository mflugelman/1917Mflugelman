#pragma once
#include <string>
#include "Unit.h"

class Plane : public Unit
{
public:
	Plane();
	~Plane();

private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
};
