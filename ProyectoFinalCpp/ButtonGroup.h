
#include "Button.h"
using namespace std;

class ButtonGroup : public sf::Drawable
{
public:
	ButtonGroup();
	~ButtonGroup();

	void addButton(const Button& button);
	void update(sf::Event& e, sf::RenderWindow& window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	vector<Button> m_buttons;
	static int s_clickedButton;
};

