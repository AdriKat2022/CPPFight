#pragma once

#include "Encounter.h"

class EncounterState {

public:
	explicit EncounterState(Encounter* parentEncounter) : m_parentEncounter(parentEncounter) {}

	virtual ~EncounterState() = default;
	
	virtual void OnEnter() = 0;
	virtual void Update() = 0;
	virtual void OnExit() = 0;

protected:
	Encounter* m_parentEncounter; // Parent encounter, so it can be accessed by the state

};