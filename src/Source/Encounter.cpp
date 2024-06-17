#include "Encounter.h"
#include "Configs.h"
#include "TextBox.h"
#include "Player.h"
#include "GameRun.h"
#include "EncounterState.h"
#include <format>
#include <iostream>



Encounter::Encounter(GameRun& gameRun, const EnemyData* enemy) :
	m_parentRun(gameRun),
	m_enemy(enemy)
{
	m_encounterStateType = std::make_shared<EncounterStateType>(EncounterStateType::Idle);
}


void Encounter::Update()
{
	m_currentEncounterState->Update();
}

void Encounter::Draw(sf::RenderWindow& window) const
{
	//affichage de l'ennemi (TODO), son nom, sa barre de vie

	TextBox name_enemy;
	name_enemy.SetString(m_enemy.GetName());
	name_enemy.SetPosition(350, 10);
	name_enemy.Draw(window);

	sf::RectangleShape background_hp_enemy({ 100, 50 });
	background_hp_enemy.setFillColor(sf::Color::White);
	background_hp_enemy.setPosition({ 350, 50 });
	window.draw(background_hp_enemy);

	sf::RectangleShape HP_bar_enemy(sf::Vector2f( 100 * (m_enemy.GetHP() / m_enemy.GetMaxHP()), 40 ));
	HP_bar_enemy.setFillColor(sf::Color::Red);
	HP_bar_enemy.setPosition({ 350, 55 });
	window.draw(HP_bar_enemy);

	//affichage du bébé (TODO), son nom, sa barre de bonheur et du multiplicateur de dégats
	Baby baby;

	TextBox name_baby;
	name_baby.SetString("J-C");
	name_baby.SetPosition(680, 550);
	name_baby.Draw(window);

	sf::RectangleShape background_happiness_baby({ 50, 100 });
	background_happiness_baby.setFillColor(sf::Color::White);
	background_happiness_baby.setPosition({ 700, 440 });
	window.draw(background_happiness_baby);

	sf::RectangleShape happiness_bar_baby(sf::Vector2f(40.f, static_cast<float>(baby.GetHappiness())));
	happiness_bar_baby.setFillColor(sf::Color::Yellow);
	happiness_bar_baby.setPosition(sf::Vector2f(705, 440 + (100 - baby.GetHappiness())));
	window.draw(happiness_bar_baby);

	TextBox damage_mult;
	damage_mult.SetString(std::format ("Dégats * \n %f", baby.GetMult()));
	damage_mult.SetPosition(760, 490);
	damage_mult.Draw(window);

	//du player(TODO), son nom et sa barre de vie
	Player player("J-P",100);

	TextBox name_player;
	name_player.SetString(player.GetName());
	name_player.SetPosition(350, 560);
	name_player.Draw(window);

	sf::RectangleShape background_hp_player({ 100, 50 });
	background_hp_player.setFillColor(sf::Color::White);
	background_hp_player.setPosition({ 350, 500 });
	window.draw(background_hp_player);

	sf::RectangleShape HP_bar_player(sf::Vector2f(100 * (player.GetHP() / player.GetMaxHP()), 40));
	HP_bar_player.setFillColor(sf::Color::Red);
	HP_bar_player.setPosition({ 350, 505 });
	window.draw(HP_bar_player);

	// affichage des boutons attaque et action et du dialogue
	m_menu_select.Draw(window);

}


void Encounter::GenerateMenus() {
	m_menu_select.AddButton(FilePaths::SP_SH_FIGHT_BTN, sf::Vector2f(400, 100), [this]() { this->SetState(EncounterStateType::Fighting); });
	m_menu_select.AddButton(FilePaths::SP_SH_ACTION_BTN, sf::Vector2f(400, 300), [this]() { this->SetState(EncounterStateType::Acting);  });
}


void Encounter::SetState(EncounterStateType type)
{
	m_encounterStateType = std::make_shared<EncounterStateType>(type);
}
