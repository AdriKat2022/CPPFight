#pragma once

#include "Button.h"


class Encounter;


class FightButton : public Button
{
public:

	FightButton(sf::Vector2f position, Encounter* parentEncounter);

	bool IsInBounds(sf::Vector2f position);
	void OnClick(sf::Vector2f position);


private:
	Encounter* m_parentEncounter;

};