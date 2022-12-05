#include "Player.h"
#include "ButtonGroup.h"
#include "Unit.h"
#include "Tank.h"
#include "Plane.h"
#include "Infantry.h"
#include "Explosion.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <SFML/Audio.hpp>
#include "AssetManager.h"
#include "AssetsEnums.h"

using namespace std;

class GameManager
{
public:
	GameManager(sf::RenderWindow& window);
	~GameManager();

	void initializeGame();
	void runGame();

private:
	void drawUnits(std::shared_ptr<Player> player);
	void update();
	shared_ptr<Unit> spawnUnit(int unitType, int x, int y, bool isUserPlayer);
	void moveUnits(std::shared_ptr<Player> player, int direction);
	void enemyAI();
	void battle(shared_ptr<Unit> unit1, shared_ptr<Unit> unit2);
	void drawTexts();
	void cleanup();
	void handleCollisions();
	AssetManager assetManager;

	vector<shared_ptr<Explosion>> m_explosions;
	sf::RenderWindow& m_window;
	shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_background;
	const int c_baseSize = 70;
	ButtonGroup m_buttons;
	std::shared_ptr<Player> m_userPlayer;
	std::shared_ptr<Player> m_enemyPlayer;
	sf::Clock m_clock;
	sf::Music music;
	sf::Sound spawnSound;
};