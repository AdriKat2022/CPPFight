#include "EncounterIdle.h"
#include "Encounter.h"
#include <iostream>



EncounterIdle::EncounterIdle(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{

}

void EncounterIdle::OnEnter()
{
	std::cout << "Idle" << std::endl;
	m_parentEncounter->SetButtonsActive(true);
}

void EncounterIdle::Update(float deltaTime)
{

}

void EncounterIdle::OnExit()
{
	m_parentEncounter->SetButtonsActive(false);
}

void EncounterIdle::Draw(sf::RenderWindow& window) const
{

}