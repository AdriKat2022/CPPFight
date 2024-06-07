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
	//std::cout << "Rendering game" << std::endl;
}

void Game::Run() {
	// Run the game
	//std::cout << "Running game" << std::endl;
}