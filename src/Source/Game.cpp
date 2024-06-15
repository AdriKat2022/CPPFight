#include "Game.h"
#include "Clickable.h"
#include "Button.h"
#include "EnemyLoader.h"


Game::Game()
{
	LoadEnemiesData();

	AddMenuButton(FilePaths::SP_SH_PLAY_BTN, sf::Vector2f(100, 100), [](Game& gameContext) {
		gameContext.NewRun(gameContext.m_window);
		gameContext.m_currentState = GameState::InRun;
	});

	AddMenuButton(FilePaths::SP_SH_QUIT_BTN, sf::Vector2f(100, 200), [](Game& gameContext) {
		gameContext.m_window.close();
	});

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



		UpdateGameMenu();


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
}

void Game::UpdateGameRun()
{

}

// This may be renamed to "Render" in the future since we might want to separe the update and render functions
void Game::RenderGameRun()
{

}

void Game::UpdateGameMenu()
{
	// définition du menu dans un premier temps
	// définition du background du menu
	sf::RectangleShape background_menu(static_cast<sf::Vector2f> (m_window.getSize()));
	sf::Texture texture_background;
	texture_background.loadFromFile(FilePaths::SP_SH_MENU_BG);
	background_menu.setTexture(&texture_background);

	// définition du bouton "play"
	sf::RectangleShape play_button(sf::Vector2f(200, 100));
	play_button.setPosition(sf::Vector2f(300, 50));
	sf::Texture texture_play_button;
	texture_play_button.loadFromFile(FilePaths::SP_SH_PLAY_BTN);
	play_button.setTexture(&texture_play_button);
	/*auto play_button = std::make_shared<Button>(sf::Vector2f(400, 100), FilePaths::SP_SH_PLAY_BTN, sf::Vector2i(1, 2), ExampleFunction);
	DRAWABLES.push_back(play_button);*/

	// définition du bouton "rules"
	sf::RectangleShape rules_button(sf::Vector2f(200, 100));
	rules_button.setPosition(sf::Vector2f(300, 250));
	sf::Texture texture_rules_button;
	texture_rules_button.loadFromFile(FilePaths::SP_SH_RULES_BTN);
	rules_button.setTexture(&texture_rules_button);
	/*auto rules_button = std::make_shared<Button>(sf::Vector2f(400, 300), FilePaths::SP_SH_RULES_BTN, sf::Vector2i(1, 2), ExampleFunction);
	DRAWABLES.push_back(rules_button);*/

	// définition du bouton "quit game"
	sf::RectangleShape quit_button(sf::Vector2f(200, 100));
	quit_button.setPosition(sf::Vector2f(300, 450));
	sf::Texture texture_quit_button;
	texture_quit_button.loadFromFile(FilePaths::SP_SH_QUIT_BTN);
	quit_button.setTexture(&texture_quit_button);
	/*auto quit_button = std::make_shared<Button>(sf::Vector2f(400, 500), FilePaths::SP_SH_QUIT_BTN, sf::Vector2i(1, 2), ExampleFunction);
	DRAWABLES.push_back(quit_button);*/

	// affichage du menu
	m_window.clear();
	m_window.draw(background_menu);
	m_window.draw(play_button);
	m_window.draw(rules_button);
	m_window.draw(quit_button);
	/*for (const auto& drawable : DRAWABLES_2) {
		drawable->Draw(*m_window);
	}*/
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

void Game::AddMenuButton(const std::string& spritePath, sf::Vector2f position, void(*OnClickEvent)(Game& gameContext))
{
	auto button = std::make_shared<Button>(position, spritePath, sf::Vector2i(1, 2), OnClickEvent);
	m_menuDrawable.push_back(button);
	m_menuButtons.push_back(std::move(button));
}

void Game::AddDrawableToRenderList(std::shared_ptr<IDrawable> drawable)
{
	m_menuDrawable.push_back(std::move(drawable));
}

std::unique_ptr<GameRun> Game::NewRun(sf::RenderWindow& renderWindow)
{
	auto game = std::make_unique<GameRun>(renderWindow);

	// TODO: Init the game run (select some enemies, etc) (we may initialize it within the constructor of GameRun)

	// TODO: Change application state to game

	return std::move(game);
}
