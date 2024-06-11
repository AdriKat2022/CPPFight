#pragma once

#include "Button.h"
#include "Encounter.h"

class FightButton : public Button
{

public:

	FightButton(int x, int y, Encounter* parentEncounter);

	bool IsInBounds(sf::Vector2i position);
	void OnClick(sf::Vector2i position);


private:
	Encounter* m_parentEncounter;

};