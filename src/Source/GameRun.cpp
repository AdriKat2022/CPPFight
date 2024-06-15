#include <iostream>
#include "GameRun.h"
#include <Button.h>
#include "Clickable.h"
//std::vector<std::shared_ptr<IDrawable>> DRAWABLES;
GameRun::GameRun(sf::RenderWindow & rWindow) :
	m_window(&rWindow)
{
	// Construct the game
	std::cout << "Constructing run..." << std::endl;


	// Main menu music
	m_currentMusic.openFromFile("resources/Audio/Music/minigame-soundtrack.wav");
	m_currentMusic.play();
	m_currentMusic.setLoop(true);

	std::cout << "GameRun constructed." << std::endl;
}

sf::Vector2f GameRun::GetMousePosition() const {
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));
}

void GameRun::Render() const {
	// Render the game
}

/*void ExampleFunction() {
	// This function is called when the button is clicked (see example in CreateMenuButton and where it's called)
	std::cout << "Button clicked !" << std::endl;
}*/

void GameRun::Run(float deltaTime) {
	// Run the game
	//std::cout << "Running game" << std::endl;
	
	// définition du menu dans un premier temps
	// définition du background du menu
	sf::RectangleShape background_menu(static_cast<sf::Vector2f> (m_window->getSize()));
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
	m_window->clear();
	m_window->draw(background_menu);
	m_window->draw(play_button);
	m_window->draw(rules_button);
	m_window->draw(quit_button);
	/*for (const auto& drawable : DRAWABLES_2) {
		drawable->Draw(*m_window);
	}*/
}

