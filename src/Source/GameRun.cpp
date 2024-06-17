#include <iostream>
#include "GameRun.h"
#include <Button.h>
#include "Clickable.h"


GameRun::GameRun(sf::RenderWindow& rWindow) :
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


void GameRun::Run(float deltaTime) {
	// Run the game run
	//std::cout << "Running game" << std::endl;
	
}

