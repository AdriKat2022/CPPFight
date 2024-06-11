#include "Game.h"


Game::Game(sf::RenderWindow* rWindow) :
	m_window(rWindow)
{
	// Construct the game
	std::cout << "Constructing game..." << std::endl;


	// Main menu music
	m_currentMusic.openFromFile("resources/Audio/Music/minigame-soundtrack.wav");
	m_currentMusic.play();
	m_currentMusic.setLoop(true);

	std::cout << "Game constructed." << std::endl;
}


void Game::Render() const {
	// Render the game
}

void Game::Run() {
	// Run the game
	//std::cout << "Running game" << std::endl;
	
	// définition du menu dans un premier temps
	// définition du background du menu
	sf::RectangleShape background_menu(static_cast<sf::Vector2f>(m_window->getSize()));
	sf::Texture texture;
	texture.loadFromFile("resources/Sprites/P.png");
	background_menu.setTexture(&texture);
	// définition du bouton "play"
	sf::RectangleShape play_button(sf::Vector2f (200,100));
	play_button.setPosition(sf::Vector2f(300, 50));
	play_button.setTexture(&texture);
	// définition du bouton "rules"
	sf::RectangleShape rules_button(sf::Vector2f(200, 100));
	rules_button.setPosition(sf::Vector2f(300, 250));
	rules_button.setTexture(&texture);
	// définition du bouton "quit game"
	sf::RectangleShape quit_button(sf::Vector2f(200, 100));
	quit_button.setPosition(sf::Vector2f(300, 450));
	quit_button.setTexture(&texture);
	// affichage du menu
	m_window->clear();
	m_window->draw(background_menu);
	m_window->draw(play_button);
	m_window->draw(rules_button);
	m_window->draw(quit_button);
}