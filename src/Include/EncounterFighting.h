#pragma once

#include "EncounterState.h"

class EncounterFighting : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update() override;
	void OnExit() override;

};