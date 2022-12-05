#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Explosion : public sf::Sprite
{
public:
	Explosion(sf::Vector2f position, shared_ptr<sf::Texture> texture);
	~Explosion();
	void animate();
	bool isFinished();
private:
	static const std::string s_spriteFile;
	static const int s_spriteSize;
	sf::IntRect m_spriteRectangle;
	bool m_isFinished;
};