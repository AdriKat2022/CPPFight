#pragma once

#include "Button.h"


class Encounter;


class ActionButton : public Button
{
public:

	ActionButton(sf::Vector2f position, Encounter* parentEncounter);

	bool IsInBounds(sf::Vector2f position) override;
	void OnClick(sf::Vector2f position) override;


private:
	Encounter* m_parentEncounter;

};