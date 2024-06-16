#include "Game.h"
#include "Clickable.h"
#include "Button.h"
#include "EnemyLoader.h"
#include <Menu.h>

void ExampleFunction() {
	// This function is called when the button is clicked (see example in CreateMenuButton and where it's called)
	std::cout << "Button clicked !" << std::endl;
}

Game::Game()
{
	LoadEnemiesData();
	
	// définition et affichage du background du menu
	sf::RectangleShape background_menu(static_cast<sf::Vector2f> (m_window.getSize()));
	sf::Texture texture_background;
	texture_background.loadFromFile(FilePaths::SP_SH_MENU_BG);
	background_menu.setTexture(&texture_background);
	m_window.draw(background_menu);

	//définition et affichage des boutons du menu
	Menu menu;
	menu.AddButton(FilePaths::SP_SH_PLAY_BTN, sf::Vector2f(400, 100), [](Context& context) {std::cout << "Working! \n"; } /*NewRun(m_window)*/);
	menu.AddButton(FilePaths::SP_SH_RULES_BTN, sf::Vector2f(400, 300), [](Context& context) {std::cout << "Working! \n"; } /*ShowRules()*/);
	menu.AddButton(FilePaths::SP_SH_QUIT_BTN, sf::Vector2f(400, 500), [](Context& context) {std::cout << "Working! \n"; } /*Exit(m_window)*/);
	menu.Draw(m_window);
	
}

void Game::RunGame()
{
	// To measure deltatime
	sf::Clock clock;

	m_window.display();
	while (m_window.isOpen()) {

		ManageWindowEvents();

		// Get the delta time thanks to the clock
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();



		//UpdateGameMenu();


		//m_window.display();
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

static std::unique_ptr<GameRun> NewRun(sf::RenderWindow& renderWindow)
{
	auto game = std::make_unique<GameRun>(renderWindow);

	// TODO: Init the game run (select some enemies, etc) (we may initialize it within the constructor of GameRun)

	// TODO: Change application state to game

	return std::move(game);
}
