#pragma once

#include "IDrawable.h"
#include "EncounterState.h"
#include <SFML/Audio.hpp>


class EncounterFighting : public EncounterState {

	enum AttackState {
		Attacking,
		Succeeded,
		Failed
	};

public:
	explicit EncounterFighting(Encounter* parentEncounter);

	void OnEnter() override;
	void Update(float deltaTime) override;
	void OnExit() override;
	void Draw(sf::RenderWindow& window) const override;

private:
	void InitAttackBox();
	void CloseAttackBox();

	IDrawable m_cursor;
	IDrawable m_attackBox;

	float m_timer = 0;
	float m_attackBoxWidth = 0;
	float m_cursorSpeed = 0;

	int m_upcomingDamage = 0;

	bool m_initFailed = false;
	bool m_initSucceeded = false;
	bool m_damageTotalShown = false;

	sf::Text m_damageText;
	sf::Text m_multText;
	sf::Font m_damageFont;

	sf::SoundBuffer m_attackSoundBuffer;
	sf::Sound m_attackSound;

	AttackState m_state = AttackState::Attacking;
};