#pragma once

#include "EncounterState.h"


class EncounterActing : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update() override;
	void OnExit() override;

};