#pragma once

#include "EncounterState.h"
#include "IDrawable.h"
#include "Enemy.h"
#include "FightButton.h"
#include "ActionButton.h"
#include <memory>


enum class EncounterStateType {
	Idle,
	Acting,
	Fighting,
	MonsterTurn
};


class Encounter : public IDrawable {

public:
	// Initialize an encounter with an enemy
	Encounter(Game* m_parentGame);

	void Update();
	void Draw(sf::RenderWindow&) const override;


private:
	// State management
	void SetState(EncounterStateType);


private:
	Game* m_parentGame;

	std::shared_ptr<EncounterState> m_currentEncounterState;

	std::shared_ptr<EncounterState> m_encounterIdle;
	std::shared_ptr<EncounterState> m_encounterActing;
	std::shared_ptr<EncounterState> m_encounterFighting;
	std::shared_ptr<EncounterState> m_encounterMonsterTurn;

	Enemy m_enemy;

	FightButton m_fightBtn;
	ActionButton m_actionBtn;

};