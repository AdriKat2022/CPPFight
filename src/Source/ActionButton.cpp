#include "ActionButton.h"
#include "FilePaths.h"


ActionButton::ActionButton(sf::Vector2f position, Encounter* parentEncounter) :
	Button(position, FilePaths::SP_SH_ACTION_BTN),
	m_parentEncounter(parentEncounter)
{

}

void ActionButton::OnClick(sf::Vector2f position)
{
	Button::OnClick(position);

	// TODO: OnClick of ActionButton
}