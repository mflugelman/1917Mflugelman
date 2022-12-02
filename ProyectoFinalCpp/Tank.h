#pragma once
#include <string>
#include "Unit.h"

class Tank : public Unit
{
public:
	Tank();
	Tank(bool isUserPlayer);
	~Tank();
	void attack(shared_ptr<Unit> attackedUnit);

private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
};
