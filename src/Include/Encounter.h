#pragma once

#include "GameRun.h"
#include "IDrawable.h"
#include "Enemy.h"
#include <memory>
#include <Menu.h>

class EncounterState;

enum class EncounterStateType {
	Idle,
	Acting,
	Fighting,
	MonsterTurn
};


class Encounter : public IDrawable {

public:
	// Initialize an encounter with an enemy
	//Encounter(GameRun* m_parentGame, EnemyData* enemyData);

	void Update();
	void Draw(sf::RenderWindow&) const override;

	// State management
	void SetState(EncounterStateType);


private:
	GameRun* m_parentGame;

	std::shared_ptr<EncounterState> m_currentEncounterState;

	std::shared_ptr<EncounterStateType> m_encounterStateType;

	std::shared_ptr<EncounterState> m_encounterIdle;
	std::shared_ptr<EncounterState> m_encounterActing;
	std::shared_ptr<EncounterState> m_encounterFighting;
	std::shared_ptr<EncounterState> m_encounterMonsterTurn;

	Enemy m_enemy;
	Menu m_menu;
	//FightButton m_fightBtn;
	//ActionButton m_actionBtn;

};