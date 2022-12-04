#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Button : public sf::Drawable
{
public:
	Button(sf::Vector2f position, sf::Color color, int value = 0, shared_ptr<sf::Texture> imageTexture = nullptr, shared_ptr<sf::Font> = nullptr);
	~Button();

	void update(sf::Event& e, sf::RenderWindow& window);
	void update();
	bool getState() { return m_state; }
	void setState(bool state) { m_state = state; }
	bool buttonClicked(sf::Event& e, sf::RenderWindow& window);
	int getValue() { return m_value; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setText(string text);
	void setCharacterSize(int size);
	void setFillColor(sf::Color color);

private:

	bool m_state;
	static const sf::Vector2f m_size;
	sf::Color m_colorNormal;
	sf::Color m_colorClicked;
	sf::Vector2f m_position;
	sf::RectangleShape m_button;
	sf::Sprite m_sprite;
	sf::Text m_text;
	int m_value;
};

