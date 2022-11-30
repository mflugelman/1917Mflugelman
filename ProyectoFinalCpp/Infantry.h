#include <string>
#include "Unit.h"

class Infantry : public Unit
{
public:
	Infantry();
	~Infantry();
	void attack(shared_ptr<Unit> attackedUnit);
	void setSprites(bool isUserPlayer);

private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
};
