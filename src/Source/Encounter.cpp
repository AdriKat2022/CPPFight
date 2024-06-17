#include "Encounter.h"
#include "Configs.h"
#include "TextBox.h"

void Encounter::Update()
{

}

void Encounter::Draw(sf::RenderWindow& window) const
{
	//affichage de l'ennemi, son nom, sa barre de vie, du bébé, son nom, sa barre de bonheur et du multiplicateur de dégats, du player, son nom et sa barre de vie, affichage des boutons attaque et action et du dialogue
	TextBox name_ennemy;
	name_ennemy.SetString(m_enemy.GetName());
	name_ennemy.SetPosition(350, 10);
	name_ennemy.Draw(window);

	sf::RectangleShape background_hp_enemy({ 100, 50 });
	background_hp_enemy.setFillColor(sf::Color::Yellow);
	background_hp_enemy.setPosition({ 350, 50 });
	window.draw(background_hp_enemy);
	sf::RectangleShape HP_bar_enemy({ 100 * (m_enemy.GetHP() / m_enemy.GetMaxHP()), 40 });
	HP_bar_enemy.setFillColor(sf::Color::Red);
	HP_bar_enemy.setPosition({ 350, 55 });
	window.draw(HP_bar_enemy);

}

void Encounter::SetState(EncounterStateType type)
{
	m_encounterStateType = std::make_shared<EncounterStateType>(type);
}
