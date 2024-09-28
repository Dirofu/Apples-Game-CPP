#pragma once
#include "Constantes.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	struct Player : GameObject
	{
		sf::String name = "PLAYER";
		float speed = INITIAL_SPEED;
		Direction direction = Direction::Right;
		bool isAlive = true;
	};

	void HandlePlayerInput(Player& player);
	void ChangePlayerSpeedByInputDirection(Player& player, float deltaTime);
	void ResetPlayer(Player& player, sf::Texture& texture, float speed, Vector2D startPosition, sf::Vector2f playerSize);
	void SetPlayerDeadStatus(Player& player);
	void AddAccelerationToPlayer(Player& player, float acceleration);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
}