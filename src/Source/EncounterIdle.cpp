#include "EncounterIdle.h"
#include "Encounter.h"
#include "GameRun.h"
#include <iostream>



EncounterIdle::EncounterIdle(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{

}

void EncounterIdle::OnEnter()
{
	m_parentEncounter->SetButtonsActive(true);


	if (m_parentEncounter->GetParentRun()->GetPlayer().IsDead())
	{
		m_parentEncounter->GetParentRun()->Gameover();
	}
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