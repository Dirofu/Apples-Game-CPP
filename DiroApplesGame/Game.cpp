#include "Game.h"
#include "Resources.h"
#include <cassert>

namespace ApplesGame
{
	void InitializeGame(Game& game)
	{
		InitializeGameResources(game.resources);
		InitializeSound(game.sound, game.resources);
		InitializeGameMode(game.mode);
		InitializeUI(game.ui, game.resources.font, SCREEN_WIDTH, SCREEN_HEIGTH);
		InitializeLeaderboard(game.leaderboard);
		InitGameOverPanel(game.gameOverPanel);
		SetGameRule(game, GAMERULE_INFINITYAPPLES, false);
		SetGameRule(game, GAMERULE_ACCELERATION, false);
		ReturnToMenu(game);
	}
	
	void InitGameOverPanel(sf::Sprite& gameOverPanel)
	{
		sf::Texture gameOverTexture = sf::Texture{};
		gameOverTexture.create(SCREEN_WIDTH, SCREEN_HEIGTH);
		gameOverPanel = sf::Sprite{};
		gameOverPanel.setTexture(gameOverTexture);
		gameOverPanel.setColor(sf::Color::Black);
	}

	void UpdateGameLoop(Game& game, float deltaTime, sf::RenderWindow& window)
	{
		switch (game.currentGameState)
		{
			case GameState::MainMenu:
				HandleMenuInput(game, deltaTime);
				return;

			case GameState::Leaderboard:
				HandleLeaderboardInput(game);
				return;

			case GameState::Game:
				HandlePlayerInput(game.player);
				break;

			case GameState::GameOverMenu:
				HandleEndGameInput(game);
				return;

			case GameState::ExitDialog:
				HandleExitDialogInput(game, window);
				return;
		}

		UpdateUI(game.ui, game.countEatenApples);
		ChangePlayerSpeedByInputDirection(game.player, deltaTime);

		if (CheckCollisionWithWindowBoarder(game.player.position, PLAYER_SIZE, SCREEN_WIDTH, SCREEN_HEIGTH) == true)
			EndGame(game);

		for (Apple& apple : game.apples)
		{
			if (CalculateDistance(game.player.position, apple.position) < PLAYER_SIZE)
				if (CheckCircleCollisionBetweenObjects(game.player.position, PLAYER_SIZE / 2, apple.position, APPLE_SIZE / 2) == true)
					EatApple(game, apple);
		}

		for (Rock& rock : game.rocks)
		{
			if (CalculateDistance(game.player.position, rock.position) < PLAYER_SIZE)
				if (CheckRectangleCollisionBetweenObjects(game.player.position, PLAYER_SIZE, rock.position, ROCK_SIZE) == true)
					EndGame(game);
		}
	}
	
	void SetGameRule(Game& game, int index, bool state)
	{
		SetGameRuleStateText(game.ui, index, state);
	}

	void SetGameRule(Game& game, int index)
	{
		bool state = ChangeGameRuleStateByIndex(game.mode, index);
		SetGameRuleStateText(game.ui, index, state);
	}

	void EatApple(Game& game, Apple& apple)
	{
		game.countEatenApples++;
		PlaySound(game.sound.eatSound);

		if (CheckGameRuleActive(game.mode.mask, GAMERULE_ACCELERATION))
			AddAccelerationToPlayer(game.player, ACCELERATION);

		if (CheckGameRuleActive(game.mode.mask, GAMERULE_INFINITYAPPLES))
		{
			UpdateApple(apple, game.resources.appleTexture, apple.sprite, SCREEN_WIDTH, SCREEN_HEIGTH, APPLE_SIZE);
		}
		else
		{
			SetAppleEatenStatus(apple, true);

			if (game.countEatenApples == game.applesOnScreen)
				EndGame(game);
		}
	}

	void HandleMenuInput(Game& game, float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			RestartGame(game);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			OpenLeaderboard(game);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			OpenExitDialog(game);

		if (game.mode.modeChangeTimer > 0.f)
		{
			game.mode.modeChangeTimer -= deltaTime;
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			game.mode.modeChangeTimer = game.mode.maxChangeTime;
			SetGameRule(game, GAMERULE_INFINITYAPPLES);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			game.mode.modeChangeTimer = game.mode.maxChangeTime;
			SetGameRule(game, GAMERULE_ACCELERATION);
		}
	}

	void HandleEndGameInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			ReturnToMenu(game);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			RestartGame(game);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			OpenLeaderboard(game);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			OpenExitDialog(game);
	}

	void HandleLeaderboardInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			ReturnToMenu(game);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			OpenExitDialog(game);
	}

	void HandleExitDialogInput(Game& game, sf::RenderWindow& window)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			ReturnToMenu(game);
	}

	void EndGame(Game& game)
	{
		UpdatePlayerScoreInLeaderboard(game.leaderboard, game.player.name, game.countEatenApples);
		game.currentGameState = GameState::GameOverMenu;
		SetPlayerDeadStatus(game.player);
		PlaySound(game.sound.dieSound);
	}

	void RestartGame(Game& game)
	{
		game.currentGameState = GameState::Game;
		game.countEatenApples = 0;

		ResetPlayer(game.player, game.resources.playerTexture, INITIAL_SPEED, Vector2D{ SCREEN_WIDTH / 2, SCREEN_HEIGTH / 2 }, sf::Vector2f{ PLAYER_SIZE, PLAYER_SIZE });
		PlaceRocksOnScreen(game);
		PlaceApplesOnScreen(game);
	}

	void ReturnToMenu(Game& game)
	{
		RestartGame(game);
		game.currentGameState = GameState::MainMenu;
	}

	void OpenLeaderboard(Game& game)
	{
		game.currentGameState = GameState::Leaderboard;

		sf::String text = GetLeaderboardText(game.ui.leaderboardText, game.ui.leaderboardEndText, game.leaderboard);
		SetText(game.ui.leaderboard, text);
	}

	void OpenExitDialog(Game& game)
	{
		game.currentGameState = GameState::ExitDialog;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		switch (game.currentGameState)
		{
			case GameState::Game:
				for (Apple apple : game.apples)
					DrawApple(apple, window);

				for (Rock rock : game.rocks)
					DrawRock(rock, window);

				DrawPlayer(game.player, window);
				break;

			case GameState::GameOverMenu:
				window.draw(game.gameOverPanel);
				break;
		}

		DrawUI(game.ui, window, game.player.isAlive, game.currentGameState);
	}

	void DeinitializeGame(Game& game)
	{

	}

	void PlaceRocksOnScreen(Game& game)
	{
		game.rocksOnScreen = rand() % (ROCKS_COUNT - 1);

		for (int i = 0; i < game.rocksOnScreen; i++)
			UpdateRock(game.rocks[i], game.resources.rockTexture, game.rocks[i].sprite, SCREEN_WIDTH, SCREEN_HEIGTH, ROCK_SIZE);
	}

	void PlaceApplesOnScreen(Game& game)
	{
		game.applesOnScreen = rand() % (APPLES_COUNT - 1);

		for (int i = 0; i < game.applesOnScreen; i++)
			UpdateApple(game.apples[i], game.resources.appleTexture, game.apples[i].sprite, SCREEN_WIDTH, SCREEN_HEIGTH, APPLE_SIZE);
	}
}