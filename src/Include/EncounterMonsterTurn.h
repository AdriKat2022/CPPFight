#pragma once

#include "EncounterState.h"
#include "SFML/Audio.hpp"

class EncounterMonsterTurn : public EncounterState {

	enum MonsterState
	{
		Ready,
		Fast,
		Wait,
		ReceiveDamage
	};

public:
	explicit EncounterMonsterTurn(Encounter* parentEncounter);

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;

	void Draw(sf::RenderWindow& window) const override;

private:
	MonsterState m_monsterState = MonsterState::Ready;

	sf::Text m_readyText;
	sf::Text m_hitText;
	sf::Text m_damageNumberText;

	sf::Font m_fontDmg;
	sf::Font m_fontMain;

	sf::SoundBuffer m_showdown;
	sf::SoundBuffer m_getReady;
	sf::SoundBuffer m_success;
	sf::SoundBuffer m_missed;
	sf::Sound m_audioSource;

	bool m_isDead = false;
	bool m_entry = false;
	bool m_parry = false;
	float m_exitTimer = 1.5f;
	float m_timer = 0.0f;
	float m_damageTextSpeed = 0.f;
};