#pragma once

#include "Button.h"


class Encounter;


class FightButton : public Button
{
public:

	FightButton(sf::Vector2f position, Encounter* parentEncounter);

	void OnClick(sf::Vector2f position) override;


private:
	Encounter* m_parentEncounter;

};