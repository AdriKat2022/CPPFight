#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameRun.h"
#include "Configs.h"
#include "Menu.h"


// Forward declarations (avoid the early header inclusion)
class GameRun;
class IDrawable;
class Button;
struct EnemyData;


enum class GameState {
	MainMenu,
	RulesMenu,
	PreRunScreen,
	InRun,
	PauseMenu
};


class Game {

public:
	Game();

	// Run the game in general (window, events, etc) functions finishes when the game is closed
	void RunGame();
	void ToMainMenu();

private:
	// Initializing functions (called once)
	void LoadEnemiesData();
	void GenerateMenus(); // Generates the menus (main menu, rules menu, pause menu, etc)
	
	// Game loop functions
	void ManageWindowEvents(); // Manages the window events (close, resize, etc)
	void UpdateGame(float deltaTime); // Manages the menus (main menu, pause menu, retry menu etc) (intern so no need to separate update and render) (i think)
	void UpdateGameRun(float deltaTime); // Runs the game loop (the "RUN" with X encounters)

	// Button calls
	void PrepareNewRun();
	void BeginNewRun();
	void ShowRules();
	void QuitRequest();

	// Utils functions
	std::unique_ptr<GameRun> NewRun(); // Creates a new game run

	// Variables


	sf::RenderWindow m_window = { sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE };
	std::unique_ptr<GameRun> m_currentRun;
	GameState m_currentState = GameState::MainMenu;

	std::unique_ptr<std::vector<EnemyData>> m_enemyDataBank; // Contains the data of all the possible enemies

	sf::Music m_mainMenuMusic;

	// Menus
	Menu m_mainMenu;
	Menu m_preRunMenu; // Unused for now
	Menu m_rulesMenu;
	Menu m_pauseMenu; // Unused for now

};


