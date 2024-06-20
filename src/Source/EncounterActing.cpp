#include "EncounterActing.h"
#include "Button.h"
#include "Encounter.h"
#include <iostream>

EncounterActing::EncounterActing(Encounter* parentEncounter) :
	EncounterState(parentEncounter),
	m_window(parentEncounter->GetWindow())
{
	BuildActionButtons();
}

void EncounterActing::OnEnter()
{
	std::cout << "Acting" << std::endl;
	m_parentEncounter->GetDialogueBox().LockTextBox(true);
	m_parentEncounter->GetDialogueBox().Show();
	m_acted = false;
	m_parentEncounter->SetButtonsActive(false);
	SetActionsActive(true);
}

void EncounterActing::Update(float deltaTime)
{
	if (m_acted)
	{
		if (m_parentEncounter->GetDialogueBox().IsFinished())
		{
			m_parentEncounter->ModifyBabyHappiness(m_upcomingModifier);
			m_parentEncounter->SetState(EncounterStateType::MonsterTurn);
		}
		return;
	}

	for (const auto& button : m_actionButtons)
	{
		button->Update(m_window, deltaTime);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_parentEncounter->SetState(EncounterStateType::Idle);
	}
}

void EncounterActing::OnExit()
{
	m_parentEncounter->GetDialogueBox().LockTextBox(false);
	m_parentEncounter->GetDialogueBox().Hide();
	// Let the buttons deactivated
}

void EncounterActing::Draw(sf::RenderWindow& window) const
{
	for (const auto& button : m_actionButtons)
	{
		button->Draw(window);
	}
}

void EncounterActing::SetActionsActive(bool active) const
{
	for (const auto& button : m_actionButtons)
	{
		button->SetEnabled(active);
		button->SetVisible(active);
	}
}

void EncounterActing::ProcessAction(ActionData* action)
{
	std::cout << "Acting: " << action->Name << std::endl;

	m_acted = true;
	SetActionsActive(false);
	m_upcomingModifier = action->HappinessShift;
	m_parentEncounter->SetDialogue(action->AssociatedDialogue);
	m_parentEncounter->GetDialogueBox().LockTextBox(false);
}

void EncounterActing::BuildActionButtons()
{
	int xIndex = 0;
	int yIndex = 0;

	for (const auto& action : *m_parentEncounter->GetPossibleActions())
	{
		// Initalizing the text buttons from the center of the screen

		m_actionButtons.push_back(std::make_unique<Button>(sf::Vector2f {
			static_cast<float>(m_window.getSize().x / 2 + Anchors::ACTION_BUTTONS_FROM_MIDDLE[xIndex]),
			static_cast<float>(m_window.getSize().y / 2 + Anchors::ACTION_BUTTONS_FROM_MIDDLE[2+yIndex])
			},
			action->Name,
			30,
			[this, action]() { this->ProcessAction(action); },
			true));

		
		xIndex++;

		if (xIndex > 1)
		{
			xIndex = 0;
			yIndex++;
		}
	}
}
