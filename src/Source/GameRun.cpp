#include <iostream>
#include "GameRun.h"
#include "Button.h"
#include "Clickable.h"
#include "Configs.h"



GameRun::GameRun(sf::RenderWindow& rWindow) :
	m_window(&rWindow)
{
	// Construct the game
	std::cout << "Constructing run..." << std::endl;


	// Run music
	m_currentMusic.openFromFile(FilePaths::MUSIC_RUN_MAIN);
	m_currentMusic.play();
	m_currentMusic.setLoop(true);



	std::cout << "GameRun constructed." << std::endl;
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

			break;

		case InEncounter:
			m_currentEncounter->Update();
			break;

		case InTransition:

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

	m_currentEncounter = std::make_unique<Encounter>(m_enemies[m_nextEncounterIndex]);
	m_nextEncounterIndex++;
	m_state = RunState::InEncounter;
}

sf::Vector2f GameRun::GetMousePosition() const {
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));
}

void GameRun::Render() const
{
	// TODO: Render the run screen
}


