#include "Apple.h"

namespace ApplesGame
{
	void UpdateApple(Apple& apple, sf::Texture& texture, sf::Sprite& sprite, float screenWidth, float screenHeigth, float size)
	{
		apple.position = GetRandomPosition2D(screenWidth, screenHeigth);
		UpdateSprite(apple, texture, sprite, size);
		sprite.setPosition(GetVector2fFrom2D(apple.position));
		SetAppleEatenStatus(apple, false);
	}

	void SetAppleEatenStatus(Apple& apple, bool status)
	{
		apple.isEaten = status;

		if (status)
			apple.position = Position2D(-100, -100);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
			return;

		window.draw(apple.sprite);
	}
}