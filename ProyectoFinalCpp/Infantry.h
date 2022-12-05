#include <string>
#include "Unit.h"

class Infantry : public Unit
{
public:
	Infantry();
	Infantry(bool isUserPlayer, shared_ptr<sf::Texture> texture, shared_ptr<sf::SoundBuffer> sound);
	~Infantry();
	void attack(shared_ptr<Unit> attackedUnit);
	void move_y(float y) override;

private:
	sf::IntRect m_spriteRectangle;
};
