#include "Rock.h"

namespace ApplesGame
{
	void UpdateRock(Rock& rock, sf::Texture& texture, sf::Sprite& sprite, float screenWidth, float screenHeigth, float size)
	{
		rock.position = GetRandomPosition2D(screenWidth, screenHeigth);
		UpdateSprite(rock, texture, sprite, size);
		sprite.setPosition(GetVector2fFrom2D(rock.position));
	}
	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		window.draw(rock.sprite);
	}
}