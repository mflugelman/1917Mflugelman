#pragma once
#include <string>
#include "Unit.h"

class Tank : public Unit
{
public:
	Tank();
	~Tank();
	void attack(shared_ptr<Unit> attackedUnit);
	void setSprites(bool isUserPlayer);

private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
	const int SIZE = 64;
};
