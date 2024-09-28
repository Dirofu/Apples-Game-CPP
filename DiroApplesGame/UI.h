#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameState.h"

namespace ApplesGame
{
	struct UI
	{
		sf::Text startGame;
		sf::Text gameTip;
		sf::Text applesCounter;
		sf::Text gameOver;
		sf::Text gameRuleInfinityApples;
		sf::Text gameRuleAcceleration;
		sf::Text leaderboard;
		sf::Text exitDialog;

		sf::String startGameText = "Press Enter to start game\nL: Leaderboard";
		sf::String gameTipText = "Arrows: change direction of player, ESC: close";
		sf::String applesCounterText = "Apples eaten: ";
		sf::String gameOverText = "Game over!\nSpace: menu\nR: restart\nL: Leaderboard";
		sf::String gameRuleInfinityApplesText = "1) Apples infinity: ";
		sf::String gameRuleAccelerationText = "2) Acceleration: ";
		sf::String leaderboardText = "Leaderboard:\n";
		sf::String leaderboardEndText = "Space: menu";
		sf::String exitDialogText = "Do you want quit?\nY/N";
	};

	void InitializeUI(UI& ui, const sf::Font& font, float width, float heigth);

	void UpdateUI(UI& ui, int eatenApples);

	void SetGameRuleStateText(UI& ui, int index, bool state);

	void SetText(sf::Text& text, sf::String string);

	void SetUpText(sf::Text& obj, const sf::Font& font, int characterSize, const sf::Color color, sf::String& text, sf::Vector2f position, Vector2D origin);

	void DrawUI(UI& ui, sf::RenderWindow& window, bool isPlayerAlive, GameState gameState);
}