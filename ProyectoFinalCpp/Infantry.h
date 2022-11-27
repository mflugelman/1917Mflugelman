#include <string>
#include "Unit.h"

class Infantry : public Unit
{
public:
	Infantry();
	~Infantry();

private:
	static const std::string s_frontSpriteFile;
	static const std::string s_backSpriteFile;
};
