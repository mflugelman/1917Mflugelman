#include "Button.h"
#include <iostream>

const sf::Vector2f Button::m_size = sf::Vector2f(50, 50);

Button::Button(sf::Vector2f position, sf::Color color, int value)
{
	m_position = position;
	m_colorNormal = color;
	m_colorClicked = sf::Color::Red;
	m_state = false;
	m_value = value;

	m_button = sf::RectangleShape(m_size);
	m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
	m_button.setPosition(m_position);
	m_button.setFillColor(color);
	m_button.setOutlineColor(m_colorClicked);
}

Button::~Button() {}

void Button::update(sf::Event& e, sf::RenderWindow& window)
{
	if (buttonClicked(e, window))
		m_state = true;
	else
		m_state = false;

	update();
}

void Button::update()
{
	if (m_state)
		m_button.setOutlineThickness(2.0f);
	else
		m_button.setOutlineThickness(0);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_button);
}

bool Button::buttonClicked(sf::Event& e, sf::RenderWindow& window)
{
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);

	bool mouseInButton = m_mousePosition.x >= m_button.getPosition().x - m_button.getGlobalBounds().width / 2
		&& m_mousePosition.x <= m_button.getPosition().x + m_button.getGlobalBounds().width / 2
		&& m_mousePosition.y >= m_button.getPosition().y - m_button.getGlobalBounds().height / 2
		&& m_mousePosition.y <= m_button.getPosition().y + m_button.getGlobalBounds().height / 2;

	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (mouseInButton)
			return true;
		else
			return false;
	}

	return false;
}