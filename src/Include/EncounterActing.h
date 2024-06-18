#pragma once

#include "EncounterState.h"

class Button;

class EncounterActing : public EncounterState {

public:
	explicit EncounterActing(Encounter* parentEncounter);

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

	void Draw(sf::RenderWindow& window) const override;


private:

	void ProcessAction(ActionData* action);
	void BuildActionButtons();

	sf::RenderWindow& m_window;

	std::vector<Button> m_actionButtons;

};