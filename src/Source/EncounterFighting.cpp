#include <random>
#include <iostream>
#include <format>
#include "EncounterFighting.h"
#include "Encounter.h"
#include "GameRun.h"
#include "Configs.h"

EncounterFighting::EncounterFighting(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{
	// Load the attack box and the cursor and the fonts
	m_attackBoxWidth = m_attackBox.GetSprite().getGlobalBounds().width;
	m_damageFont.loadFromFile(FilePaths::FONT_DAMAGE);
	m_critText.setFont(m_damageFont);
	m_critText.setCharacterSize(30);
	m_critText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 + 80,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - 35
		);
	m_critText.setString("");
	m_critText.setFillColor({
		Colors::CRIT_TEXT_COLOR[0],
		Colors::CRIT_TEXT_COLOR[1],
		Colors::CRIT_TEXT_COLOR[2]
		});
	m_damageText.setFont(m_damageFont);
	m_multText.setFont(m_damageFont);
	m_multText.setFillColor({
		Colors::MULT_TEXT_COLOR[0],
		Colors::MULT_TEXT_COLOR[1],
		Colors::MULT_TEXT_COLOR[2]
		});

	// Load sounds
	m_hitAttack.loadFromFile(FilePaths::SOUND_HIT);
	m_criticalHitAttack.loadFromFile(FilePaths::SOUND_CRITICAL_HIT);
	m_unbelievableAttack.loadFromFile(FilePaths::SOUND_UNBELIEVABLE_ATTACK);
	m_perfectAttack.loadFromFile(FilePaths::SOUND_PERFECT_ATTACK);
	m_excellentAttack.loadFromFile(FilePaths::SOUND_EXCELLENT_ATTACK);
	m_normalAttack.loadFromFile(FilePaths::SOUND_NORMAL_ATTACK);
	m_attackSound.setVolume(50*Config::GLOBAL_VOLUME_MULT);
	m_cursor.GetSprite().setScale(2, 2);
}


void EncounterFighting::OnEnter()
{
	std::cout << "Fighting" << std::endl;
	m_damageTextSpeed = 350;
	m_damageText.setString("");
	m_multText.setString("");
	m_critText.setString("");
	m_state = AttackState::Attacking;
	m_cursor.SetAnimation(0, 0);
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
				dmgMult = static_cast<float>(std::pow(dmgMult, 3));

				auto damage = static_cast<int>(dmgMult * Config::DEFAULT_PLAYER_BASE_DAMAGE);
				auto babyMult = m_parentEncounter->GetDamageMultiplier();

				m_wasCritical = dmgMult >= (1-Config::INCREDIBLE_ATTACK_TOLERANCE);

				if (m_wasCritical)
				{
					damage = static_cast<int>(static_cast<float>(damage) * Config::INCREDIBLE_ATTACK_MULT);
					m_critText.setString(Config::CRIT_TEXT);
					m_critText.setScale(3, 3);
				}

				std::cout << m_critText.getPosition().x << " " << m_critText.getPosition().y << std::endl;

				// Update the text and show it
				m_damageText.setCharacterSize(30);
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

				// Set the attack animation at the center of the screen
				m_attackAnimation.SetPosition(sf::Vector2f{
					static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2,
					static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - 75
					});
				m_attackAnimation.SetActive(true);
				m_attackAnimation.SetAnimation(7, 1);
				m_cursor.SetAnimation(10.f, 0);

				m_damageTotalShown = false;
				m_upcomingDamage = static_cast<int>(static_cast<float>(damage) * babyMult);

				if(m_wasCritical)
					m_attackSound.setBuffer(m_unbelievableAttack);
				else if (babyMult >= 1.f && damage >= Config::DEFAULT_PLAYER_BASE_DAMAGE - 1)
					m_attackSound.setBuffer(m_perfectAttack);
				else if (damage >= Config::DEFAULT_PLAYER_BASE_DAMAGE - 1)
					m_attackSound.setBuffer(m_excellentAttack);
				else
					m_attackSound.setBuffer(m_normalAttack);

				m_attackSound.play();

			}
			else if (m_timer <= Config::WAIT_TIME_AFTER_ATTACK / 2 && !m_damageTotalShown)
			{
				m_damageTotalShown = true;

				m_multText.setString("");
				m_damageText.setCharacterSize(45);
				m_damageText.setString(std::format("{}", m_upcomingDamage));
				m_damageText.setPosition(m_cursor.GetPosition().x, m_cursor.GetPosition().y - 100);


				m_damageText.setFillColor({
					Colors::DAMAGE_TEXT_COLOR_HIT[0],
					Colors::DAMAGE_TEXT_COLOR_HIT[1],
					Colors::DAMAGE_TEXT_COLOR_HIT[2]
					});

				if (m_wasCritical)
					m_attackSound.setBuffer(m_criticalHitAttack);
				else
					m_attackSound.setBuffer(m_hitAttack);

				m_attackSound.play();

				auto& baby = m_parentEncounter->GetParentRun()->GetBaby();

				baby.Modify(std::min(-baby.GetHappiness() / 2, -5));

				m_parentEncounter->DamageMonster(m_upcomingDamage);
			}
			else
			{
				m_attackAnimation.Update(deltaTime);
			}

			if (m_wasCritical)
			{
				auto scale = m_critText.getScale().x;
				scale -= (scale - 1) * deltaTime * 6;
				m_critText.setScale(scale, scale);
			}


			if (m_damageTextSpeed > -320 && m_damageTotalShown)
			{
				m_damageText.move(0, -deltaTime * m_damageTextSpeed);
				m_damageTextSpeed -= deltaTime * 800;
			}

			break;

			
		case AttackState::Failed:

			if (!m_initFailed)
			{
				m_initFailed = true;

				// Update the text and show it
				m_damageText.setCharacterSize(48);
				m_damageText.setString(std::format("Miss"));
				m_damageText.setPosition(m_cursor.GetPosition().x - 100, m_cursor.GetPosition().y - 100);
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

	m_cursor.Update(deltaTime);
}

void EncounterFighting::OnExit()
{
	// Nothing to clean and since the draw function won't be called anymore, the attack box and the cursor will be hidden
}

void EncounterFighting::InitAttackBox()
{
	auto windowSize = m_parentEncounter->GetWindow().getSize();

	m_attackBox.SetPosition(sf::Vector2f{
		static_cast<float>(windowSize.x) / 2 + Anchors::ATTACK_BOX_FROM_MIDDLE[0],
		static_cast<float>(windowSize.y) / 2 + Anchors::ATTACK_BOX_FROM_MIDDLE[1]
		});


	// Place the cursor at the beginning of the attack box according to the dimensions of the attack box

	m_cursor.SetPosition(sf::Vector2f{
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
	window.draw(m_critText);

	if (m_state != AttackState::Attacking)
	{
		window.draw(m_damageText);
	}
	if(m_state == AttackState::Succeeded)
		m_attackAnimation.Draw(window);
}