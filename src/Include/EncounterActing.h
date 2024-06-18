#pragma once

#include "EncounterState.h"


class EncounterActing : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

};