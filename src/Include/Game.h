#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameRun.h"
#include "Configs.h"
#include "Menu.h"
#include "Context.h"


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


class Game : public Context {

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



	static std::unique_ptr<GameRun> NewRun(sf::RenderWindow& renderWindow);


	// Variables

	std::unique_ptr<GameRun> m_currentRun;

	sf::RenderWindow m_window = { sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE };
	GameState m_currentState = GameState::MainMenu;

	// Constants
	std::unique_ptr<std::vector<EnemyData>> m_enemyDataBank;

	// Menus
	Menu m_mainMenu;
	Menu m_pauseMenu;

};


