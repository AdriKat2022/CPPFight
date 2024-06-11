#pragma once


#include "EncounterState.h"

class EncounterIdle : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update() override;
	void OnExit() override;

};