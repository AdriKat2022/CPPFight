#include <random>
#include <iostream>
#include <format>
#include "EncounterFighting.h"
#include "Encounter.h"

EncounterFighting::EncounterFighting(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{
	m_attackBoxWidth = m_attackBox.GetSprite().getGlobalBounds().width;
	m_damageFont.loadFromFile(FilePaths::FONT_DAMAGE);
	m_damageText.setFont(m_damageFont);
	m_multText.setFont(m_damageFont);

	m_attackSoundBuffer.loadFromFile(FilePaths::SOUND_HIT);
	m_attackSound.setBuffer(m_attackSoundBuffer);
}


void EncounterFighting::OnEnter()
{
	std::cout << "Fighting" << std::endl;
	m_state = AttackState::Attacking;
	m_timer = Config::WAIT_TIME_AFTER_ATTACK;
	m_parentEncounter->SetButtonsActive(false);
	InitAttackBox();
}

void EncounterFighting::Update(float deltaTime)
{
	switch (m_state)
	{
		case AttackState::Attacking:

			m_cursor.Move({ m_cursorSpeed * deltaTime, 0 });

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

				auto damage = static_cast<int>(dmgMult * Config::DEFAULT_PLAYER_BASE_DAMAGE);
				auto babyMult = m_parentEncounter->GetDamageMultiplier();

				// Update the text and show it
				m_damageText.setString(std::format("{}", damage));
				m_damageText.setPosition(m_cursor.GetPosition().x, m_cursor.GetPosition().y - 100);

				m_multText.setString(std::format("x {}", babyMult));
				m_multText.setPosition(
					m_damageText.getPosition().x + Anchors::MULT_TEXT_FROM_DMG_TEXT[0],
					m_damageText.getPosition().y + Anchors::MULT_TEXT_FROM_DMG_TEXT[1]
				);

				m_damageText.setFillColor({
					Colors::DAMAGE_TEXT_COLOR_HIT[0],
					Colors::DAMAGE_TEXT_COLOR_HIT[1],
					Colors::DAMAGE_TEXT_COLOR_HIT[2]
					});

				// TODO: Play an animation (optionnal)

				m_damageTotalShown = false;
				m_upcomingDamage = static_cast<int>(static_cast<float>(damage) * babyMult);
				m_timer = Config::WAIT_TIME_AFTER_ATTACK;

			}
			else if (m_timer <= 2.f && !m_damageTotalShown)
			{
				m_damageTotalShown = true;
				m_attackSound.play();


				m_parentEncounter->DamageMonster(m_upcomingDamage);
			}


			break;

			
		case AttackState::Failed:

			if (m_initFailed)
			{
				m_initFailed = true;

				// Update the text and show it
				m_damageText.setString(std::format("Manqué"));
				m_damageText.setPosition(m_cursor.GetPosition().x, m_cursor.GetPosition().y - 100);
				m_damageText.setCharacterSize(48);
				m_damageText.setFillColor({
					Colors::DAMAGE_TEXT_COLOR_MISSED[0],
					Colors::DAMAGE_TEXT_COLOR_MISSED[1],
					Colors::DAMAGE_TEXT_COLOR_MISSED[2]
					});
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
	// Nothing to clean and since the draw function won't be called anymore, the attack box and the cursor will be hidden
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

	m_state = AttackState::Attacking;
}

void EncounterFighting::CloseAttackBox()
{
	// Unused for now
}


void EncounterFighting::Draw(sf::RenderWindow& window) const
{
	m_attackBox.Draw(window);
	m_cursor.Draw(window);
	window.draw(m_multText);

	if (m_state != AttackState::Attacking)
	{
		window.draw(m_damageText);
	}
}