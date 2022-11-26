#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
	Button(sf::Vector2f position, sf::Color color);
	~Button();

	void update(sf::Event& e, sf::RenderWindow& window);
	void update();
	bool getState() { return m_state; }
	void setState(bool state) { m_state = state; }
	bool buttonClicked(sf::Event& e, sf::RenderWindow& window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_state;
	sf::Color m_colorNormal;
	sf::Color m_colorClicked;
	sf::Vector2f m_position;
	sf::RectangleShape m_button;
	static const sf::Vector2f m_size;
};

