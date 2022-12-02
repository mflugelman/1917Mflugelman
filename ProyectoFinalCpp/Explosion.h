#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class Explosion : public sf::Sprite
{
public:
	Explosion();
	~Explosion();
	void animate();
	bool isFinished();
private:
	static const std::string s_spriteFile;
	static const int s_spriteSize;
	sf::Texture* m_texture;
	sf::IntRect m_spriteRectangle;
	bool m_isFinished;
};