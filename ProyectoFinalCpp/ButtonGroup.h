
#include "Button.h"
using namespace std;

class ButtonGroup : public sf::Drawable
{
public:
	ButtonGroup();
	~ButtonGroup();

	void addButton(const Button& button);
	bool update(sf::Event& e, sf::RenderWindow& window);
	int getSelected();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	vector<Button> m_buttons;
	static int s_clickedButton;
};

