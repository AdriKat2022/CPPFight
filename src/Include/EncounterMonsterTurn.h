#pragma once

#include "EncounterState.h"

class EncounterMonsterTurn : public EncounterState {

public:
	using EncounterState::EncounterState;

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

private:

	bool m_isDead = false;
	float m_exitTimer = 1.5f;


};