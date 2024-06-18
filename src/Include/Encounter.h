#pragma once

#include "IDrawable.h"
#include "Enemy.h"
#include <memory>
#include <Menu.h>
#include "Baby.h"
#include "Player.h"


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

	void Update(float deltaTime);
	void Draw(sf::RenderWindow&) const override;
	void GenerateMenus();
	
	sf::RenderWindow& GetWindow() const;

	// State management
	void SetState(EncounterStateType);


private:
	sf::RenderWindow& m_window;

	GameRun& m_parentRun;

	Enemy m_enemy;

	std::shared_ptr<EncounterStateType> m_encounterStateType;

	std::shared_ptr<EncounterState> m_currentEncounterState;
	std::shared_ptr<EncounterState> m_encounterIdle;
	std::shared_ptr<EncounterState> m_encounterActing;
	std::shared_ptr<EncounterState> m_encounterFighting;
	std::shared_ptr<EncounterState> m_encounterMonsterTurn;
	
	sf::Font undertale_font;
	
	Menu m_menu_select;
	
	sf::Text name_enemy;
	sf::RectangleShape background_hp_enemy;
	sf::RectangleShape HP_bar_enemy;

	Baby baby;
	sf::Text name_baby;
	sf::RectangleShape background_happiness_baby;
	sf::RectangleShape happiness_bar_baby;
	sf::Text damage_mult;

	//Player player;
	sf::Text name_player;
	sf::RectangleShape background_hp_player;
	sf::RectangleShape HP_bar_player;

};