#pragma once

#include "IDrawable.h"
#include "EncounterState.h"

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

	bool m_initFailed = false;
	bool m_initSucceeded = false;

	sf::Text m_damageText;
	sf::Font m_damageFont;

	AttackState m_state = AttackState::Attacking;
};