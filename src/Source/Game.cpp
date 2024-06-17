#include "Game.h"
#include "Clickable.h"
#include "Button.h"
#include "EnemyLoader.h"
#include <Menu.h>


Game::Game()
{
	LoadEnemiesData();
	GenerateMenus();
}

void Game::RunGame()
{
	// To measure deltatime
	sf::Clock clock;

	while (m_window.isOpen()) {

		ManageWindowEvents();

		// Get the delta time thanks to the clock
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();

		UpdateGame(deltaTime);

		m_window.display();
	}

}

void Game::LoadEnemiesData()
{
	EnemyLoader loader;
	loader.ReadFromFile(FilePaths::ENEMY_DATA_LIST, m_enemyDataBank);
}

void Game::GenerateMenus()
{
	//définition et affichage des boutons du menu
	m_mainMenu.AddSprite(FilePaths::SP_SH_MENU_BG, sf::Vector2f{ 0,0 }, sf::Vector2i{ 1, 1 }, false);
	m_mainMenu.AddButton(FilePaths::SP_SH_PLAY_BTN, sf::Vector2f(400, 100), [this]() { this->BeginNewRun(); });
	m_mainMenu.AddButton(FilePaths::SP_SH_RULES_BTN, sf::Vector2f(400, 300), [this]() { this->ShowRules();  });
	m_mainMenu.AddButton(FilePaths::SP_SH_QUIT_BTN, sf::Vector2f(400, 500), [this]() { this->QuitRequest(); });
}

void Game::UpdateGame(float deltaTime)
{
	switch (m_currentState)
	{
		using enum GameState;

	case MainMenu:
		m_mainMenu.Draw(m_window);
		break;
	case RulesMenu:
		m_rulesMenu.Draw(m_window);
		break;
	case InRun:
		UpdateGameRun(deltaTime);
		break;
	case PauseMenu:
		m_pauseMenu.Draw(m_window);
		break;
	default:
		break;
	}
}

void Game::UpdateGameRun(float deltaTime)
{
	m_currentRun->Run(deltaTime);
	m_currentRun->Render();
}

void Game::ManageWindowEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				m_window.close();
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			Clickable::IsMousePressed = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			Clickable::IsMousePressed = false;
		}
	}
}

std::unique_ptr<GameRun> Game::NewRun()
{
	auto game = std::make_unique<GameRun>(m_window);

	// TODO: Init the game run (select some enemies, etc) (we may initialize it within the constructor of GameRun)

	m_currentState = GameState::InRun;

	return std::move(game);
}


void Game::BeginNewRun()
{
	// TODO : Start a new run
	std::cout << "Starting a new run !\n";

	m_currentRun = NewRun();
	m_currentState = GameState::InRun;
}

void Game::ShowRules()
{
	// TODO : Show the RULES menu
	std::cout << "Showing the rules!\n";
}

void Game::QuitRequest()
{
	std::cout << "Quitting...\n";
	// Close the window
	m_window.close();
}