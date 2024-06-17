#pragma once

#include "IDrawable.h"
#include "Enemy.h"
#include <memory>
#include <Menu.h>


class EncounterState;
class GameRun;


enum class EncounterStateType {
	Idle,
	Acting,
	Fighting,
	MonsterTurn
};


class Encounter : public IDrawable {

public:
	Encounter(GameRun& gameRun, const EnemyData* enemy);

	void Update();
	void Draw(sf::RenderWindow&) const override;
	void GenerateMenus();
	

	// State management
	void SetState(EncounterStateType);


private:
	GameRun& m_parentRun;

	Enemy m_enemy;

	std::shared_ptr<EncounterStateType> m_encounterStateType;

	std::shared_ptr<EncounterState> m_currentEncounterState;
	std::shared_ptr<EncounterState> m_encounterIdle;
	std::shared_ptr<EncounterState> m_encounterActing;
	std::shared_ptr<EncounterState> m_encounterFighting;
	std::shared_ptr<EncounterState> m_encounterMonsterTurn;

	Menu m_menu_select;
	


};