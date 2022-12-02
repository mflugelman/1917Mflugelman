#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow& window)
	:m_window(window)
{
	m_window.setFramerateLimit(30);

	m_clock = sf::Clock();
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile("../assets/background.png"))
	{
		std::cout << "Could not load from file" << std::endl;
	}

	m_background = sf::Sprite(*m_texture);
	m_font = new sf::Font;

	if (!m_font->loadFromFile("../assets/digital-7.ttf"))
	{
		// error...
	}
}


GameManager::~GameManager()
{
	delete m_texture;
	delete m_font;
}

void GameManager::initializeGame()
{
	//Create buttons and UI
	sf::Vector2u windowSize = m_window.getSize();

	Button button(sf::Vector2f(windowSize.x - 30, windowSize.y - 100), sf::Color::Blue, UnitType::INFANTRY);
	Button button2(sf::Vector2f(windowSize.x - 90, windowSize.y - 100), sf::Color::Blue, UnitType::TANK);
	Button button3(sf::Vector2f(windowSize.x - 150, windowSize.y - 100), sf::Color::Blue, UnitType::PLANE);

	m_buttons.addButton(button3);
	m_buttons.addButton(button2);
	m_buttons.addButton(button);

	//Create players
	m_userPlayer = std::make_shared<Player>();
	m_userPlayer->setBase(windowSize.x, c_baseSize, 0, windowSize.y-c_baseSize);

	m_enemyPlayer = std::make_shared<Player>();
	m_enemyPlayer->setBase(windowSize.x, c_baseSize, 0, 0);
}

void GameManager::runGame()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();


			if (event.type == sf::Event::MouseButtonPressed && !m_buttons.anyButtonPressed(event , m_window))
			{
				sf::Vector2i position = sf::Mouse::getPosition(m_window);
				int selectedUnit = m_buttons.getSelected();
				
				auto unit = spawnUnit(selectedUnit, position.x, 600, true);

				if (unit != nullptr && m_userPlayer->getMoney() >= unit->getCost())
				{
					m_userPlayer->addUnit(unit);
					m_userPlayer->addMoney(-unit->getCost());
				}

				enemyAI();
			}
		}

		if (m_clock.getElapsedTime().asSeconds() > 1)
		{
			enemyAI();
			m_clock.restart();
		}

		m_buttons.update(event, m_window);
		update();
		m_window.clear();
		m_window.draw(m_background);
		m_window.draw(m_userPlayer->getBase());
		drawUnits(m_userPlayer);
		m_window.draw(m_enemyPlayer->getBase());
		drawUnits(m_enemyPlayer);
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
		if(unit->isAlive())
			m_window.draw(*unit);
	}
}

shared_ptr<Unit> GameManager::spawnUnit(int unitType, int x, int y, bool isUserPlayer)
{
	switch (unitType)
	{
	case UnitType::TANK:
	{
		shared_ptr<Tank> tank = make_shared<Tank>(isUserPlayer);
		tank->setPosition(x, y);
		return tank;
		break;
	}
	case UnitType::INFANTRY:
	{
		shared_ptr<Infantry> infantry = make_shared<Infantry>(isUserPlayer);
		infantry->setPosition(x, y);
		return infantry;
		break;
	}
	case UnitType::PLANE:
	{
		shared_ptr<Plane> plane = make_shared<Plane>(isUserPlayer);
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
		if(!explosion->isFinished())
			explosion->animate();
	}

	m_userPlayer->addMoney(2);
	m_enemyPlayer->addMoney(2);

	for (auto player1Unit : m_userPlayer->m_units)
	{
		for (auto player2Unit : m_enemyPlayer->m_units)
		{
			bool collision = player1Unit->getGlobalBounds().intersects(player2Unit->getGlobalBounds());
			if (collision && player1Unit->isAlive() && player2Unit->isAlive())
			{
				shared_ptr<Explosion> explosion = make_shared<Explosion>();
				
				explosion->setPosition(player1Unit->getPosition());

				m_explosions.push_back(explosion);
				battle(player1Unit, player2Unit);
			}
		}
	}
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
	
	int position = rand() % (m_window.getSize().x +1);

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

	if (attacker == 1)
	{
		unit1->attack(unit2);
		if (unit2->isAlive())
			unit2->attack(unit1);
	}
	else
	{
		unit2->attack(unit1);
		if (unit1->isAlive())
			unit1->attack(unit2);
	}

	cout << "U1: " << unit1->m_strength << " U2: " << unit2->m_strength << endl;
}

void GameManager::drawTexts()
{
	sf::Text text;

	sf::Vector2u windowSize = m_window.getSize();

	text.setFont(*m_font);
	text.setString("$ : " + to_string(m_userPlayer->getMoney()));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setPosition(windowSize.x-175, windowSize.y-160);
	m_window.draw(text);
}