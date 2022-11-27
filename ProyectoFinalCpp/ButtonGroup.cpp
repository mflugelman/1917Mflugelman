#include "ButtonGroup.h"

int ButtonGroup::s_clickedButton = -1;

ButtonGroup::ButtonGroup()
{
}

ButtonGroup::~ButtonGroup()
{
}

void ButtonGroup::addButton(const Button& button)
{
	m_buttons.push_back(button);
}

void ButtonGroup::update(sf::Event& e, sf::RenderWindow& window) 
{
	for (int i = 0; i < m_buttons.size() ; i++)
	{
		bool isClicked = m_buttons[i].buttonClicked(e, window);

		if (isClicked)
		{
			m_buttons[i].setState(true);
			m_buttons[i].update();
			s_clickedButton = i;
		}
		else if (!isClicked && i != s_clickedButton)
		{
			m_buttons[i].setState(false);
			m_buttons[i].update();
		}
	}
}

void ButtonGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Button button : m_buttons)
	{
		target.draw(button);
	}
}