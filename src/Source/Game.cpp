#include "Game.h"
#include "Clickable.h"
#include "Button.h"
#include "EnemyLoader.h"
#include <Menu.h>


Game::Game()
{
	LoadEnemiesData();
	GenerateMenus();
	m_mainMenuMusic.openFromFile(FilePaths::MUSIC_MENU_MAIN);
	m_mainMenuMusic.setLoop(true);
	m_mainMenuMusic.play();
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

		m_window.clear();

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
	m_mainMenu.AddSprite(FilePaths::MENU_BG, sf::Vector2f{ 0,0 }, sf::Vector2i{ 1, 1 }, false);
	m_mainMenu.AddButton(FilePaths::SP_SH_PLAY_BTN, sf::Vector2f(400, 100), [this]() { this->BeginNewRun(); });
	m_mainMenu.AddButton(FilePaths::SP_SH_RULES_BTN, sf::Vector2f(400, 300), [this]() { this->ShowRules();  });
	m_mainMenu.AddButton(FilePaths::SP_SH_QUIT_BTN, sf::Vector2f(400, 500), [this]() { this->QuitRequest(); });

	m_rulesMenu.AddButton(FilePaths::SP_SH_BACK_BTN, sf::Vector2f(400, 525), [this]() { this->m_currentState = GameState::MainMenu; });
	m_rulesMenu.AddSprite(FilePaths::RULES_BG, sf::Vector2f{ 0,0 }, sf::Vector2i{ 1, 1 }, false);

	// TODO: Make the pause menu (no time for that)

	// TODO: Make the pre-run screen (no time for that)
}

void Game::UpdateGame(float deltaTime)
{
	// The Rules menu has been done in a hurry, so it's loading a lot of resources
	sf::Text rules;
	sf::Font font;
	switch (m_currentState)
	{
		using enum GameState;

	case MainMenu:
		m_mainMenu.Draw(m_window);
		break;
	case RulesMenu:
		font.loadFromFile(FilePaths::FONT_MAIN);
		rules.setFont(font);
		rules.setString(R"( Dans ce jeu, vous incarnez un parent qui doit protéger son bébé des terribles 
 ennemis qui lui font face, les C et les P. Pour défendre votre nourisson, 
 vous avez la possibilité d'attaquer le monstre en cliquant sur le bouton 'fight'.
 Le système d'attaque est simple : un curseur se déplace dans un rectangle 
 et il suffit de cliquer pour arrêter ce curseur : plus vous êtes proche du 
 centre du rectangle, plus vous infligez de dégats. Mais attention attaquer 
 un monstre fait baisser la jauge de bonheur de votre enfant (car pendant 
 que vous attaquez, il n'a pas l'attention qu'il désire). Cette jauge est 
 importante car le bébé peut vous donner des bonus ou malus en fonction 
 de son bonheur: plus il est heureux, plus vous faites de dégats. 
 Mais comment le rendre heureux ? C'est très simple, il suffit de cliquer 
 sur le bouton 'action' qui vous propose ensuite un choix entre 4 actions 
 qui peuvent faire monter la jauge de bonheur du bébé.Cependant certaines actions 
 peuvent également diminuer son bonheur.Alors quelle sera la meilleure stratégie 
 pour venir à bout de vos terribles adversaires ? A vous de voir en jouant à CPPFight.)");
		rules.setCharacterSize(20);
		rules.setLineSpacing(1.5);
		rules.setFillColor(sf::Color::White);
		rules.setPosition({ 75, 10 });
		m_rulesMenu.Draw(m_window);
		m_window.draw(rules);
		break;
	case PreRunScreen:
		m_preRunMenu.Draw(m_window); // Unused cause of time
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
	auto newRun = std::make_unique<GameRun>(m_window);

	newRun->AddEnemy(&m_enemyDataBank->at(0));
	newRun->AddEnemy(&m_enemyDataBank->at(2));
	newRun->AddEnemy(&m_enemyDataBank->at(3));

	return std::move(newRun);
}

void Game::PrepareNewRun()
{
	// TODO : Prepare a new run


	std::cout << "Preparing a new run !\n";

	m_currentState = GameState::PreRunScreen;

	BeginNewRun(); // No time to make a real preparation
}

void Game::BeginNewRun()
{
	// TODO : Start a new run
	std::cout << "Starting a new run !\n";

	m_currentRun = NewRun();
	m_currentRun->LaunchRun();
	m_mainMenuMusic.stop();
	m_currentState = GameState::InRun;
}

void Game::ShowRules()
{
	// TODO : Show the RULES menu DONE
	std::cout << "Showing the rules!\n";

	m_currentState = GameState::RulesMenu;
}

void Game::QuitRequest()
{
	std::cout << "Quitting...\n";
	// Close the window
	m_window.close();
}