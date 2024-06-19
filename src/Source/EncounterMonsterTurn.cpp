#include "EncounterMonsterTurn.h"
#include "Encounter.h"
#include <iostream>

void EncounterMonsterTurn::OnEnter()
{
	std::cout << "Monster turn" << std::endl;

	// Check death of monster
	m_isDead = m_parentEncounter->IsMonsterDead();
}

void EncounterMonsterTurn::Update(float deltaTime)
{
	if (m_isDead)
	{
		m_exitTimer -= deltaTime;

		if (m_exitTimer <= 0 && m_parentEncounter->IsDialogueFinished())
		{
			m_parentEncounter->EndEncounter();
		}

		return;
	}
}

void EncounterMonsterTurn::OnExit()
{
	if(!m_isDead)
		m_parentEncounter->SetButtonsActive(true);
	
}

void EncounterMonsterTurn::Draw(sf::RenderWindow& window) const
{
	// Nothing to draw
}