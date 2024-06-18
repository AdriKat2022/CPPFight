#pragma once


#include "EncounterState.h"

class EncounterIdle : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

	void Draw(sf::RenderWindow& window) const override;
};