#include "Player.h"
#include "ButtonGroup.h"
#include "Unit.h"
#include "Tank.h"
#include "Plane.h"
#include "Infantry.h"
#include <SFML/Graphics.hpp>

class GameManager
{
public:
	GameManager(sf::RenderWindow& window);
	~GameManager();

	void initializeGame();

	void runGame();
	void drawUnits(std::shared_ptr<Player> player);
	void update();
	shared_ptr<Unit> spawnUnit(int unitType, int x, int y);
	void moveUnits(std::shared_ptr<Player> player, int direction);
	void enemyAI();
	void battle(shared_ptr<Unit> unit1, shared_ptr<Unit> unit2);

private:
	sf::RenderWindow& m_window;
	sf::Texture* m_texture;
	sf::Sprite m_background;
	const int c_baseSize = 70;
	ButtonGroup m_buttons;
	std::shared_ptr<Player> m_userPlayer;
	std::shared_ptr<Player> m_enemyPlayer;
};