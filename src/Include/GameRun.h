#pragma once

#include "Player.h"
#include "Baby.h"
#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


// TODO: Rename this as GameRun since it corresponds to the game loop
class GameRun {

public:
	explicit GameRun(sf::RenderWindow & rWindow);

	void Run(float deltaTime);
	void Render() const;

	void InitEncounter();

	sf::Vector2f GetMousePosition() const;

private:
	sf::RenderWindow* m_window;
	sf::Music m_currentMusic;

	Player m_player = Player{ std::string("Chara"), 20 };
	Baby m_baby;

	std::vector<std::unique_ptr<Enemy>> m_enemies;



	int m_currentEncounter = 0;
};