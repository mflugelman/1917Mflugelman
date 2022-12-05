#include "AssetManager.h"


AssetManager::AssetManager()
{
	font = make_shared<sf::Font>();

	//LoadFonts
	if (!font->loadFromFile("../assets/digital-7.ttf"))
	{
		// error...
	}

	loadTextures();
	loadSounds();
}

AssetManager::~AssetManager()
{
}

void AssetManager::loadTextures()
{
	//load Textures for Infantry

	loadTexture("../assets/infantrybutton.png", Textures::INFANTRYBTN);
	loadTexture("../assets/infantrysprite.png", Textures::INFANTRY);
	loadTexture("../assets/tankback.png", Textures::TANKUSER);
	loadTexture("../assets/tankFront.png", Textures::TANKENEMY);
	loadTexture("../assets/planeBack.png", Textures::PLANEUSER);
	loadTexture("../assets/planeFront.png", Textures::PLANEENEMY);
	loadTexture("../assets/background.png", Textures::BACKGROUND);
	loadTexture("../assets/sandbags.png", Textures::BASE);
	loadTexture("../assets/explosion.png", Textures::EXPLOSION);
}


void AssetManager::loadTexture(string fileName, Textures textureEnum)
{
	shared_ptr<sf::Texture> texture = make_shared<sf::Texture>();
	if (!texture->loadFromFile(fileName))
	{
		std::cout << "Could not load from file" << fileName << std::endl;
		return;
	}
	textures.insert(pair<Textures, shared_ptr<sf::Texture>>(textureEnum, texture));
}

void AssetManager::loadSounds() 
{
	loadSound("../assets/infantrySound.wav", Audio::INFANTRY);
	loadSound("../assets/DeathFlash.flac", Audio::TANK);
	loadSound("../assets/explosionplane.wav", Audio::PLANE);
	loadSound("../assets/cannon_hit.ogg", Audio::BASEHIT);
	loadSound("../assets/MachinePowerOff.ogg", Audio::SPAWN);
}

void AssetManager::loadSound(string fileName, Audio audioEnum) 
{
	shared_ptr<sf::SoundBuffer> sound = make_shared<sf::SoundBuffer>();
	sound->loadFromFile(fileName);
	sounds.insert(pair<Audio, shared_ptr<sf::SoundBuffer>>(audioEnum, sound));
}