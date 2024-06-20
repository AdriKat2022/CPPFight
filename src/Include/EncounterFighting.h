#pragma once

#include "IDrawable.h"
#include "EncounterState.h"
#include "Configs.h"
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

	IDrawable m_cursor{ { 0, 0 }, FilePaths::SP_SH_CURSOR, {1, 2}, true };
	IDrawable m_attackBox{ { 0, 0 }, FilePaths::SP_SH_ATTACK_BOX, { 1, 1 }, true };
	IDrawable m_attackAnimation{ { 0, 0 }, FilePaths::SP_SH_ATTACK_ANIMATION, { 6, 1 }, true };

	float m_timer = 0;
	float m_attackBoxWidth = 0;
	float m_cursorSpeed = 0;
	float m_damageTextSpeed = 0;

	int m_upcomingDamage = 0;

	bool m_initFailed = false;
	bool m_initSucceeded = false;
	bool m_damageTotalShown = false;
	bool m_wasCritical = false;

	sf::Text m_damageText;
	sf::Text m_multText;
	sf::Text m_critText;
	sf::Font m_damageFont;

	sf::SoundBuffer m_hitAttack;
	sf::SoundBuffer m_criticalHitAttack;
	sf::SoundBuffer m_unbelievableAttack;
	sf::SoundBuffer m_perfectAttack;
	sf::SoundBuffer m_excellentAttack;
	sf::SoundBuffer m_normalAttack;
	sf::Sound m_attackSound;

	AttackState m_state = AttackState::Attacking;
};