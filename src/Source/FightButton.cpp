#include "FightButton.h"
#include "FilePaths.h"


FightButton::FightButton(sf::Vector2f position, Encounter* parentEncounter) :
	Button(position, FilePaths::SP_SH_FIGHT_BTN),
	m_parentEncounter(parentEncounter)
{

}

bool FightButton::IsInBounds(sf::Vector2f position)
{
	return GetSprite().getGlobalBounds().contains(position.x, position.y);
}

void FightButton::OnClick(sf::Vector2f position)
{
	// TODO : OnClick of FightButton
}