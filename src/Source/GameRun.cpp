#include <iostream>
#include "GameRun.h"
#include "Button.h"
#include "Clickable.h"
#include "Configs.h"



GameRun::GameRun(sf::RenderWindow& rWindow) :
	m_window(rWindow)
{
	// Construct the game
	std::cout << "Constructing run..." << std::endl;


	// Run music
	m_currentMusic.openFromFile(FilePaths::MUSIC_RUN_MAIN);
	m_currentMusic.play();
	m_currentMusic.setLoop(true);

	// Create the reward menu
	// TODO: Add multiple buttons for several rewards (more power, more health, or full heal)
	m_rewardMenu.AddButton("", {200, 200}, [this]() {
		InitNextEncounter();
	});

	std::cout << "Run constructed." << std::endl;
}

void GameRun::AddEnemy(EnemyData* enemy)
{
	m_enemies.push_back(enemy);
}

void GameRun::Run(float deltaTime)
{
	switch (m_state)
	{
		using enum RunState;

		case Intro:
			// Unused for now
			break;

		case InEncounter:
			m_currentEncounter->Update(deltaTime);
			break;

		case InTransition:
			InitNextEncounter();
			break;

		case InWin:

			break;
	}
}

void GameRun::InitNextEncounter()
{
	if(m_nextEncounterIndex >= m_enemies.size())
	{
		std::cout << "No more encounters to run." << std::endl;
		return;
	}

	m_currentEncounter = std::make_unique<Encounter>(*this, m_enemies[m_nextEncounterIndex]);
	m_nextEncounterIndex++;
	m_state = RunState::InEncounter;
}

sf::RenderWindow& GameRun::GetWindow() const
{
	return m_window;
}

sf::Vector2f GameRun::GetMousePosition() const {
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
}

Baby& GameRun::GetBaby()
{
	return m_baby;
}

void GameRun::Render() const
{
	if(m_state == RunState::InEncounter)
		m_currentEncounter->Draw(m_window);
}


