#include "Sound.h"

namespace ApplesGame
{
	void InitializeSound(Sound& sound, Resources& resources)
	{
		sound.eatSound.setBuffer(resources.eatSound);
		sound.dieSound.setBuffer(resources.dieSound);
	}

	void PlaySound(sf::Sound sound)
	{
		sound.play();
	}
}