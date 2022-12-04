#include "AssetManager.h"


AssetManager::AssetManager()
{
	font = make_shared<sf::Font>();

	//LoadFonts
	if (!font->loadFromFile("../assets/digital-7.ttf"))
	{
		// error...
	}

	//load sprites for Infantry
	shared_ptr<sf::Texture> infantryTexture = make_shared<sf::Texture>();
	if (!infantryTexture->loadFromFile("../assets/infantrybutton.png"))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	textures.insert(pair<string, shared_ptr<sf::Texture>>("INFANTRYBUTTON", infantryTexture));

	//load texture for Tank
	shared_ptr<sf::Texture> tankTexture = make_shared<sf::Texture>();
	if (!tankTexture->loadFromFile("../assets/tankback.png"))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	textures.insert(pair<string, shared_ptr<sf::Texture>>("TANK", tankTexture));

	//load texture for plane
	shared_ptr<sf::Texture> planeTexture = make_shared<sf::Texture>();
	if (!planeTexture->loadFromFile("../assets/planeback.png"))
	{
		std::cout << "Could not load from file" << std::endl;
		return;
	}

	textures.insert(pair<string, shared_ptr<sf::Texture>>("PLANE", planeTexture));
}

AssetManager::~AssetManager()
{
}