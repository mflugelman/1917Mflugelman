#include <string>
#include "Unit.h"

class Infantry : public Unit
{
public:
	Infantry();
	~Infantry();
	void attack(shared_ptr<Unit> attackedUnit);
	sf::RectangleShape rectangle;

private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
};
