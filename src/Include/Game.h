#pragma once

#include "Player.h"
#include "Baby.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Game {

public:
	Game();

	void Render() const;
	void Initialize();
	void Run();

private:
	sf::RenderWindow m_window;
	Player m_player;
	Baby m_baby;

};