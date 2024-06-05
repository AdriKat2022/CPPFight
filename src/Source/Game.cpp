#include "Game.h"


Game::Game() {
	// Construct the game
	std::cout << "Constructing game" << std::endl;
}


void Game::Render() const {
	// Render the game
	std::cout << "Rendering game" << std::endl;
}

void Game::Run() {
	// Run the game
	std::cout << "Running game" << std::endl;
}

void Game::Initialize() {
	// Initialize the game
	std::cout << "Initializing game" << std::endl;
}