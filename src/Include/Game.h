#pragma once

#include "Player.h"
#include "Baby.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Game {

public:
	explicit Game(sf::RenderWindow*);

	void Run();
	void Render() const;

private:
	sf::RenderWindow* m_window;
	sf::Music m_currentMusic;
	Player m_player = Player{ std::string("Chara"), 20 };
	Baby m_baby;

};