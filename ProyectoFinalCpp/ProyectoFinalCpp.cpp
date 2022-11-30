// ProyectoFinalCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"

using namespace std;

shared_ptr<Unit> spawnUnit(int unitType, int x, int y);
bool update(Player& player1, Player& player2);
void battle(shared_ptr<Unit> unit1, shared_ptr<Unit> unit2);

int main()
{
	srand(time(NULL));

	constexpr int WINDOW_WIDTH = 800;
	constexpr int WINDOW_HEIGHT = 600;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "1917");

	GameManager game(window);
	
	game.initializeGame();

	game.runGame();

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

//bool update(Player& player1, Player& player2)
//{
//	for (auto player1Unit : player1.m_units)
//	{
//		for (auto player2Unit : player2.m_units)
//		{
//			bool collision = player1Unit->getGlobalBounds().intersects(player2Unit->getGlobalBounds());
//			if (collision && player1Unit->is_alive() && player2Unit->is_alive())
//			{
//				battle(player1Unit, player2Unit);
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//void battle(shared_ptr<Unit> unit1, shared_ptr<Unit> unit2)
//{
//	int attacker = (rand() % 2) + 1;
//	cout << "Battle" << endl;
//	cout << "U1: " << unit1->m_strength << " U2: " << unit2->m_strength << endl;
//
//	if (attacker == 1)
//	{
//		unit1->attack(unit2);
//		if (unit2->is_alive())
//			unit2->attack(unit1);
//	}
//	else
//	{
//		unit2->attack(unit1);
//		if (unit1->is_alive())
//			unit1->attack(unit2);
//	}
//
//	cout << "U1: " << unit1->m_strength << " U2: " << unit2->m_strength << endl;
//}