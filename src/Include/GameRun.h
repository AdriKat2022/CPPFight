#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Baby.h"
#include "Encounter.h"


class Game;
class Enemy;


enum class RunState {
	Intro,
	InEncounter,
	InTransition,
	InWin,
	Lose
};

class GameRun {

public:
	explicit GameRun(Game& parentGame, sf::RenderWindow& rWindow);

	void Run(float deltaTime);
	void Render();

	void LaunchRun();
	void AddEnemy(EnemyData* enemy);
	void InitNextEncounter();

	sf::RenderWindow& GetWindow() const;
	sf::Vector2f GetMousePosition() const;

	void DamagePlayer(int damage);
	void FullHeal();
	Baby& GetBaby();
	Player& GetPlayer();
	void SetState(RunState);

	void Gameover();

private:
	Game& m_parentGame;

	Player m_player = Player{ Config::DEFAULT_PLAYER_NAME, Config::DEFAULT_PLAYER_MAX_HP };
	Baby m_baby;

	sf::RenderWindow& m_window;
	sf::Music m_currentMusic;


	std::unique_ptr<Encounter> m_currentEncounter;
	std::vector<EnemyData*> m_enemies;
	
	Menu m_rewardMenu;
	Menu m_gameoverMenu;

	RunState m_state = RunState::Intro;

	int m_nextEncounterIndex = 0;
	float m_timer = 2.f;
	bool m_runReady = false;
};