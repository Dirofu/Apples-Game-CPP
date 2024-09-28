#include "Resources.h"
#include "Constantes.h"
#include <cassert>

namespace ApplesGame
{
	void InitializeGameResources(Resources& resources)
	{
		assert(resources.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(resources.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(resources.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(resources.eatSound.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(resources.dieSound.loadFromFile(RESOURCES_PATH + "Death.wav"));
		assert(resources.font.loadFromFile(RESOURCES_PATH + "Fonts\\Roboto-Medium.ttf"));
	}
}