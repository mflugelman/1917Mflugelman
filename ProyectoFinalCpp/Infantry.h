#include <string>
#include "Unit.h"

class Infantry : public Unit
{
public:
	Infantry();
	Infantry(bool isUserPlayer);
	~Infantry();
	void attack(shared_ptr<Unit> attackedUnit);
	void move_y(float y) override;

private:
	static const std::string s_sprite;
	static const int s_spriteSize;
	sf::IntRect m_spriteRectangle;
};
