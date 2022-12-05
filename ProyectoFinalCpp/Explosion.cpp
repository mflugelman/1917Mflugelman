
#include "Explosion.h"

const std::string Explosion::s_spriteFile = "../assets/explosion.png";
const int Explosion::s_spriteSize = 64;

Explosion::Explosion(sf::Vector2f position, shared_ptr<sf::Texture> texture)
{
	m_isFinished = false;

	m_spriteRectangle = sf::IntRect(0, 0, 64, 64);
	m_isFinished = false;

	setTexture(*texture);
	setTextureRect(m_spriteRectangle);
	setPosition(position);
}

Explosion::~Explosion()
{
}

void Explosion::animate() 
{
	if (m_spriteRectangle.left == s_spriteSize * 3 && m_spriteRectangle.top == 0)
	{
		m_spriteRectangle.left = 0;
		m_spriteRectangle.top = s_spriteSize;
	}
	else if (m_spriteRectangle.left == s_spriteSize * 3 && m_spriteRectangle.top == s_spriteSize*2)
	{
		m_spriteRectangle.left = 0;
		m_spriteRectangle.top = s_spriteSize*2;
	}
	else if (m_spriteRectangle.left == s_spriteSize * 3 && m_spriteRectangle.top == s_spriteSize*3)
	{
		m_spriteRectangle.left = 0;
		m_spriteRectangle.top = s_spriteSize*3;
	}
	else if (m_spriteRectangle.left >= s_spriteSize * 3)
	{
		m_isFinished = true;
	}
		m_spriteRectangle.left += s_spriteSize;

	setTextureRect(m_spriteRectangle);
}

bool Explosion::isFinished()
{
	return m_isFinished;
}