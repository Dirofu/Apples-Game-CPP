#include "Player.h"

namespace ApplesGame
{
	void HandlePlayerInput(Player& player)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.direction = Direction::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.direction = Direction::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.direction = Direction::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.direction = Direction::Down;
		}
	}

	void ChangePlayerSpeedByInputDirection(Player& player, float deltaTime)
	{
		switch (player.direction)
		{
		case Direction::Right:
			player.position.x += player.speed * deltaTime;
			break;
		case Direction::Up:
			player.position.y -= player.speed * deltaTime;
			break;
		case Direction::Left:
			player.position.x -= player.speed * deltaTime;
			break;
		case Direction::Down:
			player.position.y += player.speed * deltaTime;
			break;
		}
	}

	void ResetPlayer(Player& player, sf::Texture& texture, float speed, Vector2D startPosition, sf::Vector2f playerSize)
	{
		player.position = startPosition;
		player.speed = speed;
		player.direction = Direction::Right;
		player.isAlive = true;

		UpdateSprite(player, texture, player.sprite, PLAYER_SIZE);
	}

	void SetPlayerDeadStatus(Player& player)
	{
		player.isAlive = false;
	}

	void AddAccelerationToPlayer(Player& player, float acceleration)
	{
		player.speed += acceleration;
	}
	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);

		switch (player.direction)
		{
			case Direction::Up:
			{
				player.sprite.setScale(player.scale);
				player.sprite.setRotation(270.f);
				break;
			}
			case Direction::Right:
			{
				player.sprite.setScale(player.scale);
				player.sprite.setRotation(0.f);
				break;
			}
			case Direction::Down:
			{
				player.sprite.setScale(player.scale);
				player.sprite.setRotation(90.f);
				break;
			}
			case Direction::Left:
			{
				player.sprite.setScale(-player.scale.x, player.scale.y);
				player.sprite.setRotation(0.f);
				break;
			}
		}

		window.draw(player.sprite);
	}
}