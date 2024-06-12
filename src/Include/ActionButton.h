#pragma once

#include "Button.h"

class ActionButton : public Button
{
public:

	ActionButton(int x, int y, Encounter* parentEncounter);

	bool IsInBounds(sf::Vector2i position);
	void OnClick(sf::Vector2i position);


private:
	Encounter* m_parentEncounter;

};