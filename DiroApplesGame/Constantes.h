#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	enum class Direction
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGTH = 1080;
	const float PLAYER_SIZE = 50.f;
	const float APPLE_SIZE = 30.f;
	const int APPLES_COUNT = 20;
	const float ROCK_SIZE = 20.f;
	const int ROCKS_COUNT = 30;
	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 100.f;
}