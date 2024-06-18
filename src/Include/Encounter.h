#pragma once

#include "IDrawable.h"
#include "Enemy.h"
#include <memory>
#include <Menu.h>
#include "Baby.h"
#include "Player.h"
#include "TextBox.h"

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
	Encounter(GameRun& gameRun, EnemyData* enemy);

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow&) const override;
	void GenerateMenus();
	
	sf::RenderWindow& GetWindow() const;

	// State management
	void SetState(EncounterStateType);

	// Getters
	std::vector<ActionData*>* GetPossibleActions();
	float GetDamageMultiplier() const;

	void SetDialogue(Dialogue& dialogue);
	TextBox& GetDialogueBox();
	bool IsDialogueFinished() const;

	void DamageMonster(int damage);
	void DamagePlayer(int damage);
	void SetButtonsActive(bool active) const;
	void EndEncounter();

	bool IsMonsterDead() const;

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

	//Baby baby;
	sf::Text name_baby;
	sf::RectangleShape background_happiness_baby;
	sf::RectangleShape happiness_bar_baby;
	sf::Text damage_mult;

	Player player = Player{ Config::DEFAULT_PLAYER_NAME, Config::DEFAULT_PLAYER_MAX_HP };
	sf::Text name_player;
	sf::RectangleShape background_hp_player;
	sf::RectangleShape HP_bar_player;

	std::vector<ActionData*> m_enemyActions;
	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;
	TextBox m_dialogueBox;
};