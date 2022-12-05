#include "GameManager.h"
#include "AssetManager.h"

GameManager::GameManager(sf::RenderWindow& window)
	:m_window(window)
{
	m_window.setFramerateLimit(30);

	m_clock = sf::Clock();

	AssetManager assetManager = AssetManager();

	music.openFromFile("../assets/song.wav");
	music.setLoop(true);

	m_texture = assetManager.textures.find(Textures::BACKGROUND)->second;
	m_background = sf::Sprite(*m_texture);
}


GameManager::~GameManager()
{
}

void GameManager::initializeGame()
{
	//Create buttons and UI
	sf::Vector2u windowSize = m_window.getSize();
	sf::Color transparentGreen(sf::Color(185, 255, 150, 125));
	int charactherSize = 16;

	Button button(sf::Vector2f(windowSize.x - 30, windowSize.y - 100), transparentGreen, UnitType::INFANTRY, assetManager.textures.find(Textures::INFANTRYBTN)->second, assetManager.font);
	
	button.setText("$ 200");
	button.setFillColor(sf::Color::Green);
	button.setCharacterSize(charactherSize);
	
	Button button2(sf::Vector2f(windowSize.x - 90, windowSize.y - 100), transparentGreen, UnitType::TANK, assetManager.textures.find(Textures::TANKUSER)->second, assetManager.font);
	button2.setText("$ 1000");
	button2.setFillColor(sf::Color::Green);
	button2.setCharacterSize(charactherSize);

	Button button3(sf::Vector2f(windowSize.x - 150, windowSize.y - 100), transparentGreen, UnitType::PLANE, assetManager.textures.find(Textures::PLANEUSER)->second, assetManager.font);
	button3.setText("$ 2000");
	button3.setFillColor(sf::Color::Green);
	button3.setCharacterSize(charactherSize);

	m_buttons.addButton(button3);
	m_buttons.addButton(button2);
	m_buttons.addButton(button);

	//Create players

	shared_ptr<sf::SoundBuffer> basehitsound = assetManager.sounds.find(Audio::BASEHIT)->second;
	m_userPlayer = std::make_shared<Player>(basehitsound);
	m_userPlayer->setBase(windowSize.x, c_baseSize, 0, windowSize.y - c_baseSize);

	m_enemyPlayer = std::make_shared<Player>(basehitsound);
	m_enemyPlayer->setBase(windowSize.x, c_baseSize, 0, 0);

	spawnSound.setBuffer(*assetManager.sounds.find(Audio::SPAWN)->second);
}

void GameManager::runGame()
{
	music.setLoop(true);
		music.play();
	while (m_window.isOpen())
	{
		sf::Event event;

		bool gameActive = m_userPlayer->getHealth() > 0 && m_enemyPlayer->getHealth() > 0;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();

			if (event.type == sf::Event::MouseButtonPressed && !m_buttons.anyButtonPressed(event, m_window) && gameActive)
			{
				sf::Vector2i position = sf::Mouse::getPosition(m_window);
				int selectedUnit = m_buttons.getSelected();

				auto unit = spawnUnit(selectedUnit, position.x, 600, true);

				if (unit != nullptr && m_userPlayer->getMoney() >= unit->getCost())
				{
					m_userPlayer->addUnit(unit);
					m_userPlayer->addMoney(-unit->getCost());
					spawnSound.play();
				}
			}
		}

		int randomSpawnTime = 1 + (rand() % 5);

		if (m_clock.getElapsedTime().asSeconds() > randomSpawnTime && gameActive)
		{
			enemyAI();
			m_clock.restart();
		}

		if (gameActive)
		{
			m_buttons.update(event, m_window);
			update();
		}

		m_window.clear();
		m_window.draw(m_background);
		drawUnits(m_userPlayer);
		drawUnits(m_enemyPlayer);
		m_window.draw(m_enemyPlayer->getBase());
		m_window.draw(m_userPlayer->getBase());
		for (auto explosion : m_explosions)
		{
			m_window.draw(*explosion);
		}
		m_window.draw(m_buttons);
		drawTexts();
		m_window.display();
	}
}

void GameManager::drawUnits(std::shared_ptr<Player> player)
{
	for (auto unit : player->m_units)
	{
		if (unit->isAlive())
			m_window.draw(*unit);
	}
}

shared_ptr<Unit> GameManager::spawnUnit(int unitType, int x, int y, bool isUserPlayer)
{
	switch (unitType)
	{
	case UnitType::TANK:
	{
		shared_ptr<Tank> tank = make_shared<Tank>(isUserPlayer,
			assetManager.textures.find(isUserPlayer ? Textures::TANKUSER : Textures::TANKENEMY )->second, 
			assetManager.sounds.find(Audio::TANK)->second);
		tank->setPosition(x, y);
		return tank;
		break;
	}
	case UnitType::INFANTRY:
	{
		shared_ptr<Infantry> infantry = make_shared<Infantry>(isUserPlayer, 
			assetManager.textures.find(Textures::INFANTRY)->second,
			assetManager.sounds.find(Audio::INFANTRY)->second);
		infantry->setPosition(x, y);
		return infantry;
		break;
	}
	case UnitType::PLANE:
	{
		shared_ptr<Plane> plane = make_shared<Plane>(isUserPlayer, 
			assetManager.textures.find(isUserPlayer ? Textures::PLANEUSER : Textures::PLANEENEMY)->second,
			assetManager.sounds.find(Audio::PLANE)->second);
		plane->setPosition(x, y);
		return plane;
		break;
	}
	default:
		return nullptr;
		break;
	}
}

void GameManager::update()
{
	moveUnits(m_userPlayer, 1);
	moveUnits(m_enemyPlayer, -1);

	for (auto explosion : m_explosions)
	{
		if (!explosion->isFinished())
			explosion->animate();
	}

	m_userPlayer->addMoney(2);
	m_enemyPlayer->addMoney(1 + rand() % 5);

	//Case for when player doesnt have units on game:
	handleCollisions();

	cleanup();
}

void GameManager::moveUnits(std::shared_ptr<Player> player, int direction)
{
	for (auto unit : player->m_units)
	{
		unit->move_y(direction);
	}
}

void GameManager::enemyAI()
{
	int unittype = 1 + rand() % (3);

	int position = rand() % (m_window.getSize().x + 1);

	auto unit = spawnUnit(unittype, position, 0, false);

	if (m_enemyPlayer->getMoney() >= unit->getCost())
	{
		m_enemyPlayer->addUnit(unit);
		m_enemyPlayer->addMoney(-unit->getCost());
	}
}

void GameManager::battle(shared_ptr<Unit> unit1, shared_ptr<Unit> unit2)
{
	int attacker = (rand() % 2) + 1;
	cout << "Battle" << endl;
	cout << "U1: " << unit1->m_strength << " U2: " << unit2->m_strength << endl;

	unit1->m_sound.play();
	unit2->m_sound.play();

	if (attacker == 1)
	{
		unit1->attack(unit2);

		if (unit2->isAlive())
			unit2->attack(unit1);
		
		if(!unit1->isAlive())
			m_enemyPlayer->addMoney(unit2->getCost());
		else
			m_userPlayer->addMoney(unit2->getCost());
	}
	else
	{
		unit2->attack(unit1);
		if (unit1->isAlive())
			unit1->attack(unit2);
		
		if (!unit2->isAlive())
			m_userPlayer->addMoney(unit2->getCost());
		else
			m_enemyPlayer->addMoney(unit1->getCost());

	}
}

void GameManager::drawTexts()
{
	sf::Text text;

	sf::Vector2u windowSize = m_window.getSize();

	text.setFont(*assetManager.font);

	//Print money
	text.setString("$ : " + to_string(m_userPlayer->getMoney()));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setPosition(windowSize.x - 175, windowSize.y - 160);
	m_window.draw(text);

	//Print health
	text.setString("Health : " + to_string(m_userPlayer->getHealth()));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setPosition(windowSize.x - 175, windowSize.y - 190);
	m_window.draw(text);

	//Print enemy health
	text.setString("Health : " + to_string(m_enemyPlayer->getHealth()));
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Red);
	text.setPosition(20, 15);
	m_window.draw(text);


	if (m_userPlayer->getHealth() <= 0)
	{
		text.setString("You Lose!");
		text.setCharacterSize(60);
		text.setFillColor(sf::Color::Red);
		text.setPosition(windowSize.x / 2 - 100, windowSize.y / 2);
		m_window.draw(text);
	}

	if (m_enemyPlayer->getHealth() <= 0)
	{
		text.setString("You Win!");
		text.setCharacterSize(60);
		text.setFillColor(sf::Color::Green);
		text.setPosition(windowSize.x / 2 - 100, windowSize.y / 2);
		m_window.draw(text);
	}
}

void GameManager::cleanup()
{
	//Delete all finished animations and dead units

	m_userPlayer->m_units.erase(std::remove_if(m_userPlayer->m_units.begin(), m_userPlayer->m_units.end(), [](const shared_ptr<Unit>& unit)
		{
			return !(unit->isAlive());
		}), m_userPlayer->m_units.end());

	m_enemyPlayer->m_units.erase(std::remove_if(m_enemyPlayer->m_units.begin(), m_enemyPlayer->m_units.end(), [](const shared_ptr<Unit>& unit)
		{
			return !(unit->isAlive());
		}), m_enemyPlayer->m_units.end());

	m_explosions.erase(std::remove_if(m_explosions.begin(), m_explosions.end(), [](const shared_ptr<Explosion>& explosion)
		{
			return (explosion->isFinished());
		}), m_explosions.end());
}

void GameManager::handleCollisions()
{
	if (m_userPlayer->m_units.size() <= 0)
	{
		for (auto enemyUnit : m_enemyPlayer->m_units)
		{
			sf::FloatRect enemyUnitRect = enemyUnit->getGlobalBounds();
			bool userPlayerCollision = enemyUnitRect.intersects(m_userPlayer->getBase().getGlobalBounds());

			if (userPlayerCollision && enemyUnit->isAlive())
			{
				m_userPlayer->m_sound.play();
				m_userPlayer->setHealth(m_userPlayer->getHealth() - enemyUnit->m_strength);
				enemyUnit->setIsAlive(false);
				m_explosions.push_back(make_shared<Explosion>(enemyUnit->getPosition(), assetManager.textures.find(Textures::EXPLOSION)->second));
			}
		}
	}

	for (auto player1Unit : m_userPlayer->m_units)
	{
		sf::FloatRect player1UnitRect = player1Unit->getGlobalBounds();
		bool enemyBaseCollision = player1UnitRect.intersects(m_enemyPlayer->getBase().getGlobalBounds());

		if (enemyBaseCollision && player1Unit->isAlive())
		{
			m_enemyPlayer->m_sound.play();
			m_enemyPlayer->setHealth(m_enemyPlayer->getHealth() - player1Unit->m_strength);
			player1Unit->setIsAlive(false);
			m_explosions.push_back(make_shared<Explosion>(player1Unit->getPosition(), assetManager.textures.find(Textures::EXPLOSION)->second));
		}

		for (auto player2Unit : m_enemyPlayer->m_units)
		{
			sf::FloatRect player2UnitRect = player2Unit->getGlobalBounds();

			bool unitCollisions = player1UnitRect.intersects(player2UnitRect);
			bool userPlayerBaseCollision = player2UnitRect.intersects(m_userPlayer->getBase().getGlobalBounds());

			if (unitCollisions && player1Unit->isAlive() && player2Unit->isAlive())
			{
				m_explosions.push_back(make_shared<Explosion>(player1Unit->getPosition(), assetManager.textures.find(Textures::EXPLOSION)->second));
				battle(player1Unit, player2Unit);
			}

			if (userPlayerBaseCollision && player2Unit->isAlive())
			{
				m_userPlayer->m_sound.play();
				m_userPlayer->setHealth(m_userPlayer->getHealth() - player2Unit->m_strength);
				player2Unit->setIsAlive(false);
				m_explosions.push_back(make_shared<Explosion>(player2Unit->getPosition(), assetManager.textures.find(Textures::EXPLOSION)->second));
			}
		}
	}
}