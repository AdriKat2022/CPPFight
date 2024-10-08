#pragma once

#include <SFML/Graphics.hpp>

class Encounter;

class EncounterState {

public:
	explicit EncounterState(Encounter* parentEncounter) : m_parentEncounter(parentEncounter) {}

	virtual ~EncounterState() = default;
	
	virtual void OnEnter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnExit() = 0;

	virtual void Draw(sf::RenderWindow& window) const = 0;

protected:
	Encounter* m_parentEncounter; // Parent encounter, so it can be accessed by the state

};