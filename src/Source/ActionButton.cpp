#include "ActionButton.h"
#include "FilePaths.h"


ActionButton::ActionButton(sf::Vector2f position, Encounter* parentEncounter) :
	Button(position, FilePaths::SP_SH_ACTION_BTN),
	m_parentEncounter(parentEncounter)
{

}

bool ActionButton::IsInBounds(sf::Vector2f position)
{
	return GetSprite().getGlobalBounds().contains(position.x, position.y);
}

void ActionButton::OnClick(sf::Vector2f position)
{
	// TODO: OnClick of ActionButton
}