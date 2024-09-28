#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	struct Resources
	{
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::SoundBuffer eatSound;
		sf::SoundBuffer dieSound;
		sf::Font font;
	};

	void InitializeGameResources(Resources& resources);
}