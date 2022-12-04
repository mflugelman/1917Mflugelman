#pragma once

#include <iterator>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	map<string, shared_ptr<sf::Texture>> textures;
	shared_ptr <sf::Font> font;
};
