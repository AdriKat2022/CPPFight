#include "Main.h"
#include "GameRun.h"
#include <iostream>

#include "Main.h"
#include "EnemyData.h"
#include "EnemyLoader.h"
#include "Configs.h"
#include "Clickable.h"
#include "IDrawable.h"
#include "Button.h"
#include "Configs.h"

struct EnemyData;


// TODO: Move those global variables to the Game class

std::unique_ptr<std::vector<EnemyData>> ENEMIES;

// Only for the menu before the game starts
std::vector<std::shared_ptr<Clickable>> MENU_BUTTONS;
std::vector<std::shared_ptr<IDrawable>> DRAWABLES;


enum class GameState {
	MainMenu,
	InRun,
	Paused
};

// TODO: Move the logic of the menu and most of the functions of this file to the Game class

int main() {
	std::cout << "Starting !" << std::endl;

	LoadEnemiesData();

	// Create a window to pass to game
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	
	// Create the game
	GameRun gameRun(window);

	// Test button
	CreateMenuButton(FilePaths::SP_SH_PLAY_BTN, { 100, 100 }, ExampleFunction);

	// To measure deltatime
	sf::Clock clock;


	while(window.isOpen()) {
		sf::Event event;

		ManageEvents(window, event);

		// Get the elapsed time and restart the clock
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();


		Update(gameRun, deltaTime);
		UpdateRun(gameRun, deltaTime);

		Render(gameRun, window);

		window.display();
	}
}

void ManageEvents(sf::RenderWindow& window, sf::Event& event)
{
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
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

// Begins a new run of the game
std::unique_ptr<GameRun> NewRun(sf::RenderWindow & renderWindow)
{
	auto game = std::make_unique<GameRun>(renderWindow);

	// TODO: Init the game (select some enemies, etc)

	// TODO: Change application state to game

	return std::move(game);
}

// This function is used to update the menu and framework of the game, it is not used to update the game itself (which is done in UpdateRun)
void Update(GameRun& gameRun, float deltaTime) {
	
	// TODO: Update the application according to the current state (menu, inRun, paused)

	for (const auto& clickable : MENU_BUTTONS) {
		clickable->Update(gameRun, deltaTime);
	}

}

// This function is used to update the current run of the game
void UpdateRun(GameRun& gameRun, float deltaTime) {
	gameRun.Run(deltaTime);
}

void Render(const GameRun & game, sf::RenderWindow& window) {
	game.Render();

	// TODO: Render the application according to the current state

	for (const auto& drawable : DRAWABLES) {
		drawable->Draw(window);
	}
}

void CreateMenuButton(const std::string& spritePath, sf::Vector2f position, void (*OnClickEvent)()) {
	// Create a button
	auto button = std::make_shared<Button>(position, spritePath, sf::Vector2i(1, 2), OnClickEvent);
	AddClickable(button);
	AddDrawable(button);

	// TODO: Make this Function more generic so it could also be used in the Game class
}


void ExampleFunction() {
	// This function is called when the button is clicked (see example in CreateMenuButton and where it's called)
	std::cout << "Button clicked !" << std::endl;
}


void AddClickable(std::shared_ptr<Clickable> clickable)
{
	MENU_BUTTONS.push_back(clickable);
}

void AddDrawable(std::shared_ptr<IDrawable> drawable)
{
	DRAWABLES.push_back(drawable);
}

void LoadEnemiesData() {
	EnemyLoader loader;
	loader.ReadFromFile(FilePaths::ENEMY_DATA_LIST, ENEMIES);
}