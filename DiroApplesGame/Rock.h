#pragma once
#include "GameObject.h"

namespace ApplesGame
{
	struct Rock : GameObject
	{

	};

	void UpdateRock(Rock& rock, sf::Texture& texture, sf::Sprite& sprite, float screenWidth, float screenHeigth, float size);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}