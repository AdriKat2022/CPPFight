#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameRun.h"
#include "Configs.h"


// Forward declarations (avoid the early header inclusion)
class GameRun;
class IDrawable;
class Button;
struct EnemyData;


enum class GameState {
	MainMenu,
	InRun,
	Paused
};


class Game {

public:
	Game();

	// Run the game in general (window, events, etc) functions finishes when the game is closed
	void RunGame();

private:
	// Initializing functions
	void LoadEnemiesData();
	void GenerateMenus();
	// Runs the game loop (the "RUN" with X encounters) 
	void UpdateGameRun();
	// Renders the game loop (the "RUN" with X encounters) (we need to separate the update and render functions to avoid having the game run at different speeds on different computers)
	void RenderGameRun();
	// Manages the menus (main menu, pause menu, retry menu etc) (intern so no need to separate update and render) (i think)
	void UpdateGameMenu();
	void ManageWindowEvents();

	void AddMenuButton(const std::string& spritePath, sf::Vector2f position, void (*OnClickEvent)(Game& gameContext));
	void AddDrawableToRenderList(std::shared_ptr<IDrawable> drawable);

	static std::unique_ptr<GameRun> NewRun(sf::RenderWindow& renderWindow);


	// Variables

	std::unique_ptr<GameRun> m_currentRun;

	sf::RenderWindow m_window = { sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE };
	GameState m_currentState = GameState::MainMenu;

	// Constants
	std::unique_ptr<std::vector<EnemyData>> m_enemyDataBank;

	// Menus


	// Move this to a separate class (Menu class)
	std::vector<std::shared_ptr<Button>> m_menuButtons;
	std::vector<std::shared_ptr<IDrawable>> m_menuDrawable;
};


