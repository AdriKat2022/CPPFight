#pragma once

#include "EncounterState.h"
#include "Button.h"

class ActionData;

class EncounterActing : public EncounterState {

public:
	explicit EncounterActing(Encounter* parentEncounter);

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

	void Draw(sf::RenderWindow& window) const override;


private:
	void SetActionsActive(bool active) const;
	void ProcessAction(ActionData* action);
	void BuildActionButtons();

	sf::RenderWindow& m_window;

	std::vector<std::unique_ptr<Button>> m_actionButtons;

	bool m_acted = false;

	int m_upcomingModifier = 0;

};