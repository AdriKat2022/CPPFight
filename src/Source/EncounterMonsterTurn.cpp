#include "EncounterMonsterTurn.h"
#include "Encounter.h"
#include "Configs.h"
#include <iostream>
#include <random>
#include <format>

#define CENTER_TEXT(text) text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2)

EncounterMonsterTurn::EncounterMonsterTurn(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{
	m_showdown.loadFromFile(FilePaths::SOUND_SHOWDOWN);
	m_getReady.loadFromFile(FilePaths::SOUND_GET_READY);
	m_success.loadFromFile(FilePaths::SOUND_SUCCESS);
	m_missed.loadFromFile(FilePaths::SOUND_MISSED);

	m_fontMain.loadFromFile(FilePaths::FONT_MAIN);
	m_readyText.setFont(m_fontMain);
	m_readyText.setCharacterSize(35);
	m_fontDmg.loadFromFile(FilePaths::FONT_DAMAGE);
	m_hitText.setFont(m_fontDmg);
	m_hitText.setCharacterSize(50);
	m_damageNumberText.setFont(m_fontDmg);
	m_damageNumberText.setCharacterSize(50);
	m_damageNumberText.setFillColor({
			Colors::DAMAGE_PLAYER_TEXT_COLOR[0],
			Colors::DAMAGE_PLAYER_TEXT_COLOR[1],
			Colors::DAMAGE_PLAYER_TEXT_COLOR[2]
		});

	m_readyTextShaker.SetObjectToShake(&m_readyText);
	m_readyTextShaker.SetMaxAmplitude(5.f);
}

void EncounterMonsterTurn::OnEnter()
{
	std::cout << "Monster turn" << std::endl;

	m_readyText.setString("");
	m_hitText.setString("");
	m_damageNumberText.setString("");
	m_readyText.setCharacterSize(45);
	m_readyText.setFillColor({
		Colors::MULT_TEXT_COLOR[0],
		Colors::MULT_TEXT_COLOR[1],
		Colors::MULT_TEXT_COLOR[2]
		});
	m_readyText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - 150,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - 50
	);

	m_hitText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - 200,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2
	);

	m_damageNumberText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) - 200
	);

	m_damageTextSpeed = 200.f;

	m_parry = false;
	m_entry = false;
	m_monsterState = MonsterState::Ready;

	// Wait a random time before attacking
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis(Config::MIN_WAIT_ATTACK_TIME, Config::MAX_WAIT_ATTACK_TIME);


	m_timer = dis(gen);
	// Check death of monster
	m_isDead = m_parentEncounter->IsMonsterDead();
}

void EncounterMonsterTurn::Update(float deltaTime)
{
	if (m_isDead)
	{
		ManageDeath(deltaTime);
		return;
	}
	
	m_timer -= deltaTime;

	switch (m_monsterState)
	{
		using enum MonsterState;

		case Ready:
			if (!m_entry)
			{
				ShowReady();
			}
			if (m_timer <= 0)
			{
				m_monsterState = Fast;
				m_timer = 1/m_parentEncounter->GetMonsterSpeed();
				m_entry = false;
			}
			break;

		case Fast:
			if (!m_entry)
			{
				m_entry = true;
				Showdown();
			}
			if (m_timer <= 0)
			{
				OnMiss();
				m_monsterState = Wait;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				OnParry();
				m_monsterState = Wait;
			}
			break;

		case Wait:
			if (m_timer <= 0)
			{
				m_readyTextShaker.StopShake();
				m_timer = 1.5f;
				m_monsterState = ReceiveDamage;
				m_entry = false;
			}
			break;

		case ReceiveDamage:
			
			if (!m_entry)
			{
				OnReceiveDamage();
				m_entry = true;
			}
			if (m_timer <= 0)
			{
				m_parentEncounter->SetState(EncounterStateType::Idle);
			}
			m_damageNumberText.move(0, -deltaTime * m_damageTextSpeed);
			m_damageTextSpeed -= deltaTime * 250;

			break;

	}
	m_readyTextShaker.Update(deltaTime);
}

void EncounterMonsterTurn::OnExit()
{
	if(!m_isDead)
		m_parentEncounter->SetButtonsActive(true);
	
}

void EncounterMonsterTurn::Draw(sf::RenderWindow& window) const
{
	window.draw(m_readyText);
	window.draw(m_hitText);
	window.draw(m_damageNumberText);
}

void EncounterMonsterTurn::ManageDeath(float deltaTime)
{
	m_exitTimer -= deltaTime;

	if (m_exitTimer <= 0 && m_parentEncounter->IsDialogueFinished())
	{
		m_parentEncounter->EndEncounter();
	}

	if (!m_entry)
	{
		m_entry = true;
		m_readyText.setString("Victory !");
		m_readyText.setFillColor(sf::Color::Yellow);
		m_readyText.setPosition(
			static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_readyText.getGlobalBounds().width / 2,
			static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_readyText.getGlobalBounds().height / 2
		);
	}
}

void EncounterMonsterTurn::ShowReady()
{
	m_entry = true;
	m_damageNumberText.setString("");
	m_hitText.setString("");
	m_readyText.setString("Préparez-vous");
	m_readyText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_readyText.getGlobalBounds().width / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_readyText.getGlobalBounds().height / 2
	);
	m_audioSource.setVolume(100 * Config::GLOBAL_VOLUME_MULT);
	m_audioSource.setBuffer(m_getReady);
	m_audioSource.play();
}

void EncounterMonsterTurn::Showdown()
{
	m_hitText.setString("");
	m_readyText.setCharacterSize(90);
	m_readyText.setString("ESPACE !");
	m_readyText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_readyText.getGlobalBounds().width / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_readyText.getGlobalBounds().height / 2
	);
	m_audioSource.setBuffer(m_showdown);
	m_audioSource.setVolume(75 * Config::GLOBAL_VOLUME_MULT);
	m_audioSource.play();
	m_readyTextShaker.ResetBasePosition();
	m_readyTextShaker.AddShakeStress(1.f);
	m_readyTextShaker.SetKeepShake(true);
}

void EncounterMonsterTurn::OnParry()
{
	m_timer = 2.f; // Time to wait before going to the next state (wait before receiving damage)
	m_readyText.setString("");
	m_hitText.setString(Config::PARRY_TEXT);
	m_hitText.setFillColor(sf::Color::Blue);
	m_hitText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_hitText.getGlobalBounds().width / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_hitText.getGlobalBounds().height / 2
	);
	m_audioSource.stop();
	m_audioSource.setBuffer(m_success);
	m_audioSource.play();
	m_parry = true;
}

void EncounterMonsterTurn::OnMiss()
{
	m_timer = 2.f; // Time to wait before going to the next state (wait before receiving damage)
	m_readyText.setString("");
	m_hitText.setString("MISS");
	m_hitText.setFillColor(sf::Color::Red);
	m_hitText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_hitText.getGlobalBounds().width / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_hitText.getGlobalBounds().height / 2
	);
	m_audioSource.stop();
	m_audioSource.setBuffer(m_missed);
	m_audioSource.play();
}

void EncounterMonsterTurn::OnReceiveDamage()
{
	if (!m_parry)
	{
		
		m_readyText.setCharacterSize(40);
		m_readyText.setString("Ouch !");
		m_readyText.setPosition(
			static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_readyText.getGlobalBounds().width / 2,
			static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_readyText.getGlobalBounds().height / 2 + 100
		);
		auto damage = static_cast<int>(Config::DEFAULT_MONSTER_BASE_MULT * m_parentEncounter->GetMonsterAttackPower());
		m_parentEncounter->DamagePlayer(damage);
		m_damageNumberText.setString(std::format("{}", damage));
		m_damageNumberText.setPosition(
			static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_damageNumberText.getGlobalBounds().width / 2,
			static_cast<float>(m_parentEncounter->GetWindow().getSize().y) - m_damageNumberText.getGlobalBounds().height / 2 - 100
		);
	}
	else
	{
		
		m_readyText.setCharacterSize(35);
		m_readyText.setString("Dommages réduits !");
		m_readyText.setPosition(
			static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_readyText.getGlobalBounds().width / 2,
			static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - m_readyText.getGlobalBounds().height / 2 + 100
		);
		auto damage = static_cast<int>(Config::DEFAULT_MONSTER_BASE_MULT * m_parentEncounter->GetMonsterAttackPower() / Config::PARRY_BONUS_DEFENSE_MULT);
		m_parentEncounter->DamagePlayer(damage);
		m_damageNumberText.setString(std::format("{}", damage));
		m_damageNumberText.setPosition(
			static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2 - m_damageNumberText.getGlobalBounds().width / 2,
			static_cast<float>(m_parentEncounter->GetWindow().getSize().y) - m_damageNumberText.getGlobalBounds().height / 2 - 100
		);
	}
}
