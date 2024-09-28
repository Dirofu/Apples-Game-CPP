#pragma once
#include "Resources.h"
#include "Player.h"
#include "Rock.h"
#include "Apple.h"
#include "UI.h"
#include "Sound.h"
#include "GameMode.h"
#include "GameState.h"
#include "Leaderboard.h"

namespace ApplesGame
{
	struct Game
	{
		Player player;
		Apple apples[APPLES_COUNT];
		Rock rocks[ROCKS_COUNT];

		sf::Sprite gameOverPanel;
		
		Resources resources;
		UI ui;
		Sound sound;
		GameMode mode;
		GameState currentGameState;
		Leaderboard leaderboard;

		int countEatenApples = 0;
		int applesOnScreen = 0;
		int rocksOnScreen = 0;
	};

	void InitializeGame(Game& game);

	void InitGameOverPanel(sf::Sprite& gameOverPanel);

	void UpdateGameLoop(Game& game, float deltaTime, sf::RenderWindow& window);

	void SetGameRule(Game& game, int index, bool state);

	void SetGameRule(Game& game, int index);

	void EatApple(Game& game, Apple& apple);
	
	void HandleMenuInput(Game& game, float deltaTime);

	void HandleEndGameInput(Game& game);

	void HandleLeaderboardInput(Game& game);

	void HandleExitDialogInput(Game& game, sf::RenderWindow& window);

	void EndGame(Game& game);

	void RestartGame(Game& game);

	void ReturnToMenu(Game& game);

	void OpenLeaderboard(Game& game);

	void OpenExitDialog(Game& game);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void DeinitializeGame(Game& game);

	void PlaceRocksOnScreen(Game& game);

	void PlaceApplesOnScreen(Game& game);
}