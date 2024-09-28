#pragma once
#include "GameObject.h"

namespace ApplesGame
{
	struct Apple : GameObject
	{
		bool isEaten = false;
	};

	void UpdateApple(Apple& apple, sf::Texture& texture, sf::Sprite& sprite, float screenWidth, float screenHeigth, float size);

	void SetAppleEatenStatus(Apple& apple, bool status);

	void DrawApple(Apple& apple, sf::RenderWindow& window);
}