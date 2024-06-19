#include "EncounterMonsterTurn.h"
#include "Encounter.h"
#include <iostream>
#include <random>


EncounterMonsterTurn::EncounterMonsterTurn(Encounter* parentEncounter) :
	EncounterState(parentEncounter)
{
	m_fontMain.loadFromFile(FilePaths::FONT_MAIN);
	m_readyText.setFont(m_fontMain);
	m_readyText.setCharacterSize(35);
	m_fontDmg.loadFromFile(FilePaths::FONT_DAMAGE);
	m_hitText.setFont(m_fontDmg);
	m_hitText.setCharacterSize(50);

	// Center the texts
	sf::FloatRect textRect = m_readyText.getLocalBounds();
	m_readyText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	textRect = m_hitText.getLocalBounds();
	m_hitText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void EncounterMonsterTurn::OnEnter()
{
	std::cout << "Monster turn" << std::endl;

	m_readyText.setString("");
	m_hitText.setString("");
	m_readyText.setCharacterSize(45);
	m_readyText.setFillColor({
		Colors::MULT_TEXT_COLOR[0],
		Colors::MULT_TEXT_COLOR[1],
		Colors::MULT_TEXT_COLOR[2]
		});
	m_readyText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2 - 50
	);

	m_hitText.setPosition(
		static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2,
		static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2
	);

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
				static_cast<float>(m_parentEncounter->GetWindow().getSize().x) / 2,
				static_cast<float>(m_parentEncounter->GetWindow().getSize().y) / 2
			);
		}
		

		return;
	}
	
	m_timer -= deltaTime;

	switch (m_monsterState)
	{
		using enum MonsterState;

		case Ready:
			if (!m_entry)
			{
				m_entry = true;
				m_readyText.setString("Attention");
				m_hitText.setString("");
			}
			if (m_timer <= 0)
			{
				m_monsterState = Fast;
				m_timer = m_parentEncounter->GetMonsterSpeed();
				m_entry = false;
			}
			break;

		case Fast:
			if (!m_entry)
			{
				m_entry = true;
				m_readyText.setCharacterSize(90);
				m_readyText.setString("ESPACE !");
				m_hitText.setString("");
			}
			if (m_timer <= 0)
			{
				m_timer = 2.f;
				m_readyText.setString("");
				m_hitText.setString("Miss");
				m_hitText.setFillColor(sf::Color::Red);
				m_monsterState = Wait;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_timer = 2.f;
				m_readyText.setString("");
				m_hitText.setString("Shielded");
				m_hitText.setFillColor(sf::Color::Blue);
				m_monsterState = Wait;
				m_parry = true;
			}
			break;

		case Wait:
			if (m_timer <= 0)
			{
				m_timer = 1.5f;
				m_monsterState = ReceiveDamage;
				m_entry = false;
			}
			break;

		case ReceiveDamage:
			if (!m_entry && !m_parry)
			{
				m_entry = true;
				m_readyText.setCharacterSize(40);
				m_readyText.setString("Ouch !");
				m_parentEncounter->DamagePlayer(static_cast<int>(m_parentEncounter->GetMonsterAttackPower()));
			}
			if (!m_entry && m_parry)
			{
				m_entry = true;
				m_readyText.setCharacterSize(35);
				m_readyText.setString("Dommages réduits !");
				m_parentEncounter->DamagePlayer(static_cast<int>(m_parentEncounter->GetMonsterAttackPower()/2));
			}
			if (m_timer <= 0)
			{
				m_parentEncounter->SetState(EncounterStateType::Idle);
			}
			break;

	}
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
}