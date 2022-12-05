#include "Player.h"

const std::string Player::s_baseTexture = "../assets/sandbags.png";

Player::Player(shared_ptr<sf::SoundBuffer> sound)
{
	m_money = 2000;
	m_health = 1000;

	m_sound.setBuffer(*sound);
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(s_baseTexture))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}
	
	m_texture->setRepeated(true);
}

Player::~Player()
{
	delete m_texture;
}

int Player::getHealth() { return m_health; }

void Player::setHealth(int health) { m_health = health; }

int Player::getMoney() { return m_money; }

void Player::addMoney(int money) { m_money += money; }

void Player::addUnit(shared_ptr<Unit> unit) 
{
	m_units.push_back(unit);
}

void Player::setBase(int width, int height, int posX, int posY)
{
	sf::Vector2f dimensions(width, height);

	m_base = sf::RectangleShape(dimensions);
	m_base.setPosition(posX, posY);
	m_base.setTexture(m_texture, true);
	m_base.setTextureRect(sf::IntRect(0, 0, width, height));
}

sf::RectangleShape Player::getBase() { return m_base; }