#include "Encounter.h"
#include "Configs.h"
#include "TextBox.h"
#include "Player.h"
#include "GameRun.h"
#include "EncounterState.h"
#include <format>
#include <iostream>



Encounter::Encounter(GameRun& gameRun, const EnemyData* enemy) :
	m_window(gameRun.GetWindow()),
	m_parentRun(gameRun),
	m_enemy(enemy)
{
	m_encounterStateType = std::make_shared<EncounterStateType>(EncounterStateType::Idle);
	undertale_font.loadFromFile(FilePaths::FONT_MAIN);

	//definition du nom de l'ennemi
	name_enemy.setString(m_enemy.GetName());
	name_enemy.setPosition({ 350, 10 });
	name_enemy.setFont(undertale_font);
	name_enemy.setCharacterSize(10);
	name_enemy.setFillColor(sf::Color::White);

	//définition de la barre de vie de l'ennemi
	background_hp_enemy.setSize({ 100, 50 });
	background_hp_enemy.setFillColor(sf::Color::White);
	background_hp_enemy.setPosition({ 350, 50 });
	HP_bar_enemy.setSize(sf::Vector2f(100 * (m_enemy.GetHP() / m_enemy.GetMaxHP()), 40));
	HP_bar_enemy.setFillColor(sf::Color::Red);
	HP_bar_enemy.setPosition({ 350, 55 });

	//définition du nom du bébé
	name_baby.setString("J-C");
	name_baby.setPosition(680, 550);
	name_baby.setFont(undertale_font);
	name_baby.setCharacterSize(10);
	name_baby.setFillColor(sf::Color::White);

	//définition de la barre de bonheur du bébé
	background_happiness_baby.setSize({ 50, 100 });
	background_happiness_baby.setFillColor(sf::Color::White);
	background_happiness_baby.setPosition({ 700, 440 });
	happiness_bar_baby.setSize(sf::Vector2f(40.f, static_cast<float>(baby.GetHappiness())));
	happiness_bar_baby.setFillColor(sf::Color::Yellow);
	happiness_bar_baby.setPosition(sf::Vector2f(705, 440 + (100 - baby.GetHappiness())));

	//définition du multiplicateur de dégats
	damage_mult.setString(std::format("Dégats * \n %f", baby.GetMult()));
	damage_mult.setPosition(760, 490);
	damage_mult.setFont(undertale_font);
	damage_mult.setCharacterSize(10);
	damage_mult.setFillColor(sf::Color::White);

	//définition du nom du joueur
	Player player("J-P", 100);
	name_player.setString(player.GetName());
	name_player.setPosition(350, 560);
	name_player.setFont(undertale_font);
	name_player.setCharacterSize(10);
	name_player.setFillColor(sf::Color::White);

	//définition de la barre de vie du joueur
	background_hp_player.setSize({ 100, 50 });
	background_hp_player.setFillColor(sf::Color::White);
	background_hp_player.setPosition({ 350, 500 });
	HP_bar_player.setSize(sf::Vector2f(100 * (player.GetHP() / player.GetMaxHP()), 40));
	HP_bar_player.setFillColor(sf::Color::Red);
	HP_bar_player.setPosition({ 350, 505 });
}


void Encounter::Update(float deltaTime)
{
	m_currentEncounterState->Update(deltaTime);
}

void Encounter::Draw(sf::RenderWindow& window) const
{
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

}

sf::RenderWindow& Encounter::GetWindow() const
{
	return m_parentRun.GetWindow();
}

float Encounter::GetDamageMultiplier() const
{
	return baby.GetMult();
}

void Encounter::GenerateMenus() {
	m_menu_select.AddSprite(FilePaths::ENCOUNTER_BG, sf::Vector2f{ 0,0 }, sf::Vector2i{ 1, 1 }, false);
	m_menu_select.AddButton(FilePaths::SP_SH_FIGHT_BTN, sf::Vector2f(400, 100), [this]() { this->SetState(EncounterStateType::Fighting); });
	m_menu_select.AddButton(FilePaths::SP_SH_ACTION_BTN, sf::Vector2f(400, 300), [this]() { this->SetState(EncounterStateType::Acting);  });
}


void Encounter::SetState(EncounterStateType type)
{
	m_encounterStateType = std::make_shared<EncounterStateType>(type);
}
