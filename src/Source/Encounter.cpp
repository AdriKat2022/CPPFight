#include "Encounter.h"
#include "Configs.h"
#include "GameRun.h"
#include <format>
#include <iostream>

#include "EncounterActing.h"
#include "EncounterFighting.h"
#include "EncounterIdle.h"
#include "EncounterMonsterTurn.h"

Encounter::Encounter(GameRun& gameRun, EnemyData* enemy) :
	m_window(gameRun.GetWindow()),
	m_parentRun(gameRun),
	m_enemy(enemy),
	player(m_parentRun.GetPlayer())
{
	undertale_font.loadFromFile(FilePaths::FONT_MAIN);

	//definition du nom de l'ennemi
	name_enemy.setString(m_enemy.GetName());
	name_enemy.setPosition({ 350, 10 });
	name_enemy.setFont(undertale_font);
	name_enemy.setCharacterSize(20);
	name_enemy.setFillColor(sf::Color::White);

	//définition de la barre de vie de l'ennemi
	background_hp_enemy.setSize({ 120, 50 });
	background_hp_enemy.setFillColor(sf::Color::White);
	background_hp_enemy.setPosition({ static_cast<float>(m_window.getSize().x/2) - background_hp_enemy.getGlobalBounds().width/2, 50});
	HP_bar_enemy.setSize(sf::Vector2f(static_cast<float> (100 * (m_enemy.GetHP() / m_enemy.GetMaxHP())), 40));
	HP_bar_enemy.setFillColor(sf::Color::Red);
	HP_bar_enemy.setPosition({ 350, 55 });

	//définition du nom du bébé
	name_baby.setString("Baboum");
	name_baby.setPosition(680, 550);
	name_baby.setFont(undertale_font);
	name_baby.setCharacterSize(10);
	name_baby.setFillColor(sf::Color::White);

	//définition de la barre de bonheur du bébé
	background_happiness_baby.setSize({ 50, 100 });
	background_happiness_baby.setFillColor(sf::Color::White);
	background_happiness_baby.setPosition({ 700, 440 });
	happiness_bar_baby.setSize(sf::Vector2f(40.f, static_cast<float>(m_parentRun.GetBaby().GetHappiness())));
	happiness_bar_baby.setFillColor(sf::Color::Yellow);
	happiness_bar_baby.setPosition(sf::Vector2f(705, static_cast<float>(440 + (100 - m_parentRun.GetBaby().GetHappiness()))));

	//définition du multiplicateur de dégats
	damage_mult.setString(std::format("Dégats * \n {}", m_parentRun.GetBaby().GetMult()));
	damage_mult.setPosition(760, 490);
	damage_mult.setFont(undertale_font);
	damage_mult.setCharacterSize(10);
	damage_mult.setFillColor(sf::Color::White);

	//définition du nom du joueur
	name_player.setString(player.GetName());
	name_player.setPosition(350, 560);
	name_player.setFont(undertale_font);
	name_player.setCharacterSize(10);
	name_player.setFillColor(sf::Color::White);

	//définition de la barre de vie du joueur
	background_hp_player.setSize({ 120, 60 });
	background_hp_player.setFillColor(sf::Color::White);
	background_hp_player.setPosition({
		static_cast<float>(m_window.getSize().x / 2) - background_hp_player.getGlobalBounds().width / 2,
		static_cast<float>(m_window.getSize().y) - 150
		});
	HP_bar_player.setSize({ 100, 40 });
	HP_bar_player.setScale(sf::Vector2f(static_cast<float>(player.GetHP()) / static_cast<float>(player.GetMaxHP()), 1));
	HP_bar_player.setFillColor(sf::Color::Red);
	HP_bar_player.setPosition({
		static_cast<float>(m_window.getSize().x / 2) - background_hp_player.getGlobalBounds().width / 2,
		static_cast<float>(m_window.getSize().y) - 150 + background_hp_player.getGlobalBounds().height/2});

	// Background
	m_backgroundTexture.loadFromFile(FilePaths::ENCOUNTER_BG);
	m_background.setTexture(m_backgroundTexture);

	GenerateMenus();

	// Load the pointers to the enemies actions
	for (auto& action : enemy->Actions)
	{
		m_enemyActions.push_back(&action);
	}


	m_encounterIdle = std::make_shared<EncounterIdle>(this);
	m_encounterActing = std::make_shared<EncounterActing>(this);
	m_encounterFighting = std::make_shared<EncounterFighting>(this);
	m_encounterMonsterTurn = std::make_shared<EncounterMonsterTurn>(this);

}


void Encounter::Update(float deltaTime)
{
	// Already done by the encounter state of MonsterTurn
	//if (m_enemy.IsDead() == true) {
	//	m_parentRun.SetState(RunState::InTransition);
	//}

	if(m_currentEncounterState)
		m_currentEncounterState->Update(deltaTime);
}

void Encounter::Draw(sf::RenderWindow& window) const
{
	window.draw(m_background);

	//affichage de l'ennemi, son nom, sa barre de vie
	window.draw(name_enemy);
	window.draw(background_hp_enemy);
	window.draw(HP_bar_enemy);

	//affichage du bébé via le background, son nom, sa barre de bonheur et du multiplicateur de dégats
	window.draw(name_baby);
	window.draw(background_happiness_baby);
	window.draw(happiness_bar_baby);
	window.draw(damage_mult);

	//du player via le background, son nom et sa barre de vie
	window.draw(name_player);
	window.draw(background_hp_player);
	window.draw(HP_bar_player);

	// affichage des boutons attaque et action et du dialogue
	m_menu_select.Draw(window);

	if(m_currentEncounterState)
		m_currentEncounterState->Draw(window);
}

sf::RenderWindow& Encounter::GetWindow() const
{
	return m_parentRun.GetWindow();
}

float Encounter::GetDamageMultiplier() const
{
	return m_parentRun.GetBaby().GetMult();
}

GameRun* Encounter::GetParentRun() const
{
	return &m_parentRun;
}

void Encounter::SetDialogue(Dialogue& dialogue)
{
	m_dialogueBox.SetDialogue(dialogue);
}

std::vector<ActionData*>* Encounter::GetPossibleActions()
{
	return &m_enemyActions;
}

void Encounter::GenerateMenus() {
	m_menu_select.AddButton(FilePaths::SP_SH_FIGHT_BTN, sf::Vector2f(200, 500), [this]() { this->SetState(EncounterStateType::Fighting); });
	m_menu_select.AddButton(FilePaths::SP_SH_ACTION_BTN, sf::Vector2f(600, 500), [this]() { this->SetState(EncounterStateType::Acting);  });
}


void Encounter::SetState(EncounterStateType type)
{
	if (m_currentEncounterState)
		m_currentEncounterState->OnExit();

	switch (type)
	{
		using enum EncounterStateType;

	case Idle:
		m_currentEncounterState = m_encounterIdle;
		break;

	case Acting:
		m_currentEncounterState = m_encounterActing;
		break;

	case Fighting:
		m_currentEncounterState = m_encounterFighting;
		break;

	case MonsterTurn:
		m_currentEncounterState = m_encounterMonsterTurn;
		break;
	}

	m_currentEncounterState->OnEnter();
}

TextBox& Encounter::GetDialogueBox()
{
	return m_dialogueBox;
}

float Encounter::GetMonsterSpeed() const
{
	return static_cast<float>(m_enemy.GetSpeed());
}

float Encounter::GetMonsterAttackPower() const
{
	return static_cast<float>(m_enemy.GetAttackPower());
}

void Encounter::DamageMonster(int damage)
{
	m_enemy.Damage(damage);
	HP_bar_enemy.setScale(sf::Vector2f(static_cast<float>(m_enemy.GetHP()) / static_cast<float>(m_enemy.GetMaxHP()), 1));
}

void Encounter::DamagePlayer(int damage)
{
	player.Damage(damage);
	HP_bar_player.setScale(sf::Vector2f(static_cast<float>(player.GetHP()) / static_cast<float>(player.GetMaxHP()), 1));
}

void Encounter::ModifyBabyHappiness(int modifier)
{
	m_parentRun.GetBaby().Modify(modifier);
	happiness_bar_baby.setScale(sf::Vector2f(1, static_cast<float>(m_parentRun.GetBaby().GetHappiness()) / 100.f));
}

void Encounter::SetButtonsActive(bool active) const
{
	m_menu_select.SetButtonsActive(active);
}

bool Encounter::IsMonsterDead() const
{
	return m_enemy.IsDead();
}

void Encounter::EndEncounter()
{
	m_parentRun.SetState(RunState::InTransition);
}

bool Encounter::IsDialogueFinished() const
{
	return m_dialogueBox.IsFinished();
}