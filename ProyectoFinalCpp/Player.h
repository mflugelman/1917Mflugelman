#pragma once

#include <vector>
#include "Unit.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();

	int getHealth();
	void setHealth(int health);

	int getMoney();
	void addMoney(int money);

	void addUnit(shared_ptr<Unit> unit);

	void setBase(int width, int height, int posX, int posY);
	sf::RectangleShape getBase();
	vector<shared_ptr<Unit>> m_units;

private:
	int m_money;
	int m_health;
	static const string s_baseTexture;

	sf::RectangleShape m_base;
	sf::Texture* m_texture;
};