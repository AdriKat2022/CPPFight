#pragma once

#include "EncounterState.h"
#include "Menu.h"

class EncounterIdle : public EncounterState {

public:
	explicit EncounterIdle(Encounter* parentEncounter);

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

	void Draw(sf::RenderWindow& window) const override;

};