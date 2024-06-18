#include "Game.h"

#include <iostream>



int main() {
	sf::Music test;
	test.openFromFile(FilePaths::SOUND_BABY_CRYING);
	test.play();
	test.setLoop(true);
	Game game;
	game.RunGame();
	
}

