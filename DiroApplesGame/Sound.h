#pragma once
#include <SFML/Audio.hpp>
#include "Resources.h"

namespace ApplesGame
{
	struct Sound
	{
		sf::Sound eatSound;
		sf::Sound dieSound;
	};

	void InitializeSound(Sound& sound, Resources& resources);
	void PlaySound(sf::Sound sound);
}