// ProyectoFinalCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "Button.h"
#include "ButtonGroup.h"
#include "Infantry.h"
#include "Tank.h"
#include "Plane.h"
#include "Player.h"

using namespace std;

shared_ptr<Unit> spawnUnit(int unitType, int x, int y);

int main()
{
	srand(time(NULL));

	constexpr int WINDOW_WIDTH = 800;
	constexpr int WINDOW_HEIGHT = 600;
	constexpr int BASEHEIGHT = 70;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "1917");
	window.setFramerateLimit(30);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../assets/background.png"))
	{
		std::cout << "Could not load from file" << std::endl;
	}

	sf::Sprite background(backgroundTexture);


	//sf::Vector2f trench(WINDOW_WIDTH, 50);

	//sf::RectangleShape home_base(trench);
	//home_base.setFillColor(sf::Color::Green);
	//home_base.setPosition(0, WINDOW_HEIGHT - 50);

	//sf::RectangleShape enemy_base(trench);
	//enemy_base.setFillColor(sf::Color::Red);
	//enemy_base.setPosition(0, 0);

	Player userPlayer;
	userPlayer.setBase(WINDOW_WIDTH, BASEHEIGHT, 0, WINDOW_HEIGHT - BASEHEIGHT);

	Player enemyPlayer;
	enemyPlayer.setBase(WINDOW_WIDTH, BASEHEIGHT, 0, 0);

	Button button(sf::Vector2f(WINDOW_WIDTH - 30, WINDOW_HEIGHT - 100), sf::Color::Blue);
	Button button2(sf::Vector2f(WINDOW_WIDTH - 90, WINDOW_HEIGHT - 100), sf::Color::Blue);
	Button button3(sf::Vector2f(WINDOW_WIDTH - 150, WINDOW_HEIGHT - 100), sf::Color::Blue);

	ButtonGroup buttons;
	buttons.addButton(button3);
	buttons.addButton(button2);
	buttons.addButton(button);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				int clicked = buttons.getSelected();

				auto unit = spawnUnit(clicked, position.x, WINDOW_HEIGHT - 50);

				if (unit != nullptr)
					 userPlayer.addUnit(unit);
			}

			buttons.update(event, window);
		}

		window.clear();

		//window.draw(home_base);
		window.draw(background);
		window.draw(userPlayer.getBase());
		window.draw(enemyPlayer.getBase());
		window.draw(buttons);

		for (int i = 0; i < userPlayer.m_units.size(); i++)
		{
			window.draw(*userPlayer.m_units[i]);

			userPlayer.m_units[i]->move_y(1);
			if (!userPlayer.m_units[i]->is_alive())
			{
				userPlayer.m_units.erase(userPlayer.m_units.begin() + i);
			}
		}

		for (int i = 0; i < enemyPlayer.m_units.size(); i++)
		{
			window.draw(*enemyPlayer.m_units[i]);

			enemyPlayer.m_units[i]->move_y(1);
			if (!enemyPlayer.m_units[i]->is_alive())
			{
				enemyPlayer.m_units.erase(userPlayer.m_units.begin() + i);
			}
		}

		window.display();
	}

	return 0;
}


shared_ptr<Unit> spawnUnit(int unitType, int x, int y)
{
	switch (unitType)
	{
	case 0:
	{
		shared_ptr<Tank> tank = make_shared<Tank>();
		tank->setPosition(x, y);
		return tank;
		break;
	}
	case 1:
	{
		shared_ptr<Infantry> infantry = make_shared<Infantry>();
		infantry->setPosition(x, y);
		return infantry;
		break;
	}
	case 2:
	{
		shared_ptr<Plane> plane = make_shared<Plane>();
		plane->setPosition(x, y);
		return plane;
		break;
	}
	default:
		return nullptr;
		break;
	}
}