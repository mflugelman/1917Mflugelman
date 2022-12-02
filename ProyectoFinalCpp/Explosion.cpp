
#include "Explosion.h"

const std::string Explosion::s_spriteFile = "../assets/explosion.png";
const int Explosion::s_spriteSize = 64;

Explosion::Explosion()
{
	m_texture = new sf::Texture;

	if (!m_texture->loadFromFile(s_spriteFile))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	m_spriteRectangle = sf::IntRect(0, 0, 64, 64);
	m_isFinished = false;

	setTexture(*m_texture);
	setTextureRect(m_spriteRectangle);
}

Explosion::~Explosion()
{
	delete m_texture;
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