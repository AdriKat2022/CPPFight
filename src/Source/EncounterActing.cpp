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
	m_acted = false;
	m_parentEncounter->SetButtonsActive(false);
}

void EncounterActing::Update(float deltaTime)
{
	if (m_acted)
	{
		if(m_parentEncounter->GetDialogueBox().IsFinished())
			m_parentEncounter->SetState(EncounterStateType::MonsterTurn);
		return;
	}

	for (auto& button : m_actionButtons)
	{
		button.Update(m_window, deltaTime);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_parentEncounter->SetState(EncounterStateType::Idle);
	}
}

void EncounterActing::OnExit()
{
	// Let the buttons deactivated
}

void EncounterActing::Draw(sf::RenderWindow& window) const
{
	for (const auto& button : m_actionButtons)
	{
		button.Draw(window);
	}
}

void EncounterActing::ProcessAction(ActionData* action)
{
	m_parentEncounter->SetDialogue(action->AssociatedDialogue);
}

void EncounterActing::BuildActionButtons()
{
	int xIndex = 0;
	int yIndex = 0;


	for (const auto& action : *m_parentEncounter->GetPossibleActions())
	{
		// Initalizing the text buttons from the center of the screen

		m_actionButtons.emplace_back(sf::Vector2f{
			static_cast<float>(m_window.getSize().x / 2 + Anchors::ACTION_BUTTONS_FROM_MIDDLE[xIndex]),
			static_cast<float>(m_window.getSize().y / 2 + Anchors::ACTION_BUTTONS_FROM_MIDDLE[yIndex])
			}, action->Name, [this, &action]() { this->ProcessAction(action); }, true);


		//m_parentEncounter->GetDialogueBox().SetPosition(button.GetPosition().x, button.GetPosition().y + 100);

		xIndex++;

		if (xIndex > 1)
		{
			xIndex = 0;
			yIndex++;
		}

		//const auto& button = m_actionButtons.at(static_cast<size_t>(xIndex + 2 * yIndex - 1));

		//button.Draw(m_parentEncounter->GetWindow());
		//button.Draw(m_parentEncounter->GetWindow());
	}

	m_actionButtons[0].Draw(m_parentEncounter->GetWindow());
	m_actionButtons.at(1).Draw(m_parentEncounter->GetWindow());
	m_actionButtons.at(2).Draw(m_parentEncounter->GetWindow());

	m_parentEncounter->GetWindow().display();

	std::cout << "Built " << m_actionButtons.size() << " action buttons." << std::endl;
}
