#include "FightButton.h"
#include "FilePaths.h"


FightButton::FightButton(sf::Vector2f position, Encounter* parentEncounter) :
	Button(position, FilePaths::SP_SH_FIGHT_BTN),
	m_parentEncounter(parentEncounter)
{

}

void FightButton::OnClick(sf::Vector2f position)
{
	Button::OnClick(position);

	// TODO : OnClick of FightButton
}