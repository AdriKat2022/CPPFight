#pragma once

#include "EncounterState.h"

class Button;

class EncounterActing : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

	void Draw(sf::RenderWindow& window) const override;

private:
	std::vector<Button> m_buttons;

};