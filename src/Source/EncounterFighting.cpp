#include "EncounterFighting.h"
#include "Configs.h"

#include <random>
#include <format>

EncounterFighting::EncounterFighting(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{
	m_attackBox = IDrawable({ 0, 0 }, FilePaths::SP_SH_CURSOR, { 1, 1 }, true);
	m_cursor = IDrawable({ 0, 0 }, FilePaths::SP_SH_CURSOR, {1, 1}, true);

	m_attackBoxWidth = m_attackBox.GetSprite().getGlobalBounds().width;
	m_damageFont.loadFromFile(FilePaths::FONT_DAMAGE);
	m_damageText.setFont(m_damageFont);
}


void EncounterFighting::OnEnter()
{
	InitAttackBox();
}

void EncounterFighting::Update(float deltaTime)
{
	switch (m_state)
	{
		case AttackState::Attacking:

			m_cursor.Move({ 0, m_cursorSpeed * deltaTime });

			if (m_cursor.GetPosition().x >= m_attackBox.GetPosition().x + m_attackBoxWidth / 2)
				m_state = AttackState::Failed;
			else
			{
				// Detect if the user pressed the space bar
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					m_state = AttackState::Succeeded;
				}
			}
			break;

		case AttackState::Succeeded:
		
			if (!m_initSucceeded)
			{
				m_initSucceeded = true;

				// Compute the damage: the more it is in the middle, the more damage it does (with an exponential distribution)
				float dmgMult = 1 - std::abs(m_cursor.GetPosition().x - m_attackBox.GetPosition().x) / (m_attackBoxWidth / 2);
				//dmgMult = static_cast<float>(std::pow(dmgMult, 2));

				auto damage = static_cast<int>(dmgMult * 100);

				// Update the text and show it
				m_damageText.setString(std::format("{}", damage * 100));
				m_damageText.setPosition(m_cursor.GetPosition().x, m_cursor.GetPosition().y - 100);

				// TODO: Play a sound
				// TODO: Play an animation (optionnal)
				// TODO: Damage the monster
			}

			break;

		case AttackState::Failed:

			if (!m_initFailed)
			{
				m_initFailed = true;

				// Update the text and show it
				m_damageText.setString(std::format("Manqué"));
				m_damageText.setPosition(m_cursor.GetPosition().x, m_cursor.GetPosition().y - 100);
			}

			break;
	}

	if (m_state != AttackState::Attacking)
	{
		m_timer -= deltaTime;

		if (m_timer <= 0)
		{
			// Exit state
			m_parentEncounter->SetState(EncounterStateType::MonsterTurn);
		}
	}

}

void EncounterFighting::OnExit()
{
	// réaffichage des boutons attaque et actions, update des dialogues
}

void EncounterFighting::InitAttackBox()
{
	auto windowSize = m_parentEncounter->GetWindow().getSize();

	m_attackBox.Move(sf::Vector2f{
		static_cast<float>(windowSize.x) / 2 + Anchors::ATTACK_BOX_FROM_MIDDLE[0],
		static_cast<float>(windowSize.y) / 2 + Anchors::ATTACK_BOX_FROM_MIDDLE[1]
		});


	// Place the cursor at the beginning of the attack box according to the dimensions of the attack box

	m_cursor.Move(sf::Vector2f{
		m_attackBox.GetPosition().x - m_attackBoxWidth / 2,
		m_attackBox.GetPosition().y
		});

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis(-1.f, 1.f);

	m_cursorSpeed = m_attackBoxWidth / (Config::GLOBAL_ATTACK_TIME + dis(gen) * Config::GLOBAL_ATTACK_TIME_VARIANCE);

	m_initSucceeded = false;
	m_initFailed = false;

	m_timer = Config::WAIT_TIME_AFTER_ATTACK;
}

void EncounterFighting::CloseAttackBox()
{

}


void EncounterFighting::Draw(sf::RenderWindow& window) const
{
	m_attackBox.Draw(window);
	m_cursor.Draw(window);

	if (m_state != AttackState::Attacking)
	{
		window.draw(m_damageText);
	}
}