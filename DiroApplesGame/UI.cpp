#include "UI.h"

namespace ApplesGame
{
	void InitializeUI(UI& ui, const sf::Font& font, float width, float heigth)
	{
		SetUpText(ui.gameTip, font, 25, sf::Color::White, ui.gameTipText, { 0.f, 0.f }, { 0.f, 0.f });
		SetUpText(ui.applesCounter, font, 25, sf::Color::White, ui.applesCounterText, { 0.f, 30.f }, { 0.f, 0.f });
		SetUpText(ui.gameOver, font, 50, sf::Color::Red, ui.gameOverText, { width / 2, heigth / 2 }, { .5f, .5f });
		SetUpText(ui.startGame, font, 100, sf::Color::White, ui.startGameText, { width / 2, heigth / 2 }, { .5f, .5f });
		SetUpText(ui.gameRuleInfinityApples, font, 25, sf::Color::White, ui.gameRuleInfinityApplesText, { 0.f, 0.f }, { 0.f, 0.f });
		SetUpText(ui.gameRuleAcceleration, font, 25, sf::Color::White, ui.gameRuleAccelerationText, { 0.f, 30.f }, { 0.f, 0.f });
		SetUpText(ui.leaderboard, font, 75, sf::Color::White, ui.leaderboardText, { width / 2, 0.f }, { .5f, 0.f });
		SetUpText(ui.exitDialog, font, 50, sf::Color::White, ui.exitDialogText, { width / 2, heigth / 2 }, { .5f, .5f });
	}

	void UpdateUI(UI& ui, int eatenApples)
	{
		SetText(ui.applesCounter, ui.applesCounterText + std::to_string(eatenApples));
	}

	void SetGameRuleStateText(UI& ui, int index, bool state)
	{
		sf::String symbol = state == true ? "+" : "-";

		switch (index)
		{
			case 1:
				SetText(ui.gameRuleInfinityApples, ui.gameRuleInfinityApplesText + symbol);
				break;

			case 2:
				SetText(ui.gameRuleAcceleration, ui.gameRuleAccelerationText + symbol);
				break;
		}
	}

	void SetText(sf::Text& text, sf::String string)
	{
		text.setString(string);
	}

	void SetUpText(sf::Text& obj, const sf::Font& font, int characterSize, const sf::Color color, sf::String& text, sf::Vector2f position, Vector2D origin)
	{
		obj.setFont(font);
		obj.setCharacterSize(characterSize);
		obj.setFillColor(color);
		obj.setString(text);
		obj.setOrigin(GetTextOrigin(obj, origin));
		obj.setPosition(position);
	}

	void DrawUI(UI& ui, sf::RenderWindow& window, bool isPlayerAlive, GameState gameState)
	{
		switch (gameState)
		{
			case GameState::MainMenu:
				window.draw(ui.startGame);
				window.draw(ui.gameRuleInfinityApples);
				window.draw(ui.gameRuleAcceleration);
				break;
			
			case GameState::Game:
				window.draw(ui.gameTip);
				window.draw(ui.applesCounter);
				break;

			case GameState::GameOverMenu:
				window.draw(ui.gameOver);
				break;

			case GameState::Leaderboard:
				window.draw(ui.leaderboard);
				break;

			case GameState::ExitDialog:
				window.draw(ui.exitDialog);
				break;
		}
	}
}