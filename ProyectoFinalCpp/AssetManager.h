#pragma once

#include <iterator>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AssetsEnums.h"
#include <SFML/Audio.hpp>

using namespace std;

class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	map<Textures, shared_ptr<sf::Texture>> textures;
	map<Audio, shared_ptr<sf::SoundBuffer>> sounds;
	shared_ptr <sf::Font> font;

private:
	void loadTextures();
	void loadSounds();
	void loadTexture(string fileName, Textures textureEnum);
	void loadSound(string fileName, Audio audioEnum);
};
