#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Baby.h"
#include "Encounter.h"


class Enemy;



enum class RunState {
	Intro,
	InEncounter,
	InTransition,
	InWin
};

class GameRun {

public:
	explicit GameRun(sf::RenderWindow& rWindow);

	void Run(float deltaTime);
	void Render() const;

	void AddEnemy(EnemyData* enemy);
	void InitNextEncounter();

	sf::Vector2f GetMousePosition() const;

private:
	Player m_player = Player{ Config::DEFAULT_PLAYER_NAME, Config::DEFAULT_PLAYER_MAX_HP };
	Baby m_baby;

	sf::RenderWindow* m_window;
	sf::Music m_currentMusic;


	std::unique_ptr<Encounter> m_currentEncounter;
	std::vector<EnemyData*> m_enemies;


	RunState m_state = RunState::Intro;

	int m_nextEncounterIndex = 0;
	float m_timer = 2.f;
};